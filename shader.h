#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "glad/glad.h"
#include "file.h"

class Shader {
public:
    GLuint id;
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();
private:
    void compileErrors(unsigned int shader, const char* type);
};

#endif
