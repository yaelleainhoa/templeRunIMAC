#include "../include/renderingTerrain.hpp"

float distanceCase(const glm::mat4 &Case){
    glm::vec4 M = glm::normalize(Case[3]); //on s'intéresse à la position, donc la derniere colonne de la matrice
    glm::vec3 pos = glm::vec3(M.x, M.y, M.z);
    return glm::distance(glm::vec3(0), pos); //on calcule la distance à 0 puisque le joueur est en 0
}

float saut(float &x){
    float l=largeur*2.0;
    float d=x*vitesse;
    if(d>l){
        return 0.0;
    }
    return (hauteur * d*(d-l)/(l/2*(l/2-l))); //trajectoire du saut
};

float baisser(){
    float l=largeur*2.0;
    float d=xBaisse*vitesse;
    if(d>l){
        return 1;
    }
    return 0.5; //on change la taille du joueur
}

void setTerrain(std::string path, std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, std::vector<Model> &obstacles){
    /*--- modeles de sols ----*/
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

    /*--- modeles de 'murs' (ce qui est autour du sol) ----*/
    Model trottoir(path + "/assets/models/trottoir/trottoir.obj");
    Model buisson(path + "/assets/models/buisson/buisson.obj");
    Model lampadaire(path + "/assets/models/lampadaire/lampadaire.obj");

    murs.push_back(trottoir);
    murs.push_back(buisson);
    murs.push_back(lampadaire);

    /*--- modeles de pieces ----*/
    Model biberon(path + "/assets/models/biberon/biberon.obj");
    Model tetine(path + "/assets/models/tetine/tetine.obj");
    Model doudou(path + "/assets/models/doudou/licorne.obj");
    pieces.push_back(biberon);
    pieces.push_back(tetine);
    pieces.push_back(doudou);

    /*--- modeles d'obstacles' ----*/
    Model tancarville(path + "/assets/models/tancarville/tancarville.obj");
    Model velo(path + "/assets/models/velo/bicycle.obj");
    obstacles.push_back(tancarville);
    obstacles.push_back(velo);
}


void drawObject(Program &program, std::vector<Model> &typeObjet,
                int idText,
                float posX, float poxY, int posZ,
                float translation, float signe, int caseRotation, float rotationObjet,
                float scaleX, float scaleY, float scaleZ, int rouge)
{
    //on envoie la couleur au shader, la couleur (avant le calcul de lumières) prend rouge en premier argument
    //si l'objet n'est pas rouge on aura une base neutre car rouge=0, sinon on aura une couleur rouge
    glUniform1i(glGetUniformLocation(program.getGLId(), "rouge"), rouge);

    ModelMatrix = glm::mat4(1.0f);
    //l'angle du terrain (droit, angle droit à gauche ou droite)
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    
    //translation correspond au mouvement
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));

    //si le terrain ne tourne pas signe=0, sinon il indique la rotation après le virage
    ModelMatrix=glm::rotate(ModelMatrix, signe*angleRotation, glm::vec3(0.0,1.0,0.0));

    //en x la position correspond au décalage jusqu'au virage, en z on a la translation qui permet de dessiner après le virage
    ModelMatrix = glm::translate(ModelMatrix, glm::vec3((signe)*(caseRotation+1)*largeur, 0.0f, -largeur*2*abs(signe)));

    //les positions en x, y et z (on a l'axe z va vers nous et on dessine dans l'autre sens)
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(largeur*posX,poxY*largeur, -largeur*posZ));

    //si l'objet effectue une rotation sur lui même
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


void drawObjetssCase(Program &program, const ssCase &ssCaseObjets, std::vector<Model> &pieces,
                std::vector<Model> &obstacles,
                float translation, float signe,
                int index, int caseRotation, int cas, int positionJoueur){              

//on ne dessine que si la sous case a des objets
    if(!ssCaseObjets.getObjet().empty()){
        for(int i=0; i<ssCaseObjets.getObjet().size(); i++){
            int attrapeObjet=ssCaseObjets.getObjet()[i].estAttrape();
            //si c'est une piece, la dessiner au bon endroit dans la map + bien placé sur sa case
            //on ne la dessine pas si elle a été attrapée
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
                            -1+ssCaseObjets.getObjet()[i].getIdObjet(), 
                            cas-3*signe, 0.4, index, 
                            translation, signe, caseRotation, 0, 1,1,1, attrapeObjet);
            }

            // //si l'obstacle est de taille 2, on le dessine entre les deux cases de gauche si on est dans 
            // //la ssCaseGauche (cas -1) et entre les deux cases de droite dans la ssCaseDroite (cas 1)
            // //dans le cas -1 on dessine à -1/2 et dans le cas 1 ) 1/2 
            else if(ssCaseObjets.getObjet()[i].getTaille()==2 && cas!=0 && ssCaseObjets.getObjet()[i].estObstacle()){
                drawObject(program, obstacles, 
                            ssCaseObjets.getObjet()[i].getIdObjet(), 
                            1/2.0*cas, 0.4, index, 
                            translation, signe, caseRotation,0, 1,1,1, attrapeObjet);
            }

            //si l'obstacle est de taille 3, on ne veut pas le dessiner 3 fois, on le dessine donc 
            //selon où le joueur se trouve latéralement (ce qui permet à l'obstacle de devenir rouge si on le touche)
            //pour éviter les doublons, on ne dessine que dans le cas 1
            else if(ssCaseObjets.getObjet()[i].getTaille()==3 && positionJoueur==cas){
                drawObject(program, obstacles, 
                            -1+ssCaseObjets.getObjet()[i].getIdObjet(), 
                            0-3*signe, 0.4, index, 
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

void drawLampadaires(Program &program, std::vector<Model> &murs, 
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

    //on décale la lumière vers le haut du lampadaire
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

    //on décale la lumière vers le haut du lampadaire
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
    if(virage){
        alreadyRotated = true;
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

    distanceAuVirage = 0;
}

void testObstacles(Program &program, float translation, std::vector<Model> &pieces, 
                    std::vector<Model> &obstacles, Case &caseTest, Joueur &joueur, 
                    Partie &partie, TableauDeScore &tableauDeScore){
                                                            
    ModelMatrix = glm::mat4(1.0f);
    ModelMatrix=glm::rotate(ModelMatrix, angleActuel, glm::vec3(0.0,1.0,0.0));
    ModelMatrix=glm::translate(ModelMatrix, glm::vec3(0,0,translation));

    //si la case est assez proche, on appelle la fonction de test
    if(distanceCase(ModelMatrix)<0.2*largeur){
        testMvt(caseTest, joueur, partie);

        //on change le tableau de score, le joueur peut avoir attrapé une pièce!
        tableauDeScore.updateScore(partie);

        //pour éviter d'appeler la fonction en continu quand la distance est suffisante
        //(et risquer d'augmenter le score en continu..) on indique qu'il n'y a plus de test
        //a faire (jusqu'à la prochaine boucle!)
        testAFaire=false;
    }
}