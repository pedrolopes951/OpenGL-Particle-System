#include "Shader.h"
#include "ErrorHandling.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) : m_vertexShader{Shader::loadShaderSource(vertexShaderPath)}, m_fragmentShader{Shader::loadShaderSource(fragmentShaderPath)}
{

    // Compilation of shaders
    this->compile();
}

std::string Shader::loadShaderSource(const std::string &filePathShader)
{
    std::ifstream shaderFile;
    std::stringstream shaderStream;

    // Ensure ifstream objects throw exception
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open the file
        shaderFile.open(filePathShader);

        shaderStream << shaderFile.rdbuf();

        shaderFile.close();

        return shaderStream.str();
    }
    catch (const std::ifstream::failure &e)
    {

        std::cerr << " ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ:  " << e.what() << '\n';

        throw("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ\n");
    }

    return std::string();
}

void Shader::compile()
{

    const char *vertexShader = m_vertexShader.c_str();
    const char *fragmentShader = m_fragmentShader.c_str();

    // Shaders
    GLuint vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShader, NULL);
    glCompileShader(vertex);
    ErrorHandling::checkCompilationError(vertex,ErrorTypeShader::SHADER);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShader, NULL);
    glCompileShader(fragment);
    ErrorHandling::checkCompilationError(fragment,ErrorTypeShader::SHADER);

    // Shader Program
    m_programID = glCreateProgram();

    glAttachShader(m_programID,vertex);
    glAttachShader(m_programID,fragment);

    glLinkProgram(m_programID);

    ErrorHandling::checkCompilationError(m_programID,ErrorTypeShader::PROGRAM);

    // Delete the shaders as they're linked into out program, and we can free up memory 

    glDeleteShader(vertex);
    glDeleteShader(fragment);


}


void Shader::use() const
{
    // Activate the shader Program
    glUseProgram(m_programID);    
}


Shader::~Shader()
{
    glDeleteProgram(m_programID);
}
