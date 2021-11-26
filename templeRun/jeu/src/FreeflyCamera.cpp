#include "../include/FreeflyCamera.hpp"
#include <glimac/SDLWindowManager.hpp>

#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>

void FreeflyCamera::computeDirectionVectors(){
	float phi=m_fPhi;
	float theta=m_fTheta;
	m_FrontVector=glm::vec3(glm::cos(theta)*glm::sin(phi), glm::sin(theta), glm::cos(theta)*glm::cos(phi));
    m_LeftVector=glm::vec3(glm::sin(phi+M_PI/2), 0, glm::cos(phi+M_PI/2));
    m_UpVector=glm::cross(m_FrontVector, m_LeftVector);
}

FreeflyCamera::FreeflyCamera(const glm::vec3 position,const float phi, const float theta)
	:m_Position(position), m_fPhi(phi), m_fTheta(theta){
		computeDirectionVectors();
	};

void FreeflyCamera::moveLeft(float t){
	m_Position+=t*m_LeftVector;
	computeDirectionVectors();
};
        
void FreeflyCamera::moveFront(float t){
	m_Position+=t*m_FrontVector;
	computeDirectionVectors();
};

void FreeflyCamera::rotateLeft(float degrees){
	m_fPhi+=degrees*M_PI/180;
	computeDirectionVectors();
};

void FreeflyCamera::rotateUp(float degrees){
	m_fTheta+=degrees*M_PI/180;
	computeDirectionVectors();
};

glm::mat4 FreeflyCamera::getViewMatrix() const{
	glm::mat4 view=glm::lookAt(m_Position, m_Position+m_FrontVector, m_UpVector);
	return view;
}
