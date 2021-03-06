#ifndef FREEFLYCAMERA_HPP
#define FREEFLYCAMERA_HPP


#include <glm/glm.hpp>
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "variablesGlobales.hpp"
#include "./camera.hpp"
#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>



class FreeflyCamera : public Camera{
    protected:
        glm::vec3 m_Position; //position cam
        float m_fPhi; //droite/gauche
        float m_fTheta; //haut/bas
        glm::vec3 m_FrontVector;
        glm::vec3 m_LeftVector;
        glm::vec3 m_UpVector;

    public:
        FreeflyCamera(const glm::vec3 position=glm::vec3(0.0f,hauteurInitFreeflyCamera,0.0f),const float phi=M_PI, const float theta=0.0);
        ~FreeflyCamera()=default;
        void reset();
        void computeDirectionVectors();
        void moveLeft(float t);
        void moveFront(float t);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        void virageCam(float degrees);
        void virageCamPassif(float degrees);
        void moveUp(float t);
        glm::mat4 getViewMatrix() const;
};

#endif