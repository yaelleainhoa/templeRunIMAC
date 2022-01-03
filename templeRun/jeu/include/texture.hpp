#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <vector>
#include <glimac/Image.hpp>
#include <iostream>
#include <GL/glew.h>

struct Texture{
    unsigned int id;
    std::string type;
    std::string path;
};

#endif