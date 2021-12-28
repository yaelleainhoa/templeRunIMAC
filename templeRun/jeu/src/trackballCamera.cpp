#include "../include/camera.hpp"
#include "../include/trackballCamera.hpp"
#include <glimac/SDLWindowManager.hpp>

#include <iostream>
#include <glm/glm.hpp>
#include <GL/glew.h>


float TrackBallCamera::getPhi(){
	return 0.0;
}

void TrackBallCamera::reset(){
	m_fAngleY=0.0;
}

void TrackBallCamera::virageCam(float degrees){
	float echelle = ((M_PI+angleActuel+angleRotation)-(M_PI))/(M_PI/2); // ou /(M_PI/3) pour un virage plus rapide
	float angle = echelle*M_PI/180;
	if(sensRotation>0){
		if(m_fAngleY> -(angleActuel+angleRotation)){
			m_fAngleY-=angle;
			rotationPersonnage+=angle;
		}
		else {
			sensRotation=-sensRotation;
			virage=false;
	        alreadyRotated = false;
			angleActuel+=angleRotation;
			rotationPersonnage=angleActuel;
			casTerrain=1;
		}
	}
	else{
		if(m_fAngleY< -(angleActuel-angleRotation)){
			m_fAngleY+=angle;
			rotationPersonnage-=angle;
		}
		else {
			sensRotation=-sensRotation;
			virage=false;
	        alreadyRotated = false;
			angleActuel-=angleRotation;
			rotationPersonnage=angleActuel;
			casTerrain=1;
		}
	}
}

void TrackBallCamera::virageCamPassif(float degrees){
	float echelle = ((M_PI+angleActuel+angleRotation)-(M_PI))/(M_PI/2); // ou /(M_PI/3) pour un virage plus rapide
	float angle = echelle*M_PI/180;
	if(sensRotation>0){
		if(m_fAngleY> -(angleActuel+angleRotation)){
			m_fAngleY-=angle;
		}
	}
	else{
		if(m_fAngleY< -(angleActuel-angleRotation)){
			m_fAngleY+=angle;
		}
	}
}

void TrackBallCamera::moveFront(float delta){
	//std::cout << "m_fDistance = " << m_fDistance << std::endl;
	m_fDistance+=delta*0.1;
	if(std::abs(m_fDistance) <=2){
		if(mouvementHorizontalTranslation == -1){
			valIncremCameraBACK = 0;
			m_fDistance+=-0.5*0.1;
			valIncremCameraFRONT = 0.5;
		}
		else if(mouvementHorizontalTranslation == 1){
			valIncremCameraFRONT = 0;
			m_fDistance+=0.5*0.1;
			valIncremCameraBACK = -0.5;
		}
	}	
}

void TrackBallCamera::rotateLeft(float degrees){
	
	m_fAngleY+=degrees*0.05;
}

  /***** PAS BESOIN DE ROTATEUP POUR LA TRACKBALL ******/  
void TrackBallCamera::rotateUp(float degrees){
	m_fAngleX+=degrees*0.05;
}



glm::mat4 TrackBallCamera::getViewMatrix() const{
	glm::mat4 view=glm::mat4(1);
	view=glm::translate(view, glm::vec3(0,-1,-m_fDistance));
	view=glm::rotate(view, m_fAngleX, glm::vec3(1.0,0.0,0.0));
	view=glm::rotate(view, m_fAngleY, glm::vec3(0.0,1.0,0.0));
	return view;
}
