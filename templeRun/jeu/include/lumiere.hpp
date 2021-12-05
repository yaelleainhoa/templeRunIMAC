#ifndef IMAGE_H
#define IMAGE_H

#include <glimac/glm.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <glimac/Program.hpp>

using namespace glimac;

class Lumiere{
    private: //a changer
        glm::vec4 m_position;
        glm::vec3 m_intensite;

    public:
        Lumiere(glm::vec4 pos, glm::vec3 intensite)
            :m_position(pos),
            m_intensite(intensite)
        {}
        glm::vec4 getPosition(){
            return m_position;
        }

        glm::vec3 getIntensite(){
            return m_intensite;
        }
};

class LumieresScenes{
    private:
        std::vector<glm::vec4> m_positions;
        std::vector<glm::vec3> m_intensites;
    public:

        LumieresScenes(){
            std::vector<glm::vec4> positions;
            std::vector<glm::vec3> intensites;
            m_positions=positions;
            m_intensites=intensites;

        }
        void addLumiere(Lumiere lum){
            m_positions.push_back(lum.getPosition());
            m_intensites.push_back(lum.getIntensite());
        }

        int getSize(){
            return m_positions.size();
        }

        glm::vec4 getPositionAt(int i){
            return m_positions[i];
        }
        
        glm::vec3 getIntensiteAt(int i){
            return m_intensites[i];
        }
};


void setLumieresIntensitees(LumieresScenes &lumScene, LumieresScenes &lumScenePonct, Program &program);

void setLumieresPositions(LumieresScenes &lumScene, LumieresScenes &lumScenePonct, Program &program, glm::mat4 &VMatrix);

#endif