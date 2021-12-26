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
                        etat=RECOMMENCER;
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

void nom(int &etat, Program &program, SDLWindowManager &windowManager, EntrerNomDeLaPartie &menu, bool &done){
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
                    //partie.setNom(nomDePartie);
                    //DONNER LE NOM DE PARTIE A PARTIE
                    // if(){ //si le nom de partie existe déjà
                    //     etat=WARNING;
                    // }
                    etat=DEBUT;
                }
                else{
                    if((e.key.keysym.unicode >= 'a' && e.key.keysym.unicode <= 'z') or  (e.key.keysym.unicode >= 'A' && e.key.keysym.unicode <= 'Z')) {
                        nomDePartie +=char(e.key.keysym.unicode);
                        menu.setNomPartie(nomDePartie);
                        menu.creation();
                        menu.Draw(program);
                        windowManager.swapBuffers();
                    }
                }
                SDL_EnableUNICODE(0);
                break;
        }
    }

    // menu.creationEntrerNomDeLaPartie(nomDePartie);
    menu.Draw(program);
    // Update the display
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


    // menu.creationEntrerNomDeLaPartie(nomDePartie);
    menu.Draw(program);
    // Update the display
    windowManager.swapBuffers();
}

// void recharger(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done){
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//         SDL_Event e;
//         while(windowManager.pollEvent(e)) {
//             switch(e.type){
//                 case SDL_QUIT:
//                     done = true; // Leave the loop after this iteration
//                     break;
//                 case SDL_KEYDOWN:
//                     if(e.key.keysym.sym == SDLK_a){
//                         //on charge la partie 1
//                         etat=RECHARGER;
//                     }
//                     if(e.key.keysym.sym == SDLK_b){
//                         //on charge la partie 2
//                         etat=RECHARGER;
//                     }
//                     if(e.key.keysym.sym == SDLK_c){
//                         //on charge la partie 3
//                         etat=RECHARGER;
//                     }
//                     break;
//             }
//         }

//         program.use();
//         menu.Draw(program);

//         windowManager.swapBuffers();
// }

// void meilleursScores(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done){
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//         SDL_Event e;
//         while(windowManager.pollEvent(e)) {
//             switch(e.type){
//                 case SDL_QUIT:
//                     done = true; // Leave the loop after this iteration
//                     break;
//                 case SDL_KEYDOWN:
//                     if(e.key.keysym.sym == SDLK_ESCAPE){
//                         //on charge la partie 1
//                         etat=DEBUT;
//                     }
//                     break;
//             }
//         }

//         program.use();
//         menu.Draw(program);

//         windowManager.swapBuffers();
// }


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
void recharger(){
    //partie charger, sert a avoir le chemin visible + numCaseRot + sensVirage
    listeCameras.at(0)->reset();
    listeCameras.at(1)->reset();
    positionLaterale=0.0;
    positionVerticale=0.0;
    score=0;
    x=largeur;
    taille=1;
    distance=0;
    indiceBoucle=0;
    angleActuel = 0;
    numCaseRot = 5;
    sensRotation = 1;
    distanceAuVirage=1;
    virage = false;
    sensVirage=1; 
    alreadyRotated = false;
    rotationPersonnage=0;
    etat=JEU;
}

//ici il faudra prendre en argument le chemin visible de départ
void recommencer(){
    //partie.charger
    listeCameras.at(0)->reset();
    listeCameras.at(1)->reset();
    positionLaterale=0.0;
    positionVerticale=0.0;
    score=0;
    x=largeur;
    taille=1;
    distance=0;
    indiceBoucle=0;
    angleActuel = 0;
    numCaseRot = casesDerrierePersonnage ;//casesDerrierePersonnage-1;
    sensRotation = 1;
    distanceAuVirage=1;
    virage = false;
    sensVirage=1; 
    alreadyRotated = false;
    rotationPersonnage=0;
    int indiceChemin=0;
    int indiceTest=0;
    etat=JEU;
}