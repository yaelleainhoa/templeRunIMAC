#include "../include/renderingTerrain.hpp"
#include "../include/variablesGlobales.hpp"

float positionLaterale=0.0;
float positionVerticale=0.0;
int score=0;
int indiceBoucle=0;
float angleActuel = 0;
float angleRotation = 90.0f*M_PI/180.0;
int numCaseRot = 10;
float sensRotation = 1;


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

                
    float angle=90.0f*M_PI/180.0;

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
                glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,float translation){
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

    //ici ça ne sera pas un mur mais un sol!!
    murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);
}



void drawTerrain(Program &program, std::vector<Model> &sols, 
                std::deque<int> &tableauDeSols, std::vector<Model> &murs, 
                glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix, 
                bool &virage, 
                float &angle,
                std::vector<Camera*> &listeCameras)

{  
    int boucleDeTranslation=50;
    indiceBoucle=(indiceBoucle+1)%(boucleDeTranslation+1);
    float translation=largeur/boucleDeTranslation;

    for(int i=0; i<numCaseRot; i++){
        drawCase(program, sols, tableauDeSols, murs, ModelMatrix, VMatrix, ProjMatrix,
                indiceBoucle*translation, 0, i, numCaseRot);
    };

    drawCaseDeTransition(program, murs, ModelMatrix, VMatrix, ProjMatrix, translation);

    for(int i=0; i<tableauDeSols.size()-numCaseRot; i++){
        drawCase(program, sols, tableauDeSols, murs, ModelMatrix, VMatrix, ProjMatrix,
                indiceBoucle*translation, sensRotation, i, numCaseRot);
    };

    if(boucleDeTranslation==indiceBoucle){
        tableauDeSols.pop_front();
        tableauDeSols.push_back(0); //ici il faudra push_back() selon le tableau quand on recevra un tableau
        numCaseRot--;
    }

    if(numCaseRot==-1){
        numCaseRot=10;
        angleActuel+=angleRotation;
        //sensRotation=-sensRotation;
    }
}