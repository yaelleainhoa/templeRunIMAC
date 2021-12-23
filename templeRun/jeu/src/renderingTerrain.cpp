#include "../include/renderingTerrain.hpp"
#include "../include/variablesGlobales.hpp"
#include "../include/rendering.hpp"

float distanceCase(const glm::mat4 Case){
    glm::vec4 M = glm::normalize(Case[3]);
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

float baisser(){
    float l=largeur*2.0;
    float d=xBaisse*vitesse;
    if(d>l){
        return 1;
    }
    return 0.2;
}

void setTerrain(std::string path, std::vector<Model> &sols, std::vector<Model> &murs){
    Model parquet(path + "/assets/models/sol/sol.obj");
    Model parquet_trou_droite(path + "/assets/models/case/case.obj");
    Model parquet_trou_gauche(path + "/assets/models/case_trou_droite/case_trou_droite.obj");

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
                std::vector<Model> &typeObjet, int idText, float translation=0, float signe=0, int caseRotation=0,
                int index=0, float scaleX=1.0f, float scaleY=1.0f, float scaleZ=1.0f, float rotationObjet=0.0f)
{
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
    ModelMatrix=glm::rotate(ModelMatrix, signe*angleRotation, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3((signe)*(caseRotation+1)*largeur, 0.0f, -largeur*(index+2*abs(signe))));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(largeur*posX,poxY*largeur, 0));
    ModelMatrix=glm::rotate(ModelMatrix, rotationObjet, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaleX, scaleY, scaleZ));

    typeObjet[idText].Draw(program);
}

void drawPersonnage(Program &program, float posX, float poxY,
                std::vector<Model> &typeObjet, int idText,  float scaleX, float scaleY, float scaleZ)
{
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, rotationPersonnage, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,poxY*largeur, -largeur*posX));
    // ModelMatrix=glm::rotate(ModelMatrix, rotationPersonnage, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaleX, scaleY, scaleZ));

    typeObjet[idText].Draw(program);
}



//CODE PAS TOUT A FAIT PRET, A TESTER AVEC LES FONCTIONS DE LISA
/*
void drawObjetssCase(Program &program, const ssCase ssCaseObjets, std::vector<Model> &pieces,
                std::vector<Model> &obstacles,
                float translation, float signe,
                int index, int caseRotation, int cas){

    if(!ssCaseObjets.empty()){
        for(int i=0; i<ssCaseObjets.objets.size(); i++){
            //si c'est une piece, la dessiner au bon endroit dans la map + bien placé sur sa case
            //pour l'instant, ne prend pas en compte le cas où la piece a été prise
            if(caseObjets.ssCaseGauche.objets[i].getType()==1){
                drawObject(program, cas, ssCaseObjets.objets[i].getMvt(),
                pieces, ssCaseObjets.objets[i].getIdTexture(), 
                translation, signe, caseRotation, index);
            }

            //si ce n'est pas une piece, il faut faire attention à la taille de l'objet
            //si l'obstacle est de taille 1, on le dessine sur la case directement
            else if(ssCaseObjets.objets[i].taille==1){
                drawObject(program, cas, ssCaseObjets.objets[i].getMvt(),
                pieces, ssCaseObjets.objets[i].getIdTexture(), 
                translation, signe, caseRotation, index);
            }

            //si l'obstacle est de taille 2, on le dessine entre les deux cases de gauche si on est dans 
            //la ssCaseGauche (cas -1) et entre les deux cases de droite dans la ssCaseDroite (cas 1)
            //dans le cas -1 on dessine à -1/2 et dans le cas 1 ) 1/2 
            else if(ssCaseObjets.objets[i].taille==2 && cas!=0){
                drawObject(program, 1/2.0 * cas, caseObjets.ssCaseGauche.objets[i].getMvt(),
                pieces, ssCaseObjets.objets[i].getIdTexture(), 
                translation, signe, caseRotation, index);
            }

            //si l'obstacle est de taille 3, on le dessine au milieu dans tous les cas
            //pour éviter les doublons, on ne dessine que dans le cas 1
            else if(ssCaseObjets.objets[i].taille==3 && cas==-1){
                drawObject(program, 0, ssCaseObjets.objets[i].getMvt(),
                pieces, ssCaseObjets.objets[i].getIdTexture(), 
                translation, signe, caseRotation, index);
            }
        }
    }
}

void drawObjetCase(Program &program, const Case caseObjets, std::vector<Model> &pieces,
                std::vector<Model> &obstacles,
                float translation, float signe,
                int index, int caseRotation){

    //on dessine les objets de la case de gauche (cas -1)
    drawObjetssCase(program, caseObjets.ssCaseGauche, pieces, obstacles,
                        translation, signe, index, caseRotation, -1);

    //on dessine les objets de la case du milieu (cas 0)
    drawObjetssCase(program, caseObjets.ssCaseMilieu, pieces, obstacles,
                        translation, signe, index, caseRotation, 0);

    //on dessine les objets de la case de droite (cas 1)
    drawObjetssCase(program, caseObjets.ssCaseDroite, pieces, obstacles,
                        translation, signe, index, caseRotation, 1);

}
*/


void drawCase(Program &program, std::vector<Model> &sols, 
                std::deque<int> &tableauDeSols, std::vector<Model> &murs, 
                float translation, float signe,
                int index, int caseRotation, int indiceTexture){

    //on dessine d'abord les murs
    drawObject(program, 4/2.0, 0, 
                murs, 0, translation, signe, caseRotation, index, 1/2.0, 1/2.0, largeur/2.0);  
    // if(index==5){
    //     lumScenePonct.updateLumiereAt(ModelMatrix[3], 0);   
    // }
    drawObject(program, -4/2.0, 0, 
                murs, 0, translation, signe, caseRotation, index, 1/2.0, 1/2.0, largeur/2.0);   
    // if(index==5){
    //     lumScenePonct.updateLumiereAt(ModelMatrix[3], 1);   
    // }
    //on dessine le sol
    drawObject(program, 0, 0.0f, 
                sols, tableauDeSols[indiceTexture], translation, signe, caseRotation, index, largeur/2.0, 1/2.0, largeur/2.0);                      
}

void drawCaseDeTransition(Program &program,
                std::vector<Model> &murs, 
                float translation){
    //sert parce que je me sers de la texture du mur, quand
    //la case aura son propre modèle il n'y aura plus 
    //de rotation "angleSol"!!
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,indiceBoucle*translation));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, 0, -largeur*(numCaseRot-casesDerrierePersonnage+1))); // translate it down so it's at the center of the scene
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(5/2.0, 1/4.0, 5/2.0));	
    
    // distance du joueur à la case de transition 
    distanceAuVirage = distanceCase(ModelMatrix);
    if(distanceAuVirage<largeur/2 && !virage && !alreadyRotated){
        std::cout << "Tu n'as pas été assez rapide ! tu aurais dû tourner avant " << std::endl;
        etat=MORT;
    }
    if(distanceAuVirage<largeur/2 && sensVirage!=sensRotation){
        std::cout << "Tu t'es trompé de sens.." << std::endl;
        //etat=MORT;
    }
    if(virage /*&& distanceAuVirage<0.95*/){
        // std::cout << "virage OK"<<std::endl;
        alreadyRotated = true;
        //std::cout<<"appel de fonction"<<std::endl;
        listeCameras.at(indiceCam)->virageCam(angleRotation);
        listeCameras.at((indiceCam+1)%2)->virageCamPassif(angleRotation);
    }

    //ici ça ne sera pas un mur mais un sol!!
    murs[0].Draw(program);
}



void drawTerrain(Program &program, std::vector<Model> &sols, 
                std::deque<int> &tableauDeSols, std::vector<Model> &murs, 
                float &angle)
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
    //     murs[0].Draw(program);
    //     //std::cout << "la case est prete pour le test! : "<<indiceBoucle<<std::endl;
    // }
    if(casTerrain==0){
        for(int i=0; i<numCaseRot; i++){
            drawCase(program, sols, tableauDeSols, murs, 
            indiceBoucle*translation, 0, i-casesDerrierePersonnage, numCaseRot, i);
        };
        drawCaseDeTransition(program, murs, translation);

        for(int i=0; i<tableauDeSols.size()-numCaseRot; i++){
            drawCase(program, sols, tableauDeSols, murs, 
            indiceBoucle*translation, sensRotation, i, numCaseRot-casesDerrierePersonnage, i+numCaseRot);
        }
    }

    if(casTerrain==1){
        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
        ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,indiceBoucle*translation));
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, 0, -largeur*(numCaseRot-casesDerrierePersonnage+1))); // translate it down so it's at the center of the scene
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(5/2.0, 1/4.0, 5/2.0));	
        murs[0].Draw(program);

        for(int i=0; i<tableauDeSols.size()-casesDerrierePersonnage; i++){
            drawCase(program, sols, tableauDeSols, murs, 
                    indiceBoucle*translation, 0, i+numCaseRot-casesDerrierePersonnage+3, numCaseRot, i+numCaseRot);

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
        tableauDeSols.push_back(indiceBoucle%3); 
        numCaseRot--;
    }

    if(numCaseRot==-casesDerrierePersonnage){
        casTerrain=0;
        numCaseRot=20;
    }
}