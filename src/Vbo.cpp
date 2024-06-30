#include "Vbo.h"


Vbo::Vbo(const GLfloat* data, GLsizeiptr size)
{
    glGenBuffers(1,&m_vbo_ID);
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo_ID); // target to which object is bound (vertex attributes),
    glBufferData(GL_ARRAY_BUFFER,size, data ,GL_STATIC_DRAW); // malloc type allocation in GPU
}

void Vbo::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo_ID);
}
void Vbo::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void Vbo::deleteVbo() const
{
    glDeleteBuffers(0,&m_vbo_ID);
}

Vbo::~Vbo()
{
    glDeleteBuffers(1,&m_vbo_ID);
}