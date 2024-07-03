#include "Shader.h"
#include "ErrorHandling.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) 
{
    m_shaderSources[GL_VERTEX_SHADER] = Shader::loadShaderSource(vertexShaderPath); 
    m_shaderSources[GL_FRAGMENT_SHADER] = Shader::loadShaderSource(fragmentShaderPath);

    // Compilation of shaders
    this->compile();
}

Shader::Shader(const std::unordered_map<GLenum, std::string> &shaderPaths) : m_shaderSources{shaderPaths}
{
    for (auto& [type,path]: m_shaderSources)
    {
        m_shaderSources[type] = Shader::loadShaderSource(path);
    }
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

    std::vector<GLuint> shaderIDs;

    for (const auto&[type,source]: m_shaderSources)
    {
        const char *shaderCode = source.c_str();

        GLuint shader = glCreateShader(type);
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        ErrorHandling::checkCompilationError(shader,ErrorTypeShader::SHADER);
        shaderIDs.push_back(shader);

    }
    


    // Shader Program
    m_programID = glCreateProgram();

    for (const auto& shaderID : shaderIDs)
    {
        glAttachShader(m_programID,shaderID);
    }
    

    glLinkProgram(m_programID);

    ErrorHandling::checkCompilationError(m_programID,ErrorTypeShader::PROGRAM);

    // Delete the shaders as they're linked into out program, and we can free up memory 

    for (const auto& shaderID : shaderIDs)
    {
        glDeleteShader(shaderID);
    }
    


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
