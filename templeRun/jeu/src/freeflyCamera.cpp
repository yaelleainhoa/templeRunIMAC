#include "../include/camera.hpp"
#include "../include/freeflyCamera.hpp"
#include <glimac/SDLWindowManager.hpp>

#include <iostream>
#include <math.h>
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
        
void FreeflyCamera::moveFront(float t, int LimitFrontOK){
	m_Position+=t*m_FrontVector;
	/*//si elle va trop haut ou trop bas 
	if(m_Position.y >0 && m_Position.y < 3)LimitFrontOK = 0;
	else LimitFrontOK = 1;

	// si elle va trop loin du perso : trop gros dézoom ou trop gros zoom
	if(m_Position.z < -5 || m_Position.z > 5) LimitFrontOK = 2;

	if(LimitFrontOK == 0) m_Position+=t*m_FrontVector;
	else if(LimitFrontOK == 1){
		// tests selon si elle est en haut ou en bas
		if(m_Position.y <=0) m_Position.y = 0.5;
		if(m_Position.y >= 3)m_Position.y = 2.5;
		std::cout << LimitFrontOK << "et position.y  = " << m_Position.y << std::endl;
	} 
	else if(LimitFrontOK == 2){
		//tests selon si elle est dézoomer ou zoomer
		if(m_Position.z <= -5) m_Position.z = -4.5;
		if(m_Position.z >= 5) m_Position.z = 4.5;
	}
	*/
	computeDirectionVectors();
	
	//std::cout << m_Position.x << " " << m_Position.y << " " << m_Position.z << std::endl;
};

void FreeflyCamera::virageCam(float degrees){
	std::cout << "m_Phi = " << m_fPhi*(180/M_PI) << std::endl;
	//m_fPhi-=(degrees*3/4)*M_PI/180;
	
	float angle = 0.25;
	for(int i=0;i<degrees;i++){
		m_fPhi-=angle*M_PI/180;
		std::cout << "m_Phi = " << m_fPhi*(180/M_PI)  << std::endl;
	}
	std::cout << "m_Phi = " << m_fPhi*(180/M_PI)  << std::endl;
	computeDirectionVectors();
}

void FreeflyCamera::rotateLeft(float degrees, bool LimitOK){
	if(m_fPhi > M_PI - atan(3/2.0*1.5) && m_fPhi < M_PI + atan(3/2.0*1.5)) LimitOK = true;
	else LimitOK = false;
	if(LimitOK){
		m_fPhi+=degrees*M_PI/180;
	}else{
		if(m_fPhi <= M_PI - atan(3/2.0*1.5)) m_fPhi = M_PI - atan(3/2.0*1.5-0.5);
		else if(m_fPhi >= M_PI + atan(3/2.0*1.5)) m_fPhi = M_PI + atan(3/2.0*1.5-0.5);
	}
	
	computeDirectionVectors();
	std::cout << m_fPhi*180/M_PI << std::endl;
	if(m_fPhi*180/M_PI < 246 && m_fPhi*180/M_PI > 114) std::cout << "on est dans le bon champs de vision" << std::endl;
};

void FreeflyCamera::rotateUp(float degrees, bool LimitUpOK){
	if(m_fTheta > 0 - atan(3/2.0*1.5) && m_fTheta < 0 + atan(3/2.0*1.5)) LimitUpOK = true;
	else LimitUpOK = false;
	if(LimitUpOK){
		m_fTheta+=degrees*M_PI/180;
	}else{
		if(m_fTheta <= 0 - atan(3/2.0*1.5)) m_fTheta = 0 - atan(3/2.0*1.5-0.5);
		else if(m_fTheta >= 0 + atan(3/2.0*1.5)) m_fTheta = 0 + atan(3/2.0*1.5-0.5);
	}

	//m_fTheta+=degrees*M_PI/180;
	computeDirectionVectors();
};

glm::mat4 FreeflyCamera::getViewMatrix() const{
	glm::mat4 view=glm::lookAt(m_Position, m_Position+m_FrontVector, m_UpVector);
	return view;
}
