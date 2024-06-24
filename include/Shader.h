#pragma once
#include <GL/glew.h>
#include <string>

class Shader
{
private:
    /* data */
    // Program ID
    GLuint m_programID;

    // Vertex Shader in str
    std::string m_vertexShader;

    // Fragment Shader in str
    std::string m_fragmentShader;
    

    // Compile the shader
    void compile();
    


    // Load Shaders
    static std::string loadShaderSource(const std::string& filePathShader);

public:
    Shader(const std::string& vertexShaderPath,const std::string& fragmentShaderPath);

    // Use the shader
    void use() const;


    ~Shader();
};

