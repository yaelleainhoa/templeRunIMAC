#pragma once

#include <vector>
#include <glimac/Image.hpp>
#include <iostream>
#include <GL/glew.h>

namespace glimac {

struct Texture{
    unsigned int id;
    std::string type;
    std::string path;
};

void creerUneTexture(GLuint &texture, std::unique_ptr<glimac::Image> &image);
void creerDeuxTextures(GLuint &texture0, GLuint &texture1, std::unique_ptr<glimac::Image> &image0, std::unique_ptr<glimac::Image> &image1);

}
