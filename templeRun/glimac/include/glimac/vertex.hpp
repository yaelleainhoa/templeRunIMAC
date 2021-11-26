#pragma once

#include <GL/glew.h>
#include "glm.hpp"
#include "Shader.hpp"
#include "Program.hpp"
#include <vector>

namespace glimac {

struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

}
