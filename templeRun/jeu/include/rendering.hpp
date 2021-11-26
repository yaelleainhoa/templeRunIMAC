#pragma once

#include <glm/glm.hpp>

float distance(const glm::mat4 ModelMatrix){
    glm::vec4 M = glm::normalize(ModelMatrix[3]);
    glm::vec3 pos = glm::vec3(M.x, M.y, M.z);
    return glm::distance(glm::vec3(0), pos);
}
