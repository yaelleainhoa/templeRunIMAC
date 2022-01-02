#include "../include/drawTerrain.hpp"
#include "../include/camera.hpp"


void drawTerrain(Program &program, 
                std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, 
                std::vector<Model> &obstacles, float &angle, TableauDeScore &menu, Partie &partieEnCours,
                Joueur &joueur, const std::vector<std::deque<Case>> &parcoursPossibles)
{  
    int boucleDeTranslation=50;
    indiceBoucle=(indiceBoucle+1)%(boucleDeTranslation+1);
    float translation=largeur/boucleDeTranslation;
    int NB_TOURS_SINGES = joueur.singes().getDistancePerso();
    if(rotationPiece<360){
        rotationPiece+=0.1;
    }
    else rotationPiece=0;
    if(casTerrain==0){
        if(testAFaire && !virage) {testObstacles(program, indiceBoucle*translation, pieces, obstacles, partieEnCours.cheminVisible[casesDerrierePersonnage], joueur, partieEnCours, menu);};
        for(int i=0; i<numCaseRot; i++){
            drawCase(program, sols, murs, 
            indiceBoucle*translation, 0, i-casesDerrierePersonnage, numCaseRot, partieEnCours.cheminVisible[i].getText());

            drawObjetCase(program, partieEnCours.cheminVisible[i], pieces,
                obstacles, 
                indiceBoucle*translation, 0, i-casesDerrierePersonnage, numCaseRot, joueur.getPositionHorizontale());
        };
        drawLampadaires(program, murs, 
                translation*indiceBoucle, 0,
                numCaseRot-casesDerrierePersonnage-1, numCaseRot-casesDerrierePersonnage,0);

        drawCaseDeTransition(program, sols, translation, partieEnCours);

        if(numCaseRot<=15){
            drawLampadaires(program, murs, 
                translation*indiceBoucle, sensRotation,
                0, numCaseRot-casesDerrierePersonnage,2);
        }
        else{
            drawLampadaires(program, murs, 
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

        drawLampadaires(program, murs, 
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

        drawLampadaires(program, murs, 
                translation*indiceBoucle, 0,
                numCaseRot-casesDerrierePersonnage+3, numCaseRot,0);
        lumScenePonct.changeIntensiteAt(2, glm::vec3(0,0,0));
        lumScenePonct.changeIntensiteAt(3, glm::vec3(0,0,0));

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
            int indiceParcours=partieEnCours.getDistance()%5;
            if(indiceParcours==0){
                indiceParcours=1;
            }
            else indiceParcours=0;
            partieEnCours.cheminVisible.push_back(parcoursPossibles[indiceParcours][rand()%(parcoursPossibles[indiceParcours].size())]);
            numCaseRot--;
        }
        indiceDepart++;
        if(casTerrain!=0){
            numCaseRot--;
        }
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