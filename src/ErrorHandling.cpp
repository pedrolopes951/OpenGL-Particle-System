#include "ErrorHandling.h"
#include <iostream>
#include <vector>


void ErrorHandling::checkCompilationError(GLuint shader, ErrorTypeShader type)
{
    int success;
    std::vector<char> infoLog(1024);

    switch (type)
    {
    case ErrorTypeShader::SHADER:
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, &infoLog[0]);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << "SHADER" << "\n"
                      << std::string(infoLog.begin(),infoLog.end()) << "\n -- --------------------------------------------------- -- " << std::endl;
        }
        break;
    case ErrorTypeShader::PROGRAM:
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog.data());
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << "PROGRAM" << "\n"
                      << std::string(infoLog.begin(),infoLog.end()) << "\n -- --------------------------------------------------- -- " << std::endl;
        }
        break;
    default:
        std::cerr << "ERROR: NOT VALID TYPE FOR SHADER COMPILATION" << "\n";
        break;
    }
}