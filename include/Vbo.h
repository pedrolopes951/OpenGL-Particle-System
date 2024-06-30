#pragma once
#include <GL/glew.h>


class Vbo
{

private:
    /* data */
    GLuint m_vbo_ID;

public:
    Vbo(const GLfloat* data, GLsizeiptr size);
    ~Vbo();

    void bind() const;
    void unbind() const;
    void deleteVbo() const;

};
