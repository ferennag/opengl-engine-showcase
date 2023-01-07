#ifndef ENGINE_SHOWCASE_SHADERPROGRAMCOMPILATIONEXCEPTION_H
#define ENGINE_SHOWCASE_SHADERPROGRAMCOMPILATIONEXCEPTION_H

#include <exception>
#include <string_view>
#include <string>
#include <sstream>

using namespace std;

class ShaderProgramCompilationException : public exception {
public:
    explicit ShaderProgramCompilationException(string_view log): m_log(log)
    {
        stringstream ss;
        ss << "Unable to compile shader program: " << m_log;
        m_message = ss.str();
    }

    [[nodiscard]] const char *what() const noexcept override {
        return m_message.c_str();
    }

    [[nodiscard]] string getLog() const { return m_log; }
private:
    string m_log, m_message;
};

#endif //ENGINE_SHOWCASE_SHADERPROGRAMCOMPILATIONEXCEPTION_H
