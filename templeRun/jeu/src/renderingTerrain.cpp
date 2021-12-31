#include "../include/renderingTerrain.hpp"
#include "./../include/camera.hpp"



float distanceCase(const glm::mat4 &Case){
    glm::vec4 M = glm::normalize(Case[3]);
    glm::vec3 pos = glm::vec3(M.x, M.y, M.z);
    return glm::distance(glm::vec3(0), pos);
}

float saut(float &x){
    float l=largeur*2.0;
    float d=x*vitesse;
    if(d>l){
        return 0.0;
    }
    return (hauteur * d*(d-l)/(l/2*(l/2-l)))+0.01;
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
    Model sol_obstacle_milieu(path + "/assets/models/sol_obstacle_milieu/sol.obj");
    Model sol_obstacle_gauche(path + "/assets/models/sol_obstacle_gauche/sol_gauche.obj");
    Model sol_rotation(path + "/assets/models/sol_rotation/sol_rotation.obj");

    sols.push_back(sol);
    sols.push_back(sol_obstacle_gauche);
    sols.push_back(sol_obstacle_milieu); 
    sols.push_back(sol_obstacle_droite);
    sols.push_back(sol_rotation);


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
    //Model pomme(path + "/assets/models/pompom/pompom.obj");
    obstacles.push_back(tancarville);
    obstacles.push_back(velo);
    //obstacles.push_back(pomme);
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
                float scaleX, float scaleY, float scaleZ, int rouge)
{
    glUniform1i(glGetUniformLocation(program.getGLId(), "rouge"), rouge);
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
                    float posX, float poxY, float posZ, int rouge)
{
    glUniform1i(glGetUniformLocation(program.getGLId(), "rouge"), rouge);
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, rotationPersonnage, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(largeur*posX,poxY*largeur, posZ));
    ModelMatrix=glm::rotate(ModelMatrix,rotationModel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(scaleX, scaleY, scaleZ));

    typeObjet[idText].Draw(program);
}


//CODE PAS TOUT A FAIT PRET, A TESTER AVEC LES FONCTIONS DE LISA

void drawObjetssCase(Program &program, const ssCase &ssCaseObjets, std::vector<Model> &pieces,
                std::vector<Model> &obstacles,
                float translation, float signe,
                int index, int caseRotation, int cas, int positionJoueur){              

    if(!ssCaseObjets.getObjet().empty()){
        //std::cout<<"taille vect : "<<ssCaseObjets.getObjet().size()<<std::endl;
        for(int i=0; i<ssCaseObjets.getObjet().size(); i++){
            int attrapeObjet=ssCaseObjets.getObjet()[i].estAttrape();
            //si c'est une piece, la dessiner au bon endroit dans la map + bien placé sur sa case
            //pour l'instant, ne prend pas en compte le cas où la piece a été prise
            if(ssCaseObjets.getObjet()[i].estPiece() && ssCaseObjets.getObjet()[i].estAttrape()==0){
                drawObject(program, pieces, 
                            ssCaseObjets.getObjet()[i].getIdObjet(),
                            cas-3*signe, ssCaseObjets.getObjet()[i].getMvt()+0.5, index,
                            translation, signe, caseRotation, rotationPiece);
            }

            //si ce n'est pas une piece, il faut faire attention à la taille de l'objet
            //si l'obstacle est de taille 1, on le dessine sur la case directement
            else if(ssCaseObjets.getObjet()[i].getTaille()==1 && ssCaseObjets.getObjet()[i].estObstacle() && ssCaseObjets.getObjet()[i].getIdObjet()!=0){
                drawObject(program, obstacles, 
                            1,//ssCaseObjets.getObjet()[i].getIdObjet(), //ici peut être la texture facile comme seulement velo??
                            cas-3*signe, 0.4, index, //mvt taille 1 seulemnt  0?
                            translation, signe, caseRotation, 0, 1,1,1, attrapeObjet);
            }

            // //si l'obstacle est de taille 2, on le dessine entre les deux cases de gauche si on est dans 
            // //la ssCaseGauche (cas -1) et entre les deux cases de droite dans la ssCaseDroite (cas 1)
            // //dans le cas -1 on dessine à -1/2 et dans le cas 1 ) 1/2 
            else if(ssCaseObjets.getObjet()[i].getTaille()==2 && cas!=0 && ssCaseObjets.getObjet()[i].estObstacle()){
                drawObject(program, obstacles, 
                            ssCaseObjets.getObjet()[i].getIdObjet(), //ici peut être la texture facile comme seulement velo??
                            1/2.0*cas, 0.4, index, //mvt taille 1 seulemnt  0?
                            translation, signe, caseRotation,0, 1,1,1, attrapeObjet);
            }

            //si l'obstacle est de taille 3, on le dessine au milieu dans tous les cas
            //pour éviter les doublons, on ne dessine que dans le cas 1
            else if(ssCaseObjets.getObjet()[i].getTaille()==3 && positionJoueur==cas){
                drawObject(program, obstacles, 
                            0,//ssCaseObjets.getObjet()[i].getIdObjet(), //pareil, je connais la texture en fait (?)
                            0-3*signe, 0.4, index, //pareil mvt no need a priori
                            translation, signe, caseRotation,0, 1,1,1, attrapeObjet);
            }
        }
    }
}

void drawObjetCase(Program &program, const Case &caseObjets, std::vector<Model> &pieces,
                std::vector<Model> &obstacles,
                float translation, float signe,
                int index, int caseRotation, int positionJoueur){

    //on dessine les objets de la case de gauche (cas -1)
    drawObjetssCase(program, caseObjets.ssCaseGauche, pieces, obstacles,
                        translation, signe, index, caseRotation, -1, positionJoueur);

    //on dessine les objets de la case du milieu (cas 0)
    drawObjetssCase(program, caseObjets.ssCaseMilieu, pieces, obstacles,
                        translation, signe, index, caseRotation, 0, positionJoueur);

    //on dessine les objets de la case de droite (cas 1)
    drawObjetssCase(program, caseObjets.ssCaseDroite, pieces, obstacles,
                        translation, signe, index, caseRotation, 1, positionJoueur);

}



void drawCase(Program &program, std::vector<Model> &sols, 
                std::vector<Model> &murs, 
                float translation, float signe,
                int i, int caseRotation, int indiceTexture){


    //on dessine d'abord les murs
    drawObject(program, murs, 0,
                1.8, 0, i,
                translation, signe, caseRotation, 0,
                1/2.0, 1/2.0, largeur/2.0);
    drawObject(program, murs, 1,
                2.4, 0, i,
                translation, signe, caseRotation, 0,
                1/2.0, 1/2.0, largeur);
    drawObject(program, murs, 0,
                -1.8, 0, i,
                translation, signe, caseRotation, 0,
                1/2.0, 1/2.0, largeur/2.0);
    drawObject(program, murs, 1,
                -2.4, 0, i,
                translation, signe, caseRotation, 0,
                1/2.0, 1/2.0, largeur);
    
    //on dessine le sol
    drawObject(program, sols, indiceTexture,
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
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(-largeur*1.8,1/4.0*largeur, 0));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1/2.0, 1/2.0, 1/2.0));

    murs[2].Draw(program);

    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,7,0));
    lumScenePonct.changePositionAt(indexCoupleLampadaire, ModelMatrix[3]);
    lumScenePonct.changeIntensiteAt(indexCoupleLampadaire, glm::vec3(252/255.0*2, 186/255.0*2, 3/255.0*2));

    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
    ModelMatrix=glm::rotate(ModelMatrix, signe*angleRotation, glm::vec3(0.0,1.0,0.0));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3((signe)*(caseRotation+1)*largeur, 0.0f, -largeur*(i+2*abs(signe))));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(+largeur*1.8,1/4.0*largeur, 0));
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1/2.0, 1/2.0, 1/2.0));

    murs[2].Draw(program);

    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,7,0));
    lumScenePonct.changePositionAt(indexCoupleLampadaire+1, ModelMatrix[3]);
    lumScenePonct.changeIntensiteAt(indexCoupleLampadaire+1, glm::vec3(252/255.0*2, 186/255.0*2, 3/255.0*2));
}

void drawCaseDeTransition(Program &program,
                std::vector<Model> &sols, 
                float translation, Partie &partieEnCours){
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,indiceBoucle*translation));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, 0, -largeur*(numCaseRot-casesDerrierePersonnage+1))); // translate it down so it's at the center of the scene
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur/3.0,1,largeur/3.0));	
    
    // distance du joueur à la case de transition 
    distanceAuVirage = distanceCase(ModelMatrix);
    if(distanceAuVirage<largeur/2 && !virage && !alreadyRotated){
        std::cout << "Tu n'as pas été assez rapide ! tu aurais dû tourner avant " << std::endl;
        partieEnCours.setEtat(MORT);
    }
    if(distanceAuVirage<largeur/2 && sensVirage!=sensRotation){
        std::cout << "Tu t'es trompé de sens.." << std::endl;
        partieEnCours.setEtat(MORT);
    }
    if(virage /*&& distanceAuVirage<0.95*/){
        // std::cout << "virage OK"<<std::endl;
        alreadyRotated = true;
        //std::cout<<"appel de fonction"<<std::endl;
        listeCameras.at(indiceCam)->virageCam(angleRotation);
        listeCameras.at((indiceCam+1)%2)->virageCamPassif(angleRotation);
    }

    sols[4].Draw(program);
}

void drawCaseDeTransitionVirage(Program &program,
                std::vector<Model> &sols, 
                float translation){
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,indiceBoucle*translation));
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0, 0, -largeur*(numCaseRot-casesDerrierePersonnage+1))); // translate it down so it's at the center of the scene
    ModelMatrix = glm::scale(ModelMatrix, glm::vec3(largeur/3.0, 1, largeur/3.0));	
    sols[4].Draw(program);

    distanceAuVirage = distanceCase(ModelMatrix);
}

void testObstacles(Program &program, float translation, std::vector<Model> &pieces, 
                    std::vector<Model> &obstacles, Case &caseTest, Joueur &joueur, 
                    Partie &partie, TableauDeScore &tableauDeScore){
                                                            
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));
     if(distanceCase(ModelMatrix)<0.2*largeur){
         std::cout<<"test obstacle"<<std::endl;
         testMvt(caseTest, joueur, partie);
         tableauDeScore.updateScore(partie);
         testAFaire=false;
     }
}

void drawTerrain(Program &program, 
                std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, 
                std::vector<Model> &obstacles, float &angle, TableauDeScore &menu, Partie &partieEnCours,
                Joueur &joueur, const std::vector<std::deque<Case>> &parcoursPossibles)
{  
    int boucleDeTranslation=50;
    indiceBoucle=(indiceBoucle+1)%(boucleDeTranslation+1);
    float translation=largeur/boucleDeTranslation;
    if(rotationPiece<360){
        rotationPiece+=0.1;
    }
    else rotationPiece=0;
    if(casTerrain==0){
        if(testAFaire) {testObstacles(program, indiceBoucle*translation, pieces, obstacles, partieEnCours.cheminVisible[casesDerrierePersonnage], joueur, partieEnCours, menu);};
        for(int i=0; i<numCaseRot; i++){
            drawCase(program, sols, murs, 
            indiceBoucle*translation, 0, i-casesDerrierePersonnage, numCaseRot, partieEnCours.cheminVisible[i].getText());

            drawObjetCase(program, partieEnCours.cheminVisible[i], pieces,
                obstacles, 
                indiceBoucle*translation, 0, i-casesDerrierePersonnage, numCaseRot, joueur.getPositionHorizontale());
        };
        tracerLampadaires(program, murs, 
                translation*indiceBoucle, 0,
                numCaseRot-casesDerrierePersonnage-1, numCaseRot-casesDerrierePersonnage,0);

        drawCaseDeTransition(program, sols, translation, partieEnCours);

        if(numCaseRot<=10){
            tracerLampadaires(program, murs, 
                translation*indiceBoucle, sensRotation,
                0, numCaseRot-casesDerrierePersonnage,2);
        }
        else{
            tracerLampadaires(program, murs, 
                translation*indiceBoucle, 0,
                -3-indiceDepart, 0,2);
        }

        for(int i=0; i<partieEnCours.cheminVisible.size()-numCaseRot; i++){
            drawCase(program, sols, murs, 
            indiceBoucle*translation, sensRotation, i, numCaseRot-casesDerrierePersonnage, partieEnCours.cheminVisible[i+numCaseRot].getText());

            drawObjetCase(program, partieEnCours.cheminVisible[i+numCaseRot], pieces,
                obstacles, 
                indiceBoucle*translation, sensRotation, i, numCaseRot, joueur.getPositionHorizontale());
        }
    }

    //ce cas sert à faire la transition entre le virage et le chemin droit
    else if(casTerrain==1){
        drawCaseDeTransitionVirage(program, sols, translation);

        tracerLampadaires(program, murs, 
                translation*indiceBoucle, 0,
                numCaseRot-casesDerrierePersonnage+3, numCaseRot,0);
        lumScenePonct.changeIntensiteAt(2, glm::vec3(0,0,0));
        lumScenePonct.changeIntensiteAt(3, glm::vec3(0,0,0));

        if(indiceDepart-2>=0){
            if(testAFaire) {testObstacles(program, indiceBoucle*translation, pieces, obstacles, partieEnCours.cheminVisible[casesDerrierePersonnage+indiceDepart-2], joueur, partieEnCours, menu);};
        }
        for(int i=0; i<partieEnCours.cheminVisible.size()-casesDerrierePersonnage; i++){
                drawCase(program, sols, murs, 
                indiceBoucle*translation, 0, i+numCaseRot-casesDerrierePersonnage+3, numCaseRot, partieEnCours.cheminVisible[i+casesDerrierePersonnage].getText());

            drawObjetCase(program, partieEnCours.cheminVisible[i+casesDerrierePersonnage], pieces,
                obstacles, 
                indiceBoucle*translation, 0, i+numCaseRot-casesDerrierePersonnage+3, numCaseRot, joueur.getPositionHorizontale());
        };
    }

    //ce cas sert à faire le dessin du terrain au départ
    else{
        drawCaseDeTransitionVirage(program, sols, translation);

        tracerLampadaires(program, murs, 
                translation*indiceBoucle, 0,
                numCaseRot-casesDerrierePersonnage+3, numCaseRot,0);
        lumScenePonct.changeIntensiteAt(2, glm::vec3(0,0,0));
        lumScenePonct.changeIntensiteAt(3, glm::vec3(0,0,0));
        // lumScenePonct.changeIntensiteAt(0, glm::vec3(0,0,0));
        // lumScenePonct.changeIntensiteAt(1, glm::vec3(0,0,0));

        // std::cout<<"indice dans le cas 2 = "<<indiceCaseDeTransition<<std::endl;
        if(indiceDepart-2>=0){
            if(testAFaire) {testObstacles(program, indiceBoucle*translation-largeur, pieces, obstacles, partieEnCours.cheminVisible[indiceDepart-2], joueur, partieEnCours, menu);};
        }
        for(int i=0; i<partieEnCours.cheminVisible.size()-casesDerrierePersonnage; i++){
            drawCase(program, sols, murs, 
                indiceBoucle*translation, 0, i+numCaseRot-casesDerrierePersonnage+3, numCaseRot, partieEnCours.cheminVisible[i].getText());

            drawObjetCase(program, partieEnCours.cheminVisible[i], pieces,
                obstacles, 
                indiceBoucle*translation, 0, i+numCaseRot-casesDerrierePersonnage+3, numCaseRot, joueur.getPositionHorizontale());
        };
    }

    if(boucleDeTranslation==indiceBoucle){
        //probablement ici qu'on fait cheminVisible.push_back(case)
        if(casTerrain==0){
            partieEnCours.cheminVisible.pop_front();
        //on pushera des cases de cheminSansDanger et cheminDanger
            int indiceParcours=rand()%2;
            partieEnCours.cheminVisible.push_back(parcoursPossibles[indiceParcours][rand()%(parcoursPossibles[indiceParcours].size())]);
        }
        //else{
            indiceDepart++;
        //}
        numCaseRot--;
        partieEnCours.incrementeDistance(1);
        menu.updateDistance(partieEnCours);

        if(NB_TOURS_SINGES!=-1){
            //joueur.singes().retireToursRestants();
            NB_TOURS_SINGES--;
        }
        if(NB_TOURS_SINGES==0){
            //joueur.singes().deplacement(1);
            //joueur.singes().setToursRestants(-1);
            NB_TOURS_SINGES = -1;
            etatSinges = 0;
        }
        testAFaire=true;
    }

    if(numCaseRot==-casesDerrierePersonnage){
        //maintenant qu'on a fait le virage et qu'on a
        //assez de cases derrière, on supprime les premieres et on en ajoute
        //des nouvelles
        if(casTerrain==1){
            partieEnCours.cheminVisible.pop_front();
            partieEnCours.cheminVisible.pop_front();
            partieEnCours.cheminVisible.pop_front();

            //on pushera des cases de cheminSansDanger et cheminDanger
            int indiceParcours=rand()%2;
            partieEnCours.cheminVisible.push_back(parcoursPossibles[indiceParcours][rand()%(parcoursPossibles[indiceParcours].size())]);
            partieEnCours.cheminVisible.push_back(parcoursPossibles[indiceParcours][rand()%(parcoursPossibles[indiceParcours].size())]);
            partieEnCours.cheminVisible.push_back(parcoursPossibles[indiceParcours][rand()%(parcoursPossibles[indiceParcours].size())]);
        }

        casTerrain=0;
        indiceDepart=0;
        numCaseRot=partieEnCours.cheminVisible.size();
    }
}