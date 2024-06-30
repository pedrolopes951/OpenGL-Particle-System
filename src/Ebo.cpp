#include "Ebo.h"


Ebo::Ebo(const GLuint* data, GLsizeiptr size)
{
    glGenBuffers(1,&m_ebo_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ebo_ID); // target to which object is bound (vertex attributes),
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,size, data ,GL_STATIC_DRAW); // malloc type allocation in GPU
}

void Ebo::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ebo_ID);
}
void Ebo::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void Ebo::deleteEbo() const
{
    glDeleteBuffers(0,&m_ebo_ID);
}

Ebo::~Ebo()
{
    glDeleteBuffers(1,&m_ebo_ID);
}