#ifndef ENGINE_SHOWCASE_SHADERMANAGER_H
#define ENGINE_SHOWCASE_SHADERMANAGER_H

using namespace std;

#include <memory>
#include <map>
#include <string>
#include <string_view>
#include <QObject>
#include <QOpenGLShaderProgram>
#include <QFileSystemWatcher>

struct Shader {
    string path;
    unique_ptr<QOpenGLShader> shader;
    QOpenGLShader::ShaderType type;
};

/**
 * An advanced singleton Shader Manager class that can hot-load shaders when those change on the filesystem.
 */
class ShaderManager: public QObject {
    Q_OBJECT
public:
    ShaderManager(const ShaderManager &other) = delete;
    ShaderManager& operator=(const ShaderManager& other) = delete;
    ~ShaderManager() override = default;

    static ShaderManager& getInstance();

    QOpenGLShaderProgram& load(string_view name, string_view vertexPath, string_view fragmentPath);
    [[nodiscard]] QOpenGLShaderProgram& getShaderProgram(string_view name) const;

    void cleanup();
public slots:
    void shaderChanged(const QString &path);
private:
    /**
     * Unique singleton instance of this class.
     */
    static unique_ptr<ShaderManager> s_instance;

    map<string, unique_ptr<QOpenGLShaderProgram>> m_shaderProgramCache;

    /**
     * Each shader is cached in this map, and reused between shader programs.
     */
    map<string, Shader> m_shaderCache;

    /**
     * Stores a reference from shader path -> shader program names.
     * This way when a shader changes, we can update all the shader programs using that shader.
     */
    multimap<string, string> m_shaderReference;
    QFileSystemWatcher m_fsWatcher;

    ShaderManager();
    void compileShader(QOpenGLShader::ShaderType type, string_view path);
};


#endif //ENGINE_SHOWCASE_SHADERMANAGER_H
