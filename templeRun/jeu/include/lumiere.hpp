#ifndef LUMIERE_HPP
#define LUMIERE_HPP

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
        glm::vec4 getPosition() const{
            return m_position;
        }

        glm::vec3 getIntensite() const{
            return m_intensite;
        }

        void changePosition(glm::vec4 pos){
            m_position=pos;
        }

        void changeIntensite(glm::vec3 intensite){
            m_intensite=intensite;
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

        int getSize()const {
            return m_lumiere.size();
        }

        glm::vec4 getPositionAt(int i) const{
            return m_lumiere[i].getPosition();
        }
        
        glm::vec3 getIntensiteAt(int i) const{
            return m_lumiere[i].getIntensite();
        }

        void changePositionAt(int i, glm::vec4 position){
            m_lumiere[i].changePosition(position);
        }

        void changeIntensiteAt(int i, glm::vec3 intensite){
            m_lumiere[i].changeIntensite(intensite);
        }

        void displayPosLumieres(){
            for (int i=0;i<m_lumiere.size();i++){
                std::cout << "Lumiere : "<<i<<"pos : "<<m_lumiere[i].getPosition().x<<" "<<m_lumiere[i].getPosition().y<<" "<<m_lumiere[i].getPosition().z<<std::endl;
            }
        }

        void displayIntensiteLumieres(){
            for (int i=0;i<m_lumiere.size();i++){
                std::cout << "Lumiere : "<<i<<"intensite : "<<m_lumiere[i].getIntensite().x<<" "<<m_lumiere[i].getIntensite().y<<" "<<m_lumiere[i].getIntensite().z<<std::endl;
            }
        }
};

//on envoie les intensités et positions des lumières (ponctuelles et diffuses) au shader
void setLumieresIntensites(LumieresScenes &lumScene, LumieresScenes &lumScenePonct, Program &program);
void setLumieresPositions(LumieresScenes &lumScene, LumieresScenes &lumScenePonct, Program &program, const glm::mat4 &VMatrix);

#endif