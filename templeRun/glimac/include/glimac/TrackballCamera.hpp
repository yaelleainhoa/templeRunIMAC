#pragma once

// #include <glm/glm.hpp>
// #include <GL/glew.h>

#include <glm/glm.hpp>



namespace glimac {

class TrackBallCamera{
    private:
        float m_fDistance;
        float m_fAngleX; //haut/bas
        float m_fAngleY; //droite/gauche

    public:
        //TrackBallCamera()=default;
        TrackBallCamera(const float distance=5,const float angleX=0.0, const float angleY=0.0)
        :m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY){};
        ~TrackBallCamera()=default;

        void moveFront(float delta);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        glm::mat4 getViewMatrix() const;
};

}