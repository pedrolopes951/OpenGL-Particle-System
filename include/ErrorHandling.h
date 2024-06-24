#pragma once
#include <GL/glew.h>

enum class ErrorTypeShader
{
    SHADER,
    PROGRAM
};

namespace ErrorHandling
{
    void checkCompilationError(GLuint shader, ErrorTypeShader type);
}