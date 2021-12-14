#include "../include/renderingTerrain.hpp"
#include "../include/variablesGlobales.hpp"

int numeroCase=0;
float positionLaterale=0.0;
float positionVerticale=0.0;
int score=0;
float decalageSolX = 0.0;
float decalageSolZ = 0.0;
glm::vec3 decalageMurD(0.0);
glm::vec3 decalageMurG(0.0);
float scaleX = 1.0f;

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

void drawTerrain(Program &program, std::vector<Model> &sols, 
                std::deque<int> &tableauDeSols, std::vector<Model> &murs, 
                int &numeroCase, glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix, 
                float time,
                bool &virage, 
                float &angle,
                float phiStable,
                std::vector<Camera*> &listeCameras)
{  
    int numCaseRot = 50;
        for(int i=0; i<tableauDeSols.size(); i++){    
            if(numeroCase+i>numCaseRot){
            

                angle=90.0*M_PI/180;

                scaleX = 1.0f;
                
                decalageSolX = -2.0*largeur;
                decalageSolZ = 2*largeur;
               // decalageMurG = glm::vec3(-2*largeur,0,-largeur);
              //  decalageMurD = glm::vec3(2*largeur,0,-largeur);
                if(virage==true){
                std::cout << "virage" << std::endl;
                listeCameras.at(1)->virageCam(angle, VMatrix,virage, phiStable);
                //VMatrix=listeCameras.at(1)->getViewMatrix();
                // virage=false;
            }
            }
            else if(numeroCase+i>numCaseRot-3){
                angle = 0*M_PI/180;
                scaleX = 3.0f;

                decalageSolX = 0;
                decalageSolZ = 0; 
            }
            else {
                angle = 0*M_PI/180;
                decalageSolX = 0;
                decalageSolZ = 0; 
            }
            
        
            ModelMatrix = glm::mat4(1.0f);
            // ModelMatrix = glm::translate(ModelMatrix, decalageMurG);
            ModelMatrix=glm::rotate(ModelMatrix, angle, glm::vec3(0.0,1.0,0.0));
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-3/2.0*largeur, largeur/2, (-largeur*(i+numeroCase)+time*vitesse))); // translate it down so it's at the center of the scene
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, largeur, largeur));	
            
            //murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);

            ModelMatrix = glm::mat4(1.0f);
            // ModelMatrix = glm::translate(ModelMatrix, decalageMurD);
            ModelMatrix=glm::rotate(ModelMatrix, angle, glm::vec3(0.0,1.0,0.0));
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(3/2.0*largeur, largeur/2, (-largeur*(i+numeroCase)+time*vitesse))); // translate it down so it's at the center of the scene
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, largeur, largeur));	
            
            //murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);

            ModelMatrix = glm::mat4(1.0f);
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(decalageSolX, 0, decalageSolZ));
            ModelMatrix=glm::rotate(ModelMatrix, angle, glm::vec3(0.0,1.0,0.0));
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, (-largeur*(i+numeroCase)+time*vitesse)));
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur, 1.0f, largeur));
            
            sols[tableauDeSols[i]].Draw(program, ModelMatrix, VMatrix, ProjMatrix);
        
        }

        //if(virage) angle=-90.0; 
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, (-largeur*numeroCase+time*vitesse)));
        //ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur, 1.0f, largeur));
        //ModelMatrix=glm::rotate(ModelMatrix, angle, glm::vec3(0.0,1.0,0.0));
        if(ModelMatrix[3][2]>5){
            tableauDeSols.pop_front();
            tableauDeSols.push_back(0); //ici il faudra push_back(tableau[numeroCase + sizeTableau]) quand on recevra un tableau
            numeroCase++;
        }
}