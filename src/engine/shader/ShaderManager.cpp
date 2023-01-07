#include <memory>
#include <QOpenGLShaderProgram>
#include "ShaderManager.h"
#include "ShaderCompilationException.h"
#include "ShaderProgramCompilationException.h"

unique_ptr<ShaderManager> ShaderManager::s_instance = nullptr;

ShaderManager &ShaderManager::getInstance() {
    if (!s_instance) {
        s_instance = unique_ptr<ShaderManager>(new ShaderManager());
    }

    return *s_instance;
}

ShaderManager::ShaderManager() {
    QObject::connect(&m_fsWatcher, &QFileSystemWatcher::fileChanged, this, &ShaderManager::shaderChanged);
}


void ShaderManager::compileShader(QOpenGLShader::ShaderType type, string_view path) {
    if (!m_shaderCache.contains(path.data())) {
        qDebug() << "Shader is not in the cache yet: " << path.data() << ". Compiling...";
        auto shader = make_unique<QOpenGLShader>(type);
        if (!shader->compileSourceFile(path.data())) {
            throw ShaderCompilationException(path, shader->log().toStdString());
        }

        m_shaderCache[path.data()] = {
                .path = path.data(),
                .shader = move(shader),
                .type = type
        };

        m_fsWatcher.addPath(path.data());
    }
}

QOpenGLShaderProgram &
ShaderManager::load(string_view name, string_view vertexPath, string_view fragmentPath) {
    compileShader(QOpenGLShader::Vertex, vertexPath);
    compileShader(QOpenGLShader::Fragment, fragmentPath);

    auto shader = make_unique<QOpenGLShaderProgram>();
    shader->addShader(m_shaderCache[vertexPath.data()].shader.get());
    shader->addShader(m_shaderCache[fragmentPath.data()].shader.get());
    if (!shader->link()) {
        throw ShaderProgramCompilationException(shader->log().toStdString());
    }

    m_shaderProgramCache[name.data()] = move(shader);
    m_shaderReference.insert({vertexPath.data(), name.data()});
    m_shaderReference.insert({fragmentPath.data(), name.data()});

    return *m_shaderProgramCache[name.data()];
}

void ShaderManager::cleanup() {
    m_shaderProgramCache.clear();
    m_shaderCache.clear();
    m_shaderReference.clear();
}

QOpenGLShaderProgram &ShaderManager::getShaderProgram(string_view name) const {
    return *m_shaderProgramCache.find(name.data())->second;
}

void ShaderManager::shaderChanged(const QString &path) {
    qDebug() << "File changed: " << path << ". Recompiling...";
    auto &existingShader = m_shaderCache[path.toStdString()];
    auto newShader = make_unique<QOpenGLShader>(existingShader.type);
    if (!newShader->compileSourceFile(path)) {
        qDebug() << "Failed to compile shader: " << path << ". Keeping the old version.";
        return;
    }

    auto begin = m_shaderReference.lower_bound(path.toStdString());
    auto end = m_shaderReference.upper_bound(path.toStdString());

    for (auto &it{begin}; it != end; ++it) {
        qDebug() << "Updating shader program: " << it->second.data();
        auto &shader = *m_shaderProgramCache[it->second];
        auto existingShaders = shader.shaders();

        auto result = find_if(existingShaders.begin(), existingShaders.end(), [&existingShader](QOpenGLShader *s) {
            return s->shaderType().testFlags(existingShader.type);
        });

        if (result == existingShaders.end()) {
            qDebug() << "ERROR: Didn't find an existing shader for " << path;
            continue;
        }

        shader.removeShader(*result);
        shader.addShader(newShader.get());
        shader.link();
        qDebug() << "Finished updating shader program: " << it->second.data();
    }

    existingShader.shader.reset();
    existingShader.shader = move(newShader);
}


