#pragma once
#include <GL/glew.h>

class Ebo {
private:
    GLuint m_ebo_ID;
public:
    Ebo(const GLuint* data, GLsizeiptr size);
    ~Ebo();

    void bind() const;
    void unbind() const;
    void deleteEbo() const;
};

