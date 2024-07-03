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
    Shader(const std::string& vertexShaderPath,const std::string& fragmentShaderPath);
    Shader(const std::unordered_map<GLenum, std::string>& shaderPaths);


    // Use the shader
    void use() const;

    GLuint getProgramID()const {return m_programID;}



    


    ~Shader();
};

