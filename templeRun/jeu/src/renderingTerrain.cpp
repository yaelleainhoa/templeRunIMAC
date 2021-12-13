#include "../include/renderingTerrain.hpp"
#include "../include/variablesGlobales.hpp"

int numeroCase=0;
float positionLaterale=0.0;
float positionVerticale=0.0;
int score=0;
int indiceBoucle=0;
float angleActuel = 0;
float angleRotation = 0;
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
                int &numeroCase, glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,
                float translation, float signe,
                int index, int caseRotation){

                
    float angle=90.0f*M_PI/180.0;

    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
    ModelMatrix=glm::rotate(ModelMatrix, signe*angle, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-3/2.0*largeur+(signe)*(caseRotation+1)*largeur, largeur/2, -largeur*(index+2*abs(signe)))); 
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, largeur, largeur));
    murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);

    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
    ModelMatrix=glm::rotate(ModelMatrix, signe*angle, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(3/2.0*largeur+(signe)*(caseRotation+1)*largeur, largeur/2, -largeur*(index+2*abs(signe)))); 
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, largeur, largeur));	
    
    murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);

    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
    ModelMatrix=glm::rotate(ModelMatrix, signe*angle, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3((signe)*(caseRotation+1)*largeur, 0.0f, -largeur*(index+2*abs(signe))));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur, 1.0f, largeur));
    
    sols[tableauDeSols[index]].Draw(program, ModelMatrix, VMatrix, ProjMatrix);
                    
}


void drawTerrain(Program &program, std::vector<Model> &sols, 
                std::deque<int> &tableauDeSols, std::vector<Model> &murs, 
                int &numeroCase, glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix, 
                bool &virage, 
                float &angle,
                std::vector<Camera*> &listeCameras)

{  
    int boucleDeTranslation=50;
    indiceBoucle=(indiceBoucle+1)%(boucleDeTranslation+1);
    float translation=largeur/boucleDeTranslation;

    for(int i=0; i<numCaseRot; i++){
        drawCase(program, sols, tableauDeSols, murs, numeroCase, ModelMatrix, VMatrix, ProjMatrix,
                indiceBoucle*translation, 0, i, numCaseRot);
    };

    float angleSol=90.0f*M_PI/180.0;
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleSol, glm::vec3(0.0,0.0,1.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,indiceBoucle*translation));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, 0, -largeur*(numCaseRot+1))); // translate it down so it's at the center of the scene
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur*3, largeur*3, largeur*3));	

    murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);

    for(int i=0; i<tableauDeSols.size()-numCaseRot; i++){
        drawCase(program, sols, tableauDeSols, murs, numeroCase, ModelMatrix, VMatrix, ProjMatrix,
                indiceBoucle*translation, sensRotation, i, numCaseRot);
    };

    if(boucleDeTranslation==indiceBoucle){
        tableauDeSols.pop_front();
        tableauDeSols.push_back(0); //ici il faudra push_back(tableau[numeroCase + sizeTableau]) quand on recevra un tableau
        numeroCase++;
        numCaseRot--;
    }

    if(numCaseRot==-1){
        numCaseRot=10;
        sensRotation=-1;
    }
}

// void drawTerrain(Program &program, std::vector<Model> &sols, 
//                 std::deque<int> &tableauDeSols, std::vector<Model> &murs, 
//                 int &numeroCase, glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix, 
//                 float time,
//                 bool &virage, 
//                 float &angle,
//                 std::vector<Camera*> &listeCameras)
// {  int numCaseRot = 17;
//          for(int i=0; i<tableauDeSols.size(); i++){    
//              if(numeroCase+i>numCaseRot){
//                  angle=100.0;
//                  if(virage==true){
//                  std::cout << "virage" << std::endl;
//                     listeCameras.at(1)->virageCam(angle);
//                     VMatrix=listeCameras.at(1)->getViewMatrix();
//                     virage=false;
//                 }
//              }
//              else angle = 0;
            
//             ModelMatrix = glm::mat4(1.0f);
//             ModelMatrix=glm::rotate(ModelMatrix, angle, glm::vec3(0.0,1.0,0.0));
//             ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-3/2.0*largeur, largeur/2, (-largeur*(i+numeroCase)+time*vitesse))); // translate it down so it's at the center of the scene
//             ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, largeur, largeur));	
            
//             murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);

//             ModelMatrix = glm::mat4(1.0f);
//             ModelMatrix=glm::rotate(ModelMatrix, angle, glm::vec3(0.0,1.0,0.0));
//             ModelMatrix = glm::translate(ModelMatrix, glm::vec3(3/2.0*largeur, largeur/2, (-largeur*(i+numeroCase)+time*vitesse))); // translate it down so it's at the center of the scene
//             ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, largeur, largeur));	
            
//             murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);

//             ModelMatrix = glm::mat4(1.0f);
//             ModelMatrix=glm::rotate(ModelMatrix, angle, glm::vec3(0.0,1.0,0.0));
//             ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, (-largeur*(i+numeroCase)+time*vitesse)));
//             ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur, 1.0f, largeur));
            
//             sols[tableauDeSols[i]].Draw(program, ModelMatrix, VMatrix, ProjMatrix);
            
//          }

//         //if(virage) angle=-90.0; 
//         ModelMatrix = glm::mat4(1.0f);
//         ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, (-largeur*numeroCase+time*vitesse)));
//         //ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur, 1.0f, largeur));
//         //ModelMatrix=glm::rotate(ModelMatrix, angle, glm::vec3(0.0,1.0,0.0));
//         if(ModelMatrix[3][2]>5){
//             tableauDeSols.pop_front();
//             tableauDeSols.push_back(numeroCase%3); //ici il faudra push_back(tableau[numeroCase + sizeTableau]) quand on recevra un tableau
//             numeroCase++;
//         }
// }