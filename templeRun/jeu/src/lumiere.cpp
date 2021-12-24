#include "../include/lumiere.hpp"


void setLumieresIntensites(LumieresScenes &lumScene, LumieresScenes &lumScenePonct, Program &program){
    for(int i=0; i<lumScene.getSize();i++){
        const std::string strIntensite = "uIntensites["+std::to_string(i)+"]";
        glUniform3fv(glGetUniformLocation(program.getGLId(), strIntensite.c_str()), 1, glm::value_ptr(lumScene.getIntensiteAt(i)));
    }

    for(int i=0; i<lumScene.getSize();i++){
        const std::string strIntensitePonct = "uIntensitesPonct["+std::to_string(i)+"]";
        glUniform3fv(glGetUniformLocation(program.getGLId(), strIntensitePonct.c_str()), 1, glm::value_ptr(lumScenePonct.getIntensiteAt(i)));
    }
};

void setLumieresPositions(LumieresScenes &lumScene, LumieresScenes &lumScenePonct, Program &program, glm::mat4 &VMatrix){
    for(int i=0; i<lumScene.getSize();i++){
        const std::string strPosition = "uPositions["+std::to_string(i)+"]";
        glUniform4fv(glGetUniformLocation(program.getGLId(), strPosition.c_str()), 1, glm::value_ptr(lumScene.getPositionAt(i)));
    }

for(int i=0; i<lumScenePonct.getSize();i++){
        const std::string strPositionPonct = "uPositionsPonct["+std::to_string(i)+"]";
        glUniform4fv(glGetUniformLocation(program.getGLId(), strPositionPonct.c_str()), 1, glm::value_ptr(lumScenePonct.getPositionAt(i)));
    }

}