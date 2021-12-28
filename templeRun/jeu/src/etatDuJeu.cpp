#include "../include/etatDuJeu.hpp"
using namespace glimac;

void debut(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            switch(e.type){
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_j){
                        etat=DEBUTDEPARTIE;
                    }
                    if(e.key.keysym.sym == SDLK_r){
                        etat=ANCIENNESPARTIES;
                    }
                    if(e.key.keysym.sym == SDLK_m){
                        etat=MEILLEURSSCORES;
                    }
                    break;
            }
        }

        program.use();
        menu.Draw(program);

        windowManager.swapBuffers();
}

void pause(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_Event e;
    while(windowManager.pollEvent(e)) {
        switch(e.type){
            case SDL_QUIT:
                done = true; // Leave the loop after this iteration
                break;
            case SDL_KEYDOWN:
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    etat=JEU;
                }
                if(e.key.keysym.sym == SDLK_s){
                    //inserer fonction pour sauvegarder
                    etat=SAUVEGARDER;
                }
                if(e.key.keysym.sym == SDLK_r){
                    etat=RECOMMENCER;
                }
                if(e.key.keysym.sym == SDLK_m){
                    etat=MEILLEURSSCORES;
                    }
                break;
        }
    }

    program.use();
    menu.Draw(program);

    // Update the display
    windowManager.swapBuffers();
}

void nom(int &etat, Program &program, SDLWindowManager &windowManager, EntrerNomDeLaPartie &menu, bool &done, Partie &partie){
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
                    partie.setNom(nomDePartie);
                    //DONNER LE NOM DE PARTIE A PARTIE
                    // if(){ //si le nom de partie existe déjà
                    //     etat=WARNING;
                    // }
                    etat=RECOMMENCER;
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

void warning(int &etat, Program &program, SDLWindowManager &windowManager, Warning &menu, bool &done){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_Event e;
    program.use();
    SDL_EnableUNICODE(1);
    while(windowManager.pollEvent(e)) {
        switch(e.type){
            case SDL_QUIT:
                done = true; 
                break;
            case SDL_KEYDOWN:
                if(e.key.keysym.sym == SDLK_o){
                    //sauvegarder partie
                    etat=DEBUT;
                }
                if(e.key.keysym.sym == SDLK_n){
                    nomDePartie="";
                    etat=SAUVEGARDER;
                }
                SDL_EnableUNICODE(0);
                break;
        }
    }


    program.use();
    menu.Draw(program);
    // Update the display
    windowManager.swapBuffers();
}

void rechargerParties(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, std::deque<Partie> &partiesSauvegardees, Partie &partieJouee){
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
                        recharger(partiesSauvegardees[0], partieJouee);
                    }
                    if(e.key.keysym.sym == SDLK_b){
                        //on charge la partie 2
                        recharger(partiesSauvegardees[1], partieJouee);
                    }
                    if(e.key.keysym.sym == SDLK_c){
                        //on charge la partie 3
                        recharger(partiesSauvegardees[2], partieJouee);
                    }
                    break;
            }
        }

        program.use();
        menu.Draw(program);

        windowManager.swapBuffers();
}

void meilleursScores(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, std::vector<Partie> &meilleursScores){
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
                        etat=DEBUT;
                    }
                    break;
            }
        }

        program.use();
        menu.Draw(program);

        windowManager.swapBuffers();
}


void mort(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            switch(e.type){
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;
                case SDL_KEYDOWN:
                    etat=DEBUT;
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
    //partieJouee.setChemin(partieACharger.cheminVisible);
    /*---- Camera et rotation du terrain ---*/
    angleActuel = 0;
    listeCameras.at(0)->reset();
    listeCameras.at(1)->reset();
    /*numCasRot et sensRotation ont été instanciés par le chargement de la partie!*/
    distanceAuVirage=1;
    virage = false;
    sensVirage=1; 
    alreadyRotated = false;
    rotationPersonnage=0;


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
    //cas terrain deja instancié dans le chargement de la partie
    indiceDepart=0;

    /*--maintenant que tout est pret, on joue!--*/
    etat=RECHARGER;
}

//ici il faudra prendre en argument le chemin visible de départ
void recommencer(){
    /* ici on part du principe qu'on charge le cheminVisible crée dans le main
    correspondant au chemin de départ de base (à changer?)*/

    /*---- Camera et rotation du terrain ---*/
    angleActuel = 0;
    listeCameras.at(0)->reset();
    listeCameras.at(1)->reset();
    numCaseRot = casesDerrierePersonnage ;//casesDerrierePersonnage-1;
    sensRotation = 1;
    distanceAuVirage=1;
    virage = false;
    sensVirage=1; 
    alreadyRotated = false;
    rotationPersonnage=0;


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
    etat=JEU;
}