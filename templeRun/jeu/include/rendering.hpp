#pragma once

#include <glm/glm.hpp>
#include "variablesGlobales.hpp"

// float distanceCase(const glm::mat4 ModelMatrix){
//     glm::vec4 M = glm::normalize(ModelMatrix[3]);
//     glm::vec3 pos = glm::vec3(M.x, M.y, M.z);
//     return glm::distance(glm::vec3(0), pos);
// }

// float saut(){
//     float l=largeur*2.0;
//     float d=x*vitesse;
//     if(d>l){
//         return 0.0;
//     }
//     return (hauteur * d*(d-l)/(l/2*(l/2-l)));
// }