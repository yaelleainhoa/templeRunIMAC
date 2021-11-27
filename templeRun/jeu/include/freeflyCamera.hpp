#pragma once

#include <glm/glm.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

class FreeflyCamera{
    private:
        glm::vec3 m_Position; //position cam
        float m_fPhi; //droite/gauche
        float m_fTheta; //haut/bas
        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;

    public:
        FreeflyCamera(const glm::vec3 position=glm::vec3(0.0,0.0,0.0),const float phi=M_PI, const float theta=0.0);
        ~FreeflyCamera()=default;

        void computeDirectionVectors();
        void moveLeft(float t);
        void moveFront(float t);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        glm::mat4 getViewMatrix() const;
};