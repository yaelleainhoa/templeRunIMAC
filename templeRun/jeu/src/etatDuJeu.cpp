#include "../include/etatDuJeu.hpp"

using namespace glimac;

void debut(Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, Partie &partieEnCours){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            switch(e.type){
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_j){
                        nomDePartie="";
                        partieEnCours.setNom(nomDePartie);
                        partieEnCours.setEtat(DEBUTDEPARTIE);
                    }
                    if(e.key.keysym.sym == SDLK_r){
                        partieEnCours.setEtat(ANCIENNESPARTIES);
                    }
                    if(e.key.keysym.sym == SDLK_m){
                        partieEnCours.setEtat(MEILLEURSSCORES);
                    }
                    break;
            }
        }

        program.use();
        menu.Draw(program);

        windowManager.swapBuffers();
}

void pause(Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, Partie &partieEnCours){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_Event e;
    while(windowManager.pollEvent(e)) {
        switch(e.type){
            case SDL_QUIT:
                done = true; // Leave the loop after this iteration
                break;
            case SDL_KEYDOWN:
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    partieEnCours.setEtat(JEU);
                }
                if(e.key.keysym.sym == SDLK_s){
                    //inserer fonction pour sauvegarder
                    partieEnCours.setEtat(SAUVEGARDER);
                }
                if(e.key.keysym.sym == SDLK_r){
                    partieEnCours.setEtat(RECOMMENCER);
                }
                if(e.key.keysym.sym == SDLK_m){
                    partieEnCours.setEtat(MEILLEURSSCORES);
                    }
                break;
        }
    }

    program.use();
    menu.Draw(program);

    // Update the display
    windowManager.swapBuffers();
}

void nom(Program &program, SDLWindowManager &windowManager, EntrerNomDeLaPartie &menu, bool &done, Partie &partieEnCours){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_Event e;
    program.use();
    SDL_EnableUNICODE(1);
    while(windowManager.pollEvent(e)) {
        switch(e.type){
            case SDL_QUIT:
                done = true; // Leave the loop after this iteration
                break;
            case SDL_KEYDOWN:
                if(e.key.keysym.sym == SDLK_RETURN){
                    std::cout<<nomDePartie<<std::endl;
                    partieEnCours.setNom(nomDePartie);
                    partieEnCours.setEtat(RECOMMENCER);
                }
                else{
                    if((e.key.keysym.unicode >= 'a' && e.key.keysym.unicode <= 'z') or  (e.key.keysym.unicode >= 'A' && e.key.keysym.unicode <= 'Z')) {
                        nomDePartie +=char(e.key.keysym.unicode);
                        menu.updateNom(nomDePartie);
                        menu.Draw(program);
                        windowManager.swapBuffers();
                    }
                }
                SDL_EnableUNICODE(0);
                break;
        }
    }

    program.use();
    menu.Draw(program);
    windowManager.swapBuffers();
}

void rechargerParties(Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, std::deque<Partie> &partiesSauvegardees, Partie &partieJouee){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            switch(e.type){
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_a){
                        //on charge la partie 1
                        if(partiesSauvegardees.size() > 0) recharger(partiesSauvegardees[0], partieJouee);
                    }
                    if(e.key.keysym.sym == SDLK_b){
                        //on charge la partie 2
                        if(partiesSauvegardees.size() > 1) recharger(partiesSauvegardees[1], partieJouee);
                    }
                    if(e.key.keysym.sym == SDLK_c){
                        //on charge la partie 3
                        if(partiesSauvegardees.size() > 2) recharger(partiesSauvegardees[2], partieJouee);
                    }
                    if(e.key.keysym.sym == SDLK_d){
                        //on charge la partie 3
                        if(partiesSauvegardees.size() > 3) recharger(partiesSauvegardees[3], partieJouee);
                    }
                    if(e.key.keysym.sym == SDLK_e){
                        //on charge la partie 3
                        if(partiesSauvegardees.size() > 4) recharger(partiesSauvegardees[4], partieJouee);
                    }
                    if(e.key.keysym.sym == SDLK_ESCAPE){
                        //on charge la partie 1
                        partieJouee.setEtat(DEBUT);
                    }
                    break;
            }
        }

        program.use();
        menu.Draw(program);

        windowManager.swapBuffers();
}

void meilleursScores(Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, Partie &partieEnCours){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            switch(e.type){
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE){
                        //on charge la partie 1
                        partieEnCours.setEtat(DEBUT);
                    }
                    break;
            }
        }

        program.use();
        menu.Draw(program);

        windowManager.swapBuffers();
}


void mort(Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, Partie &partieEnCours){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            switch(e.type){
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;
                case SDL_KEYDOWN:
                    partieEnCours.setEtat(DEBUT);
                    break;
            }
        }

        //oh euh je suis mort est ce que mon score est cool ? si oui l'enregistrer ! si non osef
        //Jeu.ajouterMeilleurScore()
        program.use();
        menu.Draw(program);

        windowManager.swapBuffers();
}

//ici il faudra prendre en argument le chemin visible
void recharger(Partie &partieACharger, Partie &partieJouee){
    /* ici on charge le chemin visible de la partie chargée!*/
    partieJouee.cheminVisible=partieACharger.cheminVisible;

    /*---- Camera et rotation du terrain ---*/
    angleActuel = 0;
    listeCameras.at(0)->reset();
    listeCameras.at(1)->reset();
    numCaseRot=partieACharger.getNumeroCaseRotation();
    sensRotation=partieACharger.getSensRotation();
    distanceAuVirage=1;
    virage = false;
    sensVirage=sensRotation; 
    alreadyRotated = false;
    rotationPersonnage=0;
    etatSinges=0;


    /*---score---*/
    partieJouee.setScore(partieACharger.getScore());
    partieJouee.setDistance(partieACharger.getDistance());

    /*---positions du joueur--*/
    positionLaterale=0.0;
    positionVerticale=0.0;
    x=largeur;
    xBaisse=largeur;
    taille=1;

    /*---dessin du terrain, partie du terrain qu'on dessine---*/
    indiceBoucle=0;
    casTerrain=partieACharger.getCasDeTerrain();
    indiceDepart=0;

    /*--maintenant que tout est pret, on joue!--*/
    partieJouee.setEtat(RECHARGER);
}

//ici il faudra prendre en argument le chemin visible de départ
void recommencer(Partie &partieEnCours){
    /* ici on part du principe qu'on charge le cheminVisible crée dans le main
    correspondant au chemin de départ de base (à changer?)*/

    /*---- Camera et rotation du terrain ---*/
    angleActuel = 0;
    listeCameras.at(0)->reset();
    listeCameras.at(1)->reset();
    numCaseRot = casesDerrierePersonnage ;
    sensRotation = 1;
    distanceAuVirage=1;
    virage = false;
    sensVirage=1; 
    alreadyRotated = false;
    rotationPersonnage=0;
    etatSinges=0;
    poursuite1 = true;

    // /*---score---*/
    // score=0;
    // distance=0;

    /*---positions du joueur--*/
    positionLaterale=0.0;
    positionVerticale=0.0;
    x=largeur;
    xBaisse=largeur;
    taille=1;

    /*---dessin du terrain, partie du terrain qu'on dessine---*/
    indiceBoucle=0;
    casTerrain=2;
    indiceDepart=0;

    /*--maintenant que tout est pret, on joue!--*/
    partieEnCours.setEtat(JEU);
}