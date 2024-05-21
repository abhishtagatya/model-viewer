#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "glad/glad.h"
#include "vbo.h"

// Vertex Array Object : Manages vertex attribute state and configurations.
class VAO {
public:
    GLuint id;
    VAO();

    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void LinkVBO(VBO& VBO, GLuint layout);
    void Bind();
    void Unbind();
    void Delete();
};


#endif
