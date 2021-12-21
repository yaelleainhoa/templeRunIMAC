#include "../include/renderingTerrain.hpp"
#include "../include/variablesGlobales.hpp"
#include "../include/rendering.hpp"

float positionLaterale=0.0;
float positionVerticale=0.0;
int score=0;
int indiceBoucle=0;
float angleActuel = 0;
float angleRotation =90.0f*M_PI/180.0;
int numCaseRot = 10;
float sensRotation = 1;
float phiStable = M_PI;
float distanceAuVirage=-1;
float angle = 0.0;
bool virage = false;
bool alreadyRotated = false;

int etat=DEBUT;

float valIncremCameraRotationUP = 0.5;
float valIncremCameraRotationDOWN = -0.5;

float valIncremCameraRotationLEFT = 0.5;
float valIncremCameraRotationRIGHT = -0.5;

float valIncremCameraFRONT = 0.5;
float valIncremCameraBACK = -0.5;
int mouvementHorizontalTranslation = 0;

float phi=M_PI;

//indice pour le vecteur de caméras : quand indiceCam = 0 c'est la TrackballCamera
// quand indiceCam = 1 c'est la FreeFly
int indiceCam = 0;

float distanceCase(const glm::mat4 ModelMatrix){
    glm::vec4 M = glm::normalize(ModelMatrix[3]);
    glm::vec3 pos = glm::vec3(M.x, M.y, M.z);
    return glm::distance(glm::vec3(0), pos);
}


float saut(){
    float l=largeur*2.0;
    float d=x*vitesse;
    if(d>l){
        return 0.0;
    }
    return (hauteur * d*(d-l)/(l/2*(l/2-l)));
};

void setTerrain(std::string path, std::vector<Model> &sols, std::vector<Model> &murs){
    Model parquet(path + "/assets/models/case/case.obj");
    Model parquet_trou_droite(path + "/assets/models/case_trou_droite/case_trou_droite.obj");
    Model parquet_trou_gauche(path + "/assets/models/case_trou_gauche/case_trou_gauche.obj");

    sols.push_back(parquet);
    sols.push_back(parquet_trou_droite);
    sols.push_back(parquet_trou_gauche);

    Model brique(path + "/assets/models/mur/mur.obj");
    murs.push_back(brique);
}

void destroyTerrain(std::vector<Model> &sols, std::vector<Model> &murs){
    for(int i=0; i<sols.size(); i++){
        sols[i].destroy();
    }
    for(int i=0; i<murs.size(); i++){
        murs[i].destroy();
    }
}


void drawCase(Program &program, std::vector<Model> &sols, 
                std::deque<int> &tableauDeSols, std::vector<Model> &murs, 
                glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,
                float translation, float signe,
                int index, int caseRotation){

    angle=90.0f*M_PI/180.0;

    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
    ModelMatrix=glm::rotate(ModelMatrix, signe*angle, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-3/2.0*largeur+(signe)*(caseRotation+1)*largeur, largeur/2, -largeur*(index+2*abs(signe)))); 
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, largeur, largeur));
    murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);

    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
    ModelMatrix=glm::rotate(ModelMatrix, signe*angle, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(3/2.0*largeur+(signe)*(caseRotation+1)*largeur, largeur/2, -largeur*(index+2*abs(signe)))); 
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, largeur, largeur));	
    
    murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);

    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
    ModelMatrix=glm::rotate(ModelMatrix, signe*angle, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3((signe)*(caseRotation+1)*largeur, 0.0f, -largeur*(index+2*abs(signe))));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur, 1.0f, largeur));
    
    sols[tableauDeSols[index]].Draw(program, ModelMatrix, VMatrix, ProjMatrix);
                    
}

void drawCaseDeTransition(Program &program,
                std::vector<Model> &murs, 
                glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,float translation, std::vector<Camera*> &listeCameras){
    //sert parce que je me sers de la texture du mur, quand
    //la case aura son propre modèle il n'y aura plus 
    //de rotation "angleSol"!!
    float angleSol=90.0f*M_PI/180.0;
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::rotate(ModelMatrix, angleSol, glm::vec3(0.0,0.0,1.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,indiceBoucle*translation));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, 0, -largeur*(numCaseRot+1))); // translate it down so it's at the center of the scene
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur*3, largeur*3, largeur*3));	
    
    // distance du joueur à la case de transition 
    distanceAuVirage = distanceCase(ModelMatrix);
    if(distanceAuVirage<largeur/2 && !virage && !alreadyRotated){
        std::cout << "Tu n'as pas été assez rapide ! tu aurais dû tourner avant " << std::endl;
        etat=MORT;
    }
    if(virage /*&& distanceAuVirage<0.95*/){
         //std::cout << "virage OK" << std::endl;
         alreadyRotated = true;
        listeCameras.at(indiceCam)->virageCam(angleRotation, VMatrix);
    }

    //ici ça ne sera pas un mur mais un sol!!
    murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);
}



void drawTerrain(Program &program, std::vector<Model> &sols, 
                std::deque<int> &tableauDeSols, std::vector<Model> &murs, 
                glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,
                float &angle,
                std::vector<Camera*> &listeCameras)
{  
    int boucleDeTranslation=50;
    indiceBoucle=(indiceBoucle+1)%(boucleDeTranslation+1);
    float translation=largeur/boucleDeTranslation;

    if(numCaseRot<=tableauDeSols.size()){

        for(int i=0; i<numCaseRot; i++){
            drawCase(program, sols, tableauDeSols, murs, ModelMatrix, VMatrix, ProjMatrix,
            indiceBoucle*translation, 0, i, numCaseRot);
        };
        drawCaseDeTransition(program, murs, ModelMatrix, VMatrix, ProjMatrix, translation, listeCameras);

        for(int i=0; i<tableauDeSols.size()-numCaseRot; i++){
            drawCase(program, sols, tableauDeSols, murs, ModelMatrix, VMatrix, ProjMatrix,
            indiceBoucle*translation, sensRotation, i, numCaseRot);
        }
    }

    else{
        for(int i=0; i<tableauDeSols.size(); i++){
            drawCase(program, sols, tableauDeSols, murs, ModelMatrix, VMatrix, ProjMatrix,
                    indiceBoucle*translation, 0, i, numCaseRot);
        };
    }

    if(boucleDeTranslation==indiceBoucle){
        tableauDeSols.pop_front();
        tableauDeSols.push_back(0); //ici il faudra push_back() selon le tableau quand on recevra un tableau
        numCaseRot--;
    }

    if(numCaseRot==-1){
        numCaseRot=20;
        angleActuel+=angleRotation;
        alreadyRotated = false;
        //sensRotation=-sensRotation;
    }
}