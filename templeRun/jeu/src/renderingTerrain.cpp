#include "../include/renderingTerrain.hpp"

float largeur=1.5;
float vitesse=2.0;
float hauteur=2.0;
int numeroCase=0;
float positionLaterale=0.0;
float positionVerticale=0.0;
float x=largeur;
int score=0;

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

void drawTerrain(Program &program, std::vector<Model> &sols, std::deque<int> &tableauDeSols, std::vector<Model> &murs, 
int &numeroCase, glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix, float time){

         for(int i=0; i<tableauDeSols.size(); i++){            

            ModelMatrix = glm::mat4(1.0f);
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-3/2.0*largeur, largeur/2, (-largeur*(i+numeroCase)+time*vitesse))); // translate it down so it's at the center of the scene
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, largeur, largeur));	
            murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);

            ModelMatrix = glm::mat4(1.0f);
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(3/2.0*largeur, largeur/2, (-largeur*(i+numeroCase)+time*vitesse))); // translate it down so it's at the center of the scene
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, largeur, largeur));	
            murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);

            ModelMatrix = glm::mat4(1.0f);
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, (-largeur*(i+numeroCase)+time*vitesse)));
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur, 1.0f, largeur));
            sols[tableauDeSols[i]].Draw(program, ModelMatrix, VMatrix, ProjMatrix);
         }
         
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, (-largeur*numeroCase+time*vitesse)));
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur, 1.0f, largeur));
        if(ModelMatrix[3][2]>5){
            tableauDeSols.pop_front();
            tableauDeSols.push_back(numeroCase%3); //ici il faudra push_back(tableau[numeroCase + sizeTableau]) quand on recevra un tableau
            numeroCase++;
        }
}