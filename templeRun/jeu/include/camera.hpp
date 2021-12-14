#pragma once

// #include <glm/glm.hpp>
// #include <GL/glew.h>

#include <iostream>
#include <vector>

#include <glm/glm.hpp>


class Camera{
    private:

    public:
        //Camera()=default;
        // Camera(const float distance=5,const float angleX=0.0, const float angleY=0.0)
        // :m_fDistance(distance), m_fAngleX(angleX), m_fAngleY(angleY){};
        //virtual ~Camera();

         virtual void moveFront(float delta, int LimitFrontOK=0)=0;
        virtual void rotateLeft(float degrees, bool LimitOK=true)=0;
        virtual void rotateUp(float degrees, bool LimitUpOK=true)=0;
        virtual void virageCam(float degree, glm::mat4 &VMatrix, bool &virage, float &phiStable)=0;
         virtual glm::mat4 getViewMatrix()const = 0;
};
