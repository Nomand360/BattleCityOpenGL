#include "ShaderProgram.h"
#include <iostream>

Renderer::ShaderProgram::ShaderProgram(const std::string &vertexShader, const std::string &fragmentShader)
{
    GLuint vertexShaderID;
    if(!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)){
        std::cerr << "ERROR VERTEX SHADER!" << std::endl;
        return;
    }

    GLuint fragmentShaderID;
    if(!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)){
        std::cerr << "ERROR FRAGMENT SHADER!" << std::endl;
        glDeleteShader(vertexShaderID);
        return;
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShaderID);
    glAttachShader(m_ID, fragmentShaderID);
    glLinkProgram(m_ID);
    GLint status;
    glGetShaderiv(m_ID, GL_LINK_STATUS, &status);
    if(!status){
        ushort buffSize = 1024;
        GLchar infolog[buffSize];
        glGetShaderInfoLog(m_ID, buffSize, nullptr, infolog);
        std::cerr << "ERROR::SHADER: Link error: \n" << infolog << std::endl;
    }
    else{
        m_isCompiled = true;
    }
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);
}

Renderer::ShaderProgram::ShaderProgram(ShaderProgram &&shaderProgram) noexcept
{
    m_ID = shaderProgram.m_ID;
    m_isCompiled = shaderProgram.m_isCompiled;

    shaderProgram.m_ID = 0;
    shaderProgram.m_isCompiled = false;
}

Renderer::ShaderProgram &Renderer::ShaderProgram::operator=(ShaderProgram &&shaderProgram) noexcept
{
    glDeleteProgram(m_ID);
    m_ID = shaderProgram.m_ID;
    m_isCompiled = shaderProgram.m_isCompiled;

    shaderProgram.m_ID = 0;
    shaderProgram.m_isCompiled = false;

    return *this;
}

Renderer::ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(m_ID);
}

void Renderer::ShaderProgram::use() const
{
    glUseProgram(m_ID);
}

bool Renderer::ShaderProgram::createShader(const std::string &source, const GLenum shaderType, GLuint &shaderID)
{
    shaderID = glCreateShader(shaderType);
    const char *code = source.c_str();
    glShaderSource(shaderID, 1, &code, nullptr);
    glCompileShader(shaderID);
    GLint status;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
    if(!status){
        ushort buffSize = 1024;
        GLchar infolog[buffSize];
        glGetShaderInfoLog(shaderID, buffSize, nullptr, infolog);
        std::cerr << "ERROR::SHADER: Compile error: \n" << infolog << std::endl;
        return false;
    }
    return true;
}
