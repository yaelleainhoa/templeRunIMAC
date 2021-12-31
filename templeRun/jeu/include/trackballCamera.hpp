#pragma once

#include <glm/glm.hpp>
#include "variablesGlobales.hpp"
#include "camera.hpp"


class TrackBallCamera : public Camera{
    protected:
        float m_fDistance;
        float m_fAngleX; //haut/bas
        float m_fAngleY; //droite/gauche

    public:
        //TrackBallCamera()=default;
        TrackBallCamera(const float distance=2.5f*largeur,const float angleX=0.30, const float angleY=0.0)
        :m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY){};
        ~TrackBallCamera()=default;

        void moveFront(float delta);
        void rotateLeft(float degrees);
        void rotateUp(float degrees);
        void virageCam(float degree);
        void virageCamPassif(float degrees);
        void reset();
        float getPhi();
        void moveLeft(float t);
        void moveUp(float t);
        glm::mat4 getViewMatrix() const;
};