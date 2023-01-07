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
    static unique_ptr<ShaderManager> s_instance;
    map<string, unique_ptr<QOpenGLShaderProgram>> m_shaderProgramCache;
    map<string, Shader> m_shaderCache;
    multimap<string, string> m_shaderReference;
    QFileSystemWatcher m_fsWatcher;

    ShaderManager();
    void compileShader(QOpenGLShader::ShaderType type, string_view path);
};


#endif //ENGINE_SHOWCASE_SHADERMANAGER_H
