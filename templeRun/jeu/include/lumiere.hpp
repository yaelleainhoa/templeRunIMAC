#ifndef IMAGE_H
#define IMAGE_H

#include <glimac/glm.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <glimac/Program.hpp>

using namespace glimac;

class Lumiere{
    private:
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

        void changePosition(glm::vec4 pos){
            m_position=pos;
        }
};

class LumieresScenes{
    private:
        std::vector<Lumiere> m_lumiere;
    public:

        LumieresScenes(){
            std::vector<Lumiere> lumiere;
            m_lumiere=lumiere;
        }
        void addLumiere(Lumiere lum){
            m_lumiere.push_back(lum);
        }

        int getSize(){
            return m_lumiere.size();
        }

        glm::vec4 getPositionAt(int i){
            return m_lumiere[i].getPosition();
        }
        
        glm::vec3 getIntensiteAt(int i){
            return m_lumiere[i].getIntensite();
        }

        void changePositionAt(int i, glm::vec4 position){
            m_lumiere[i].changePosition(position);
        }
};


void setLumieresIntensites(LumieresScenes &lumScene, LumieresScenes &lumScenePonct, Program &program);

void setLumieresPositions(LumieresScenes &lumScene, LumieresScenes &lumScenePonct, Program &program, glm::mat4 &VMatrix);

#endif