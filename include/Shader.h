#pragma once
#include <GL/glew.h>
#include <string>
#include <unordered_map>

class Shader
{
private:
    /* data */
    // Program ID
    GLuint m_programID{};

    // Store the shaders of the shader/
    std::unordered_map<GLenum,std::string> m_shaderSources; 
    

    // Compile the shader
    void compile();
    


    // Load Shaders
    static std::string loadShaderSource(const std::string& filePathShader);

public:
    Shader(){}
    Shader(const std::string& vertexShaderPath,const std::string& fragmentShaderPath);
    Shader(const std::unordered_map<GLenum, std::string>& shaderPaths);

    // Delete cpy construcotr and copy assignment

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;


    // Use the shader
    void use() const;

    GLuint getProgramID()const {return m_programID;}



    


    ~Shader();
};

