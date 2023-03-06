#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <string>
#include <glad/glad.h>

namespace Renderer {
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader);
        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram &operator=(ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram() = delete;
        ShaderProgram(const ShaderProgram&) = delete;
        ShaderProgram &operator=(const ShaderProgram&) = delete;
        ~ShaderProgram();
        bool isCompiled() {return m_isCompiled;}
        void use() const;
    private:
        bool createShader(const std::string &source, const GLenum shaderType, GLuint &shaderID);
        bool m_isCompiled = false;
        GLuint m_ID = 0;
    };
}


#endif // SHADERPROGRAM_H
