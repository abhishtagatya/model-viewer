#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "glad/glad.h"
#include "stb/stb_image.h"

#include "shader.h"


class Texture {
public:
    GLuint id;
    const char* type;
    GLuint unit;

    Texture(const char* image, const char* texType, GLuint slot);

    static void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    static void Unbind();
    void Delete();
};

#endif