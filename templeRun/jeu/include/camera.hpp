#pragma once

// #include <glm/glm.hpp>
// #include <GL/glew.h>

#include <iostream>
#include <vector>

#include <glm/glm.hpp>


class Camera{
    private:

    public:
        virtual void moveFront(float delta)=0;
        virtual void rotateLeft(float degrees)=0;
        virtual void rotateUp(float degrees)=0;
        virtual void virageCam(float degrees)=0;
        virtual void virageCamPassif(float degrees)=0;
        virtual void reset()=0;
        virtual void moveLeft(float t)=0;
        virtual void moveUp(float t)=0;
        virtual glm::mat4 getViewMatrix()const = 0;
};
