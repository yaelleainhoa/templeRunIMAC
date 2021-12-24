#include "../include/renderingTerrain.hpp"

float distanceCase(const glm::mat4 &Case){
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

void setTerrain(std::string path, std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, std::vector<Model> &obstacles){
    Model sol(path + "/assets/models/sol/sol.obj");
    Model sol_obstacle_droite(path + "/assets/models/sol_obstacle_droite/sol_droite.obj");
    Model sol_obstacle_gauche(path + "/assets/models/sol_obstacle_gauche/sol_gauche.obj");
    Model sol_rotation(path + "/assets/models/sol_rotation/sol_rotation.obj");

    sols.push_back(sol_rotation);
    sols.push_back(sol);
    sols.push_back(sol_obstacle_droite);
    sols.push_back(sol_obstacle_gauche);

    Model trottoir(path + "/assets/models/trottoir/trottoir.obj");
    Model buisson(path + "/assets/models/buisson/buisson.obj");
    Model lampadaire(path + "/assets/models/lampadaire/lampadaire.obj");

    murs.push_back(trottoir);
    murs.push_back(buisson);
    murs.push_back(lampadaire);

    Model biberon(path + "/assets/models/biberon/biberon.obj");
    Model tetine(path + "/assets/models/tetine/tetine.obj");
    Model doudou(path + "/assets/models/doudou/licorne.obj");
    pieces.push_back(biberon);
    pieces.push_back(tetine);
    pieces.push_back(doudou);

    Model tancarville(path + "/assets/models/tancarville/tancarville.obj");
    Model velo(path + "/assets/models/velo/bicycle.obj");
    obstacles.push_back(tancarville);
    obstacles.push_back(velo);
}

void destroyTerrain(std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, std::vector<Model> &obstacles){
    for(int i=0; i<sols.size(); i++){
        sols[i].destroy();
    }
    for(int i=0; i<murs.size(); i++){
        murs[i].destroy();
    }
    for(int i=0; i<pieces.size(); i++){
        pieces[i].destroy();
    }
    for(int i=0; i<obstacles.size(); i++){
        obstacles[i].destroy();
    }
}

void drawObject(Program &program, std::vector<Model> &typeObjet,
                int idText,
                float posX, float poxY, int posZ,
                float translation, float signe, int caseRotation, float rotationObjet,
                float scaleX, float scaleY, float scaleZ)
{
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
    ModelMatrix=glm::rotate(ModelMatrix, signe*angleRotation, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3((signe)*(caseRotation+1)*largeur, 0.0f, -largeur*(posZ+2*abs(signe))));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(largeur*posX,poxY*largeur, 0));
    ModelMatrix=glm::rotate(ModelMatrix, rotationObjet, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaleX, scaleY, scaleZ));

    typeObjet[idText].Draw(program);
}

void drawPersonnage(Program &program, std::vector<Model> &typeObjet, int idText,  
                    float rotationModel,
                    float scaleX, float scaleY, float scaleZ,
                    float posX, float poxY, float posZ)
{
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, rotationPersonnage, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(largeur*posX,poxY*largeur, posZ));
    ModelMatrix=glm::rotate(ModelMatrix,rotationModel, glm::vec3(0.0,1.0,0.0));
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
                drawObject(program, pieces, 
                            ssCaseObjets.objets[i].getIdTexture(),
                            cas, ssCaseObjets.objets[i].getMvt(), index??
                            translation, signe, caseRotation, 0,
                            1, 1, 1);
            }

            //si ce n'est pas une piece, il faut faire attention à la taille de l'objet
            //si l'obstacle est de taille 1, on le dessine sur la case directement
            else if(ssCaseObjets.objets[i].taille==1){
                drawObject(program, obstacles, 
                            ssCaseObjets.objets[i].getIdTexture(), //ici peut être la texture facile comme seulement velo??
                            cas, ssCaseObjets.objets[i].getMvt(), index?? //mvt taille 1 seulemnt  0?
                            translation, signe, caseRotation, 0,
                            1, 1, 1);
            }

            // //si l'obstacle est de taille 2, on le dessine entre les deux cases de gauche si on est dans 
            // //la ssCaseGauche (cas -1) et entre les deux cases de droite dans la ssCaseDroite (cas 1)
            // //dans le cas -1 on dessine à -1/2 et dans le cas 1 ) 1/2 
            // else if(ssCaseObjets.objets[i].taille==2 && cas!=0){
            //     drawObject(program, 1/2.0 * cas, caseObjets.ssCaseGauche.objets[i].getMvt(),
            //     pieces, ssCaseObjets.objets[i].getIdTexture(), 
            //     translation, signe, caseRotation, index);
            // }

            //si l'obstacle est de taille 3, on le dessine au milieu dans tous les cas
            //pour éviter les doublons, on ne dessine que dans le cas 1
            else if(ssCaseObjets.objets[i].taille==3 && cas==-1){
                drawObject(program, obstacles, 
                            ssCaseObjets.objets[i].getIdTexture(), //pareil, je connais la texture en fait (?)
                            0, ssCaseObjets.objets[i].getMvt(), index?? //pareil mvt no need a priori
                            translation, signe, caseRotation, 0,
                            1, 1, 1);
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
                int i, int caseRotation, int indiceTexture){


    //on dessine d'abord les murs
    drawObject(program, murs, 0,
                (3/2.0*largeur), 0, i,
                translation, signe, caseRotation, 0,
                1/2.0, 1/2.0, largeur/2.0);
    drawObject(program, murs, 1,
                (4/2.0*largeur), 0, i,
                translation, signe, caseRotation, 0,
                1/2.0, 1/2.0, largeur/2.0);
    drawObject(program, murs, 0,
                -(3/2.0*largeur), 0, i,
                translation, signe, caseRotation, 0,
                1/2.0, 1/2.0, largeur/2.0);
    drawObject(program, murs, 1,
                -(4/2.0*largeur), 0, i,
                translation, signe, caseRotation, 0,
                1/2.0, 1/2.0, largeur/2.0);
    
    //on dessine le sol
    drawObject(program, sols, tableauDeSols[indiceTexture],
                0, 0, i,
                translation, signe, caseRotation, 0,
                largeur, 1, largeur);
                   
}

void tracerLampadaires(Program &program, std::vector<Model> &murs, 
                    float translation, float signe,
                    int i, int caseRotation, int indexCoupleLampadaire){

    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
    ModelMatrix=glm::rotate(ModelMatrix, signe*angleRotation, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3((signe)*(caseRotation+1)*largeur, 0.0f, -largeur*(i+2*abs(signe))));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(-largeur*largeur*3/2.0,1/4.0*largeur, 0));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1/2.0, 1/2.0, 1/2.0));

    murs[2].Draw(program);

    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,2,0));
    lumScenePonct.changePositionAt(indexCoupleLampadaire, ModelMatrix[3]);

    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
    ModelMatrix=glm::rotate(ModelMatrix, signe*angleRotation, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3((signe)*(caseRotation+1)*largeur, 0.0f, -largeur*(i+2*abs(signe))));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(+largeur*largeur*3/2.0,1/4.0*largeur, 0));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1/2.0, 1/2.0, 1/2.0));

    murs[2].Draw(program);

    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,2,0));
    lumScenePonct.changePositionAt(indexCoupleLampadaire+1, ModelMatrix[3]);

}

void drawCaseDeTransitionVirage(Program &program,
                std::vector<Model> &sols, 
                float translation){
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,indiceBoucle*translation));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, 0, -largeur*(numCaseRot-casesDerrierePersonnage+1))); // translate it down so it's at the center of the scene
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur/3.0,1,largeur/3.0));	
    
    // distance du joueur à la case de transition 
    distanceAuVirage = distanceCase(ModelMatrix);
    if(distanceAuVirage<largeur/2 && !virage && !alreadyRotated){
        std::cout << "Tu n'as pas été assez rapide ! tu aurais dû tourner avant " << std::endl;
        etat=MORT;
    }
    if(distanceAuVirage<largeur/2 && sensVirage!=sensRotation){
        std::cout << "Tu t'es trompé de sens.." << std::endl;
        etat=MORT;
    }
    if(virage /*&& distanceAuVirage<0.95*/){
        // std::cout << "virage OK"<<std::endl;
        alreadyRotated = true;
        //std::cout<<"appel de fonction"<<std::endl;
        listeCameras.at(indiceCam)->virageCam(angleRotation);
        listeCameras.at((indiceCam+1)%2)->virageCamPassif(angleRotation);
    }

    sols[0].Draw(program);
}

void drawCaseDeTransition(Program &program,
                std::vector<Model> &sols, 
                float translation){
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,indiceBoucle*translation));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, 0, -largeur*(numCaseRot-casesDerrierePersonnage+1))); // translate it down so it's at the center of the scene
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur/3.0, 1, largeur/3.0));	
    sols[0].Draw(program);

    distanceAuVirage = distanceCase(ModelMatrix);
}

void testObstacles(Program &program, float translation, std::vector<Model> &pieces, std::vector<Model> &obstacles){
    //PARTIE TEST SUR LA CASE LA PLUS PROCHE
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,indiceBoucle*translation));
    if(distanceCase(ModelMatrix)<0.5*largeur){
        drawObject(program, pieces, 0,
                -1, 1, 0,
                translation, 0, 0, 0,
                1/2.0, 1/2.0, largeur/2.0);
        //Test pour cheminVisible à l'indice casesDerrierePersonnage
    }
}

void drawTerrain(Program &program, std::deque<int> &tableauDeSols,
                std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, std::vector<Model> &obstacles,
                float &angle, TableauDeScore &menu)
{  
    int boucleDeTranslation=50;
    indiceBoucle=(indiceBoucle+1)%(boucleDeTranslation+1);
    float translation=largeur/boucleDeTranslation;

    testObstacles(program, translation, pieces, obstacles);


    if(casTerrain==0){

        // //PARTIE TEST SUR LA CASE LA PLUS PROCHE
        // ModelMatrix = glm::mat4(1.0f);
        // ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
        // ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,indiceBoucle*translation));
        // if(distanceCase(ModelMatrix)<0.5*largeur){
        //     drawObject(program, 0, largeur/3,obstacles, 0, translation, 0, numCaseRot, 0, 1,1,1,0);
        // //Test pour cheminVisible à l'indice casesDerrierePersonnage
        // }

        for(int i=0; i<numCaseRot; i++){
            drawCase(program, sols, tableauDeSols, murs, 
            indiceBoucle*translation, 0, i-casesDerrierePersonnage, numCaseRot, i);

            // drawObjetCase(program, cheminVisible[i], pieces,
            //     obstacles, 
            //     translation, 0, i, numCaseRot);
        };
        tracerLampadaires(program, murs, 
                translation*indiceBoucle, 0,
                numCaseRot-casesDerrierePersonnage-1, numCaseRot-casesDerrierePersonnage,0);

        drawCaseDeTransitionVirage(program, sols, translation);

        tracerLampadaires(program, murs, 
                translation*indiceBoucle, sensRotation,
                0, numCaseRot-casesDerrierePersonnage,2);

        for(int i=0; i<tableauDeSols.size()-numCaseRot; i++){
            drawCase(program, sols, tableauDeSols, murs, 
            indiceBoucle*translation, sensRotation, i, numCaseRot-casesDerrierePersonnage, i+numCaseRot);

            // drawObjetCase(program, cheminVisible[i+numCaseRot], pieces,
            //     obstacles, 
            //     translation, sensRotation, i, numCaseRot);
        }
    }

    if(casTerrain==1){
        drawCaseDeTransition(program, sols, translation);

        // //PARTIE TEST SUR LA CASE LA PLUS PROCHE
        // ModelMatrix = glm::mat4(1.0f);
        // ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
        // ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,indiceBoucle*translation));
        // if(distanceCase(ModelMatrix)<0.5*largeur){
        //     drawObject(program, -1, largeur/2,pieces, 2, translation, 0, numCaseRot, 0, 1,1,1,0);
        //     //Test pour cheminVisible à l'indice casesDerrierePersonnage
        // }

        tracerLampadaires(program, murs, 
                translation*indiceBoucle, 0,
                numCaseRot-casesDerrierePersonnage+3, numCaseRot,0);
        lumScenePonct.changePositionAt(2, glm::vec4(1,0,1,1));
        lumScenePonct.changePositionAt(3, glm::vec4(1,0,1,1));



        for(int i=0; i<tableauDeSols.size()-numCaseRot; i++){
            drawCase(program, sols, tableauDeSols, murs, 
                    indiceBoucle*translation, 0, i+numCaseRot-casesDerrierePersonnage+3, numCaseRot, i+numCaseRot);
            // drawObjetCase(program, cheminVisible[i+numCaseRot], pieces,
            //     obstacles, 
            //     translation, 0, i, numCaseRot);
        };
    }

    if(boucleDeTranslation==indiceBoucle){
        //probablement ici qu'on fait cheminVisible.push_back(case)
        tableauDeSols.pop_front();
        tableauDeSols.push_back(indiceBoucle%3);
        numCaseRot--;
        distance++;
        menu.updateScore();
    }

    if(numCaseRot==-casesDerrierePersonnage){
        casTerrain=0;
        numCaseRot=20;
    }
}