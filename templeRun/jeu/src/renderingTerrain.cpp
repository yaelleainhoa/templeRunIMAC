#include "../include/renderingTerrain.hpp"
#include "../include/variablesGlobales.hpp"

float positionLaterale=0.0;
float positionVerticale=0.0;
int score=0;
int indiceBoucle=0;
float angleActuel = 0;
float angleRotation = 90.0f*M_PI/180.0;
int numCaseRot = 20;
float sensRotation = 1;

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
}

void setTerrain(std::string path, std::vector<Model> &sols, std::vector<Model> &murs){
    Model parquet(path + "/assets/models/sol/sol.obj");
    Model parquet_trou_droite(path + "/assets/models/sol/sol.obj");
    Model parquet_trou_gauche(path + "/assets/models/sol/sol.obj");

    sols.push_back(parquet);
    sols.push_back(parquet_trou_droite);
    sols.push_back(parquet_trou_gauche);

    Model brique(path + "/assets/models/trottoir/trottoir.obj");
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

void drawObject(Program &program, float posX, float poxY,
                glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,
                std::vector<Model> &typeObjet, int idText, float translation, float signe, int caseRotation,
                int index, float scaleX=1.0f, float scaleY=1.0f, float scaleZ=1.0f, float rotationObjet=0.0f)
{
    float angle=90.0f*M_PI/180.0;

    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
    ModelMatrix=glm::rotate(ModelMatrix, signe*angle, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3((signe)*(caseRotation+1)*largeur, 0.0f, -largeur*(index+2*abs(signe))));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(largeur*posX,poxY*largeur, 0));
    ModelMatrix=glm::rotate(ModelMatrix, rotationObjet, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaleX, scaleY, scaleZ));

    typeObjet[idText].Draw(program, ModelMatrix, VMatrix, ProjMatrix);
}



//CODE PAS TOUT A FAIT PRET, A TESTER AVEC LES FONCTIONS DE LISA
/*
void drawObjetssCase(Program &program, const ssCase ssCaseObjets, std::vector<Model> &pieces,
                std::vector<Model> &obstacles,
                glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,
                float translation, float signe,
                int index, int caseRotation, int cas){

    if(!ssCaseObjets.empty()){
        for(int i=0; i<ssCaseObjets.objets.size(); i++){
            //si c'est une piece, la dessiner au bon endroit dans la map + bien placé sur sa case
            //pour l'instant, ne prend pas en compte le cas où la piece a été prise
            if(caseObjets.ssCaseGauche.objets[i].getType()==1){
                drawObject(program, cas, ssCaseObjets.objets[i].getMvt(),
                ModelMatrix, VMatrix, ProjMatrix, pieces, ssCaseObjets.objets[i].getIdTexture(), 
                translation, signe, caseRotation, index);
            }

            //si ce n'est pas une piece, il faut faire attention à la taille de l'objet
            //si l'obstacle est de taille 1, on le dessine sur la case directement
            else if(ssCaseObjets.objets[i].taille==1){
                drawObject(program, cas, ssCaseObjets.objets[i].getMvt(),
                ModelMatrix, VMatrix, ProjMatrix, pieces, ssCaseObjets.objets[i].getIdTexture(), 
                translation, signe, caseRotation, index);
            }

            //si l'obstacle est de taille 2, on le dessine entre les deux cases de gauche si on est dans 
            //la ssCaseGauche (cas -1) et entre les deux cases de droite dans la ssCaseDroite (cas 1)
            //dans le cas -1 on dessine à -1/2 et dans le cas 1 ) 1/2 
            else if(ssCaseObjets.objets[i].taille==2 && cas!=0){
                drawObject(program, 1/2.0 * cas, caseObjets.ssCaseGauche.objets[i].getMvt(),
                ModelMatrix, VMatrix, ProjMatrix, pieces, ssCaseObjets.objets[i].getIdTexture(), 
                translation, signe, caseRotation, index);
            }

            //si l'obstacle est de taille 3, on le dessine au milieu dans tous les cas
            //pour éviter les doublons, on ne dessine que dans le cas 1
            else if(ssCaseObjets.objets[i].taille==3 && cas==-1){
                drawObject(program, 0, ssCaseObjets.objets[i].getMvt(),
                ModelMatrix, VMatrix, ProjMatrix, pieces, ssCaseObjets.objets[i].getIdTexture(), 
                translation, signe, caseRotation, index);
            }
        }
    }
}

void drawObjetCase(Program &program, const Case caseObjets, std::vector<Model> &pieces,
                std::vector<Model> &obstacles,
                glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,
                float translation, float signe,
                int index, int caseRotation){

    //on dessine les objets de la case de gauche (cas -1)
    drawObjetssCase(program, caseObjets.ssCaseGauche, pieces, obstacles, ModelMatrix, VMatrix, ProjMatrix,
                        translation, signe, index, caseRotation, -1);

    //on dessine les objets de la case du milieu (cas 0)
    drawObjetssCase(program, caseObjets.ssCaseMilieu, pieces, obstacles, ModelMatrix, VMatrix, ProjMatrix,
                        translation, signe, index, caseRotation, 0);

    //on dessine les objets de la case de droite (cas 1)
    drawObjetssCase(program, caseObjets.ssCaseDroite, pieces, obstacles, ModelMatrix, VMatrix, ProjMatrix,
                        translation, signe, index, caseRotation, 1);

}
*/


void drawCase(Program &program, std::vector<Model> &sols, 
                std::deque<int> &tableauDeSols, std::vector<Model> &murs, 
                glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,
                float translation, float signe,
                int index, int caseRotation){

    //on dessine d'abord les murs
    drawObject(program, 4/2.0, 0, ModelMatrix, VMatrix, ProjMatrix, 
                murs, 0, translation, signe, caseRotation, index, 1/2.0, 1/2.0, largeur/2.0);      

    drawObject(program, -4/2.0, 0, ModelMatrix, VMatrix, ProjMatrix, 
                murs, 0, translation, signe, caseRotation, index, 1/2.0, 1/2.0, largeur/2.0);      

    //on dessine le sol
    drawObject(program, 0, 0.0f, ModelMatrix, VMatrix, ProjMatrix, 
                sols, tableauDeSols[index], translation, signe, caseRotation, index, largeur/2.0, 1/2.0, largeur/2.0);                      
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

    //à voir s'il faut mettre ça au début ou à la fin de la fonction
    //ici, on regarde dès que la case la + proche est très proche si le joueur meurt ou attrape une pièce
    // ModelMatrix = glm::mat4(1.0f);
    // ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    // ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation-largeur/2));
    // if(distanceCase(ModelMatrix)<1){
    //     //appeler la fonction test!
    //     murs[0].Draw(program, ModelMatrix, VMatrix, ProjMatrix);
    //     //std::cout << "la case est prete pour le test! : "<<indiceBoucle<<std::endl;
    // }
    if(numCaseRot<=tableauDeSols.size()){

        for(int i=0; i<numCaseRot; i++){
            drawCase(program, sols, tableauDeSols, murs, ModelMatrix, VMatrix, ProjMatrix,
                    indiceBoucle*translation, 0, i, numCaseRot);

            // drawObjetCase(program, cheminVisible[i+indiceChemin], pieces,
            //     obstacles, ModelMatrix, VMatrix, ProjMatrix,
            //     translation, 0, i, numCaseRot);
        };
        //drawCaseDeTransition(program, murs, ModelMatrix, VMatrix, ProjMatrix, translation);

        for(int i=0; i<tableauDeSols.size()-numCaseRot; i++){
            drawCase(program, sols, tableauDeSols, murs, ModelMatrix, VMatrix, ProjMatrix,
                    indiceBoucle*translation, sensRotation, i, numCaseRot);

            // drawObjetCase(program, cheminVisible[i+indiceChemin], pieces,
            //     obstacles, ModelMatrix, VMatrix, ProjMatrix,
            //     translation, sensRotation, i, numCaseRot);
        }
    }

    else{
        for(int i=0; i<tableauDeSols.size(); i++){
            drawCase(program, sols, tableauDeSols, murs, ModelMatrix, VMatrix, ProjMatrix,
                    indiceBoucle*translation, 0, i, numCaseRot);

            // drawObjetCase(program, cheminVisible[i+indiceChemin], pieces,
            //     obstacles, ModelMatrix, VMatrix, ProjMatrix,
            //     translation, 0, i, numCaseRot);
        };
    }

    if(boucleDeTranslation==indiceBoucle){
        //normalement à la place d'ici on va juste stocker l'indice du tableau de Lisa et ici
        //incrémenter l'indice pour dit qui est le nouveau premier de la liste :)
        //ainsi dans les lignes précédentes on ne dessine pas à l'incidice i mais i+indiceChemin
        //tableauDeSols.size() correspondra à la taille du chemin visible
        //et tableauDeSols[i] pour la texture du sol sera plutot cheminVisible[indiceChemin+i].idText
        tableauDeSols.pop_front();
        tableauDeSols.push_back(0); 
        numCaseRot--;
    }

    if(numCaseRot==-1){
        numCaseRot=30;
        angleActuel+=angleRotation;
        //sensRotation=-sensRotation;
    }
}