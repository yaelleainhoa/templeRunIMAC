#include "../include/freeflyCamera.hpp"


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

void FreeflyCamera::reset(){
	m_Position = glm::vec3(0.0f,hauteurInitFreeflyCamera,0.0f);
	m_fPhi = M_PI+angleActuel;
	m_fTheta = 0.0f;
	computeDirectionVectors();
}

void FreeflyCamera::moveLeft(float t){
	m_Position+=t*m_LeftVector;
	computeDirectionVectors();
};

  /***** PAS BESOIN DE MOVEFRONT AVEC LA FREEFLY ******/      
void FreeflyCamera::moveFront(float t){};

void FreeflyCamera::moveUp(float t){
	m_Position.y=t+hauteurInitFreeflyCamera;
	computeDirectionVectors();
}

void FreeflyCamera::virageCam(float degrees){
	float echelle = ((M_PI+angleActuel+angleRotation)-(M_PI))/(M_PI/2);
	float angle = 2*echelle*M_PI/180;	
	
	// virage à gauche
	if(sensRotation>0){
		if(m_fPhi<M_PI+angleActuel+angleRotation){
			m_fPhi+=angle;
			rotationPersonnage+=angle;
			computeDirectionVectors();
			VMatrix=getViewMatrix();
		}
		else{
			sensRotation=-sensRotation;
			virage=false;
	        alreadyRotated = false;
			angleActuel+=angleRotation;
			rotationPersonnage=angleActuel-90*M_PI/180.0;
            indiceDepart=0;
			casTerrain=1;
		}
	}
	//virage à droite
	else{
		if(m_fPhi>M_PI+angleActuel-angleRotation){
			m_fPhi-=angle;
			rotationPersonnage-=angle;
			computeDirectionVectors();
			VMatrix=getViewMatrix();
		}
		else{
			sensRotation=-sensRotation;
			virage=false;
	        alreadyRotated = false;
			angleActuel-=angleRotation;
			rotationPersonnage=angleActuel-90*M_PI/180.0;
            indiceDepart=0;
			casTerrain=1;
		}
	}

	computeDirectionVectors();
}

// la caméra prend le virage même lorsqu'elle est inactive
void FreeflyCamera::virageCamPassif(float degrees){
	float echelle = ((M_PI+angleActuel+angleRotation)-(M_PI))/(M_PI/2);
	float angle = 2*echelle*M_PI/180;
	if(sensRotation>0){
		if(m_fPhi<M_PI+angleActuel+angleRotation){
			m_fPhi+=angle;
			computeDirectionVectors();
		}
	}
	else{
		if(m_fPhi>M_PI+angleActuel-angleRotation){
			m_fPhi-=angle;
			computeDirectionVectors();
		}
	}
}

void FreeflyCamera::rotateLeft(float degrees){
	float radians = degrees*M_PI/180.0f;
	float limiteDroite = M_PI + angleActuel - M_PI/4;
	float limiteGauche = M_PI + angleActuel + M_PI/4;
	float newAngle = m_fPhi + radians;
	if(newAngle > limiteDroite && newAngle < limiteGauche){
		m_fPhi+=radians;
		computeDirectionVectors();
	}
};

void FreeflyCamera::rotateUp(float degrees){
	float radians = degrees*M_PI/180.0f;
	float limiteHaut =  M_PI/6;
	float limiteBas= - M_PI/6;
	float newAngle = m_fTheta + radians;
	if(newAngle > limiteBas && newAngle < limiteHaut){
		m_fTheta+=radians;
		computeDirectionVectors();
	}
};

glm::mat4 FreeflyCamera::getViewMatrix() const{
	glm::mat4 view=glm::lookAt(m_Position, m_Position+m_FrontVector, m_UpVector);
	return view;
}
