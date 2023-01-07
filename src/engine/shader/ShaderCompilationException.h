#ifndef ENGINE_SHOWCASE_SHADERCOMPILATIONEXCEPTION_H
#define ENGINE_SHOWCASE_SHADERCOMPILATIONEXCEPTION_H

#include <exception>
#include <string_view>
#include <string>
#include <sstream>

using namespace std;

class ShaderCompilationException : public exception {
public:
    explicit ShaderCompilationException(string_view path, string_view log): m_path(path), m_log(log)
    {
        stringstream ss;
        ss << "Unable to compile shader file: " << m_path;
        m_message = ss.str();
    }

    [[nodiscard]] const char *what() const noexcept override {
        return m_message.c_str();
    }

    [[nodiscard]] string getPath() const { return m_path; }
    [[nodiscard]] string getLog() const { return m_log; }
private:
    string m_path, m_log, m_message;
};

#endif //ENGINE_SHOWCASE_SHADERCOMPILATIONEXCEPTION_H
