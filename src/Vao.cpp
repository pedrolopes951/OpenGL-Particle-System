#include "Vao.h"

Vao::Vao()
{
    glGenVertexArrays(1,&m_vao_ID);
}

Vao::~Vao()
{
    this->deleteVao();
}

void Vao::bind() const
{
    glBindVertexArray(m_vao_ID);
}

void Vao::unbind() const
{
    glBindVertexArray(0);
}

void Vao::deleteVao() const
{
    glDeleteVertexArrays(1,&m_vao_ID);
}

void Vao::setAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer) const
{
    glVertexAttribPointer(index,size,type, normalized, stride, pointer);// location is 0, xyz numebr os positions, gl_float,normzalize no,
    glEnableVertexAttribArray(index);

}
