#include "../include/drawTerrain.hpp"

void drawTerrain(Program &program, 
                std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, 
                std::vector<Model> &obstacles, float &angle, TableauDeScore &menu, Partie &partieEnCours,
                Joueur &joueur, const std::vector<std::deque<Case>> &parcoursPossibles)
{  
    //pour tracer le terrain on avance sur une boucle : on divise la largeur d'une case 
    //en boucleDeTranslation et on avance de ce pas
    int boucleDeTranslation=50;
    indiceBoucle=(indiceBoucle+1)%(boucleDeTranslation+1);
    float translation=largeur/boucleDeTranslation;

    //int NB_TOURS_SINGES = joueur.singes().getDistancePerso();

    //pour éviter de stocker un trop grand float pour la rotation, on le remet à 0 à chaque tour
    if(rotationPiece<360){
        rotationPiece+=0.1;
    }
    else rotationPiece=0;

    //Dans le cas où on n'est ni dans un virage, ni au tout départ du jeu
    if(casTerrain==0){

        //si on est assez proche de la case, testAFaire est true, on fait le test
        //on ne fait pas de test lorsque l'on est sur un virage
        if(testAFaire && !virage) {testObstacles(program, indiceBoucle*translation, pieces, obstacles, partieEnCours.cheminVisible[casesDerrierePersonnage], joueur, partieEnCours, menu);};

        //on dessine la première partie du terrain, celle avant le virage
        for(int i=0; i<numCaseRot; i++){
            //on dessine le sol, les buissons et trottoires
            drawCase(program, sols, murs, 
            indiceBoucle*translation, 0, i-casesDerrierePersonnage, numCaseRot, partieEnCours.cheminVisible[i].getText());

            //on dessine les obstacles et les pièces
            drawObjetCase(program, partieEnCours.cheminVisible[i], pieces,
                obstacles, 
                indiceBoucle*translation, 0, i-casesDerrierePersonnage, numCaseRot, joueur.getPositionHorizontale());
        };

        //on dessine le virage
        drawCaseDeTransition(program, sols, translation, partieEnCours);

        //on dessine les lampadaires qui sont au prochain virage
        drawLampadaires(program, murs, 
                translation*indiceBoucle, 0,
                numCaseRot-casesDerrierePersonnage-1, numCaseRot-casesDerrierePersonnage,0);

        //pour éviter que la lumière du virage précédent disparaisse d'un coup, on dessine encore la lumière des cases derrières
        //une fois que ces lampadaires sont trop loins, on dessine les prochains
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

        //on dessine la partie du terrain après la rotation, elle est tournée à gauche ou à droite selon l'indice sensRotation
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
        //on dessine le virage qu'on vient de depasser
        drawCaseDeTransitionVirage(program, sols, translation);

        //on dessine les lampadaires proches et on "éteint" les lampadaires qui ne servent pas
        drawLampadaires(program, murs, 
                translation*indiceBoucle, 0,
                numCaseRot-casesDerrierePersonnage+3, numCaseRot,0);
        lumScenePonct.changeIntensiteAt(2, glm::vec3(0,0,0));
        lumScenePonct.changeIntensiteAt(3, glm::vec3(0,0,0));

        //on ne commence les test qu'une fois qu'on est bien sortis de la case de transition pour le virage
        if(indiceDepart-2>=0){
            if(testAFaire) {testObstacles(program, indiceBoucle*translation, pieces, obstacles, partieEnCours.cheminVisible[casesDerrierePersonnage+indiceDepart-2], joueur, partieEnCours, menu);};
        }

        //on dessine les cases devant nous
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
        //on commence le parcours sur une trace de transition
        drawCaseDeTransitionVirage(program, sols, translation);

        drawLampadaires(program, murs, 
                translation*indiceBoucle, 0,
                numCaseRot-casesDerrierePersonnage+3, numCaseRot,0);
        lumScenePonct.changeIntensiteAt(2, glm::vec3(0,0,0));
        lumScenePonct.changeIntensiteAt(3, glm::vec3(0,0,0));

        //on ne fait des test qu'une fois qu'on est bien sortis de la case de transition
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

    //si on a bien parcouru une case 
    if(boucleDeTranslation==indiceBoucle){
        //si l'on est dans le cas 0, on supprime la premier case du deque du cheminVisible, puisqu'on ne la voit plus
        if(casTerrain==0){
            partieEnCours.cheminVisible.pop_front();

            //pour éviter de mettre des obstacles trop proches, on decide d'en mettre toutes les 5 cases
            int indiceParcours=partieEnCours.getDistance()%5;
            if(indiceParcours==0){
                indiceParcours=1;
            }
            else indiceParcours=0;

            //on rajoute une case prédéfinie dans les vecteurs crée aléatoirement dans le main, soit avec des osbtacles, soit sans
            partieEnCours.cheminVisible.push_back(parcoursPossibles[indiceParcours][rand()%(parcoursPossibles[indiceParcours].size())]);
        }
        indiceDepart++;
        //on s'approche du virage, l'indice de case de rotation diminue
        numCaseRot--;

        partieEnCours.incrementeDistance(1);
        menu.updateDistance(partieEnCours);

        if(joueur.singes().getDistancePerso()!=-1){
            joueur.singes().deplacement(-1);
        }
        if(joueur.singes().getDistancePerso()==0){
            joueur.singes().initialiseDistancePersonnage();
            etatSinges = 0;
        }

        std::cout<<"DISTANCE SINGE : "<<joueur.singes().getDistancePerso()<<std::endl;

        //la boucle est finie, on peut donc recommencer les tests si la case est assez proche
        testAFaire=true;
    }

    if(numCaseRot==-casesDerrierePersonnage){
        //maintenant qu'on a fait le virage et qu'on a
        //assez de cases derrière, on supprime les premieres cases et on en ajoute
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

        //le prochain virage
        numCaseRot=partieEnCours.cheminVisible.size();
    }
}