#pragma once
#include <GL/glew.h>
    
class Vao
{
private:
    /* data */
    GLuint m_vao_ID;

public:
    Vao();
    ~Vao();


    void bind() const;
    void unbind() const;
    void deleteVao() const;

    void setAttribute(GLuint index,GLint size , GLenum type , GLboolean normalized, GLsizei stride, const void* pointer) const;

};

