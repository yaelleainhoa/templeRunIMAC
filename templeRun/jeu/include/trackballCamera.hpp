#pragma once

#include <glm/glm.hpp>
#include "camera.hpp"


class TrackBallCamera : public Camera{
    protected:
        float m_fDistance;
        float m_fAngleX; //haut/bas
        float m_fAngleY; //droite/gauche

    public:
        //TrackBallCamera()=default;
        TrackBallCamera(const float distance=3,const float angleX=0.0, const float angleY=0.0)
        :m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY){};
        ~TrackBallCamera()=default;

        void moveFront(float delta, int LimitFrontOK=0);
        void rotateLeft(float degrees, bool LimitOK=true);
        void rotateUp(float degrees, bool LimitUpOK=true);
        void virageCam(float degree);
        glm::mat4 getViewMatrix() const;
};