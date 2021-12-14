#include "../include/camera.hpp"
#include "../include/trackballCamera.hpp"
#include <glimac/SDLWindowManager.hpp>

#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>


void TrackBallCamera::virageCam(float degrees, glm::mat4 &VMatrix, bool &virage, float &phiStable){
	float angle = 0;
	while(angle<degrees){
		m_fAngleY+=angle*M_PI/180;
	}
}

void TrackBallCamera::moveFront(float delta, int LimitFrontOK){
	m_fDistance+=delta*0.1;
}

void TrackBallCamera::rotateLeft(float degrees, bool LimitOK){
	m_fAngleY+=degrees*0.1;
}

void TrackBallCamera::rotateUp(float degrees, bool LimitUpOK){
	m_fAngleX+=degrees*0.1;
}



glm::mat4 TrackBallCamera::getViewMatrix() const{
	glm::mat4 view=glm::mat4(1);
	view=glm::translate(view, glm::vec3(-0.5,-1,-m_fDistance));
	view=glm::rotate(view, m_fAngleX, glm::vec3(1.0,0.0,0.0));
	view=glm::rotate(view, m_fAngleY, glm::vec3(0.0,1.0,0.0));
	return view;
}
