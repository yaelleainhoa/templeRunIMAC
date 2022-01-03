#include "../include/trackballCamera.hpp"

void TrackBallCamera::reset(){
	m_fDistance=2.5f*largeur;
	m_fAngleX=0.30;
	m_fAngleY=-angleActuel;
}

//même principe que pour la freeflyCamera 
void TrackBallCamera::virageCam(float degrees){
	float echelle = ((M_PI+angleActuel+angleRotation)-(M_PI))/(M_PI/2);
	float angle = 2*echelle*M_PI/180;
	//virage à gauche
	if(sensRotation>0){
		// le virage est en cours
		if(m_fAngleY> -(angleActuel+angleRotation)){
			m_fAngleY-=angle;
			rotationPersonnage+=angle;
		}
		// ici il est terminé
		else {
			sensRotation=-sensRotation;
			virage=false;
	        alreadyRotated = false;
			angleActuel+=angleRotation;
			rotationPersonnage=angleActuel;
            indiceDepart=0;
			casTerrain=1;
		}
	}
	//virage à droite
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
            indiceDepart=0;
			casTerrain=1;
		}
	}
}

void TrackBallCamera::virageCamPassif(float degrees){
	float echelle = ((M_PI+angleActuel+angleRotation)-(M_PI))/(M_PI/2);
	float angle = 2*echelle*M_PI/180;
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
	m_fDistance+=delta*0.1;
	// limites
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
void TrackBallCamera::rotateUp(float degrees){}



glm::mat4 TrackBallCamera::getViewMatrix() const{
	glm::mat4 view=glm::mat4(1);
	view=glm::translate(view, glm::vec3(0,-1,-m_fDistance));
	view=glm::rotate(view, m_fAngleX, glm::vec3(1.0,0.0,0.0));
	view=glm::rotate(view, m_fAngleY, glm::vec3(0.0,1.0,0.0));
	return view;
}

void TrackBallCamera::moveLeft(float t){}

void TrackBallCamera::moveUp(float t){}

