#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <assert.h>

#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include <string>
#include <deque>

#include "../glimac/src/stb_image.h"

#include "include/variablesGlobales.hpp"

#include "include/trackballCamera.hpp"
#include "include/freeflyCamera.hpp"
#include "include/model.hpp"
#include "include/texture.hpp"
#include "include/lumiere.hpp"
#include "include/drawTerrain.hpp"
#include "include/renderingTerrain.hpp"
#include "include/fenetresTextuelles.hpp"
#include "include/etatDuJeu.hpp"
#include "include/Jeu.hpp"
#include "include/Objets.hpp"
#include "include/Personnage.hpp"
#include "include/Cases.hpp"


#define GLM_SWIZZLE
#include <glm/glm.hpp>


std::string CHEATCODE;
GLuint width = 800, height=600 ;


std::vector<float> distanceSingePerso;

using namespace glimac;


int main(int argc, char** argv) {

    /*********************************
     * INITIALISATION
     *********************************/

    if( TTF_Init() == -1 ) { 
		return false; 
	} 

    SDLWindowManager windowManager(width, height, "Babymac Escape");

    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);

    Program program_menu = loadProgram(applicationPath.dirPath() + "shaders/menus.vs.glsl",
                    applicationPath.dirPath() + "shaders/menus.fs.glsl");

    TTF_Font *font = TTF_OpenFont( (applicationPath.dirPath() + "/assets/fonts/retro.ttf").c_str(), 15 ); 
    TTF_Font *fontMenu = TTF_OpenFont( (applicationPath.dirPath() + "/assets/fonts/retro.ttf").c_str(), 45 ); 

    if(!font){
        std::cout<<applicationPath.dirPath()+ "assets/fonts/retro.ttf"<<std::endl;
    }
    SDL_Color textColor = { 255, 255, 255 };

    Program program = loadProgram(applicationPath.dirPath() + "shaders/objets.vs.glsl",
                    applicationPath.dirPath() + "shaders/objets.fs.glsl");
    program.use();

    /*********************************
     * PREPARATION DES VARIABLES
     *********************************/

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);

/*---------------------Jeu------------------------------*/

    Jeu* jeu = Jeu::getInstance();
    jeu->chargerJeu("partiesSauvegardees", "meilleursScores");
    Joueur joueur;
    std::vector<std::pair<std::string, int>> partiesMeilleursScores=jeu->getListeMeilleuresParties();
    std::deque<Partie> partiesSauvegardees=jeu->getPartiesSauvegardees();


/*---creation de cases aléatoires avec obstacles ou non---*/

    std::deque<Case> parcoursAvecDanger=creerCasesAvecDanger();
    std::deque<Case> parcoursSansDanger=creerCasesSansDanger();

    std::vector<std::deque<Case>> parcoursPossibles;
    parcoursPossibles.push_back(parcoursSansDanger);
    parcoursPossibles.push_back(parcoursAvecDanger);

    Partie partieEnCours("partieEnCours", initialiseParcoursDepart(parcoursPossibles));
    partieEnCours.setEtat(DEBUT);

/*-------creation des fenetres textuelles du jeu-------*/
    TableauDeScore menu(font, textColor);
    menu.setTableauDeScore(partieEnCours);
    menu.creation();

    MenuPause menuPause(fontMenu, textColor);
    menuPause.creation();

    MenuDebutDePartie menuDebut(fontMenu, textColor);
    menuDebut.creation();

    Mort menuMort(fontMenu, textColor);
    menuMort.creation();

    EntrerNomDeLaPartie menuNom(fontMenu, textColor);
    menuNom.setNomPartie(nomDePartie);
    menuNom.creation();

    AffichageAnciennesPartiesSauvegardees menuAnciennesParties(fontMenu, textColor);
    menuAnciennesParties.setAnciennesParties(partiesSauvegardees);
    menuAnciennesParties.creation();

    AffichageMeilleursScores menuMeilleursScores(fontMenu, textColor);
    menuMeilleursScores.setMeilleursParties(partiesMeilleursScores);
    menuMeilleursScores.creation();
    

/*----------------creation des matrices-----------------*/
    ProjMatrix= glm::perspective(glm::radians(70.f), (float)width/height, 0.1f, 100.0f);

/*--------creation des personnages et de la skybox--------*/
    std::vector<Model> personnages;
    Model personnage(applicationPath.dirPath() + "assets/models/poussette/poussette.obj");
    Model singe(applicationPath.dirPath() + "assets/models/singe/twingo.obj");
    Model skybox(applicationPath.dirPath() + "assets/models/skybox/skybox.obj");
    personnages.push_back(personnage);
    personnages.push_back(singe);
    personnages.push_back(skybox);

    distanceSingesPerso = joueur.singes().getDistancePerso();


/*---------creation du terrain et objets-----*/
    std::vector<Model> sols;
    std::vector<Model> murs;
    std::vector<Model> pieces;
    std::vector<Model> obstacles;
    setTerrain(applicationPath.dirPath(), sols, murs, pieces, obstacles);

/*----------creation des lumières----------*/

    //DIRECTIONNELLES
    LumieresScenes lumScene;
    lumScene.addLumiere(Lumiere(glm::vec4(0,1,0,0), glm::vec3(79/255., 45/255., 173/255.)));
    //dans le shader le tableau de lumières a une taille prédéfinie, il vaut mieux ne pas la dépasser...
    assert(lumScene.getSize()<3 && "le nombre de lumières diffuses ne doit pas dépasser 2");

    //PONCTUELLES
    lumScenePonct.addLumiere(Lumiere(glm::vec4(0,1,0,1), glm::vec3(252/255.0*4, 186/255.0*4, 3/255.0*4)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(0,1,0,1), glm::vec3(252/255.0*4, 186/255.0*4, 3/255.0*4)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(0,1,0,1), glm::vec3(252/255.0*4, 186/255.0*4, 3/255.0*4)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(0,1,0,1), glm::vec3(252/255.0*4, 186/255.0*4, 3/255.0*4)));
    assert(lumScenePonct.getSize()<10 && "le nombre de lumières ponctuelles ne doit pas dépasser 10");


    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieres"), lumScene.getSize());
    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieresPonct"), lumScenePonct.getSize());

    setLumieresIntensites(lumScene, lumScenePonct, program);

/*----- creation d'un vecteur de caméras pour simplifier le changement de caméra---*/
    const float radius=2, min=0, max=360;
    float angle = 0;
    listeCameras.push_back(new TrackBallCamera); //indiceCam=0
    listeCameras.push_back(new FreeflyCamera); //indiceCam=1
 


    /*********************************
     * AFFICHAGE MENUS
     *********************************/

    bool done = false;
    while(!done) {
        
        if(partieEnCours.getEtat()==DEBUT){
            debut(program_menu, windowManager, menuDebut, done, partieEnCours);
        }

        else if(partieEnCours.getEtat()==DEBUTDEPARTIE){
            nom(program_menu, windowManager, menuNom,done, partieEnCours);
        }

        else if(partieEnCours.getEtat()==PAUSE){
            pause(program_menu, windowManager, menuPause, done, partieEnCours);
        }

        else if(partieEnCours.getEtat()==SAUVEGARDER){
            jeu->ajoutePartieSauvergardee(partieEnCours);
            jeu->sauvegarderJeu("partiesSauvegardees");
            jeu->ajouteMeilleurePartie(partieEnCours);
            jeu->sauvegarderMeilleur("meilleursScores");
            partieEnCours.setEtat(DEBUT);
        }

        else if(partieEnCours.getEtat()==ANCIENNESPARTIES){
            rechargerParties(program_menu, windowManager, menuAnciennesParties, done, partiesSauvegardees, partieEnCours);
        }

        else if(partieEnCours.getEtat()==MEILLEURSSCORES){
            meilleursScores(program_menu, windowManager, menuMeilleursScores, done, partieEnCours);
        }

        else if(partieEnCours.getEtat()==MORT){
            mort(program_menu, windowManager, menuMort, done, partieEnCours);
            jeu->ajouteMeilleurePartie(partieEnCours);
            jeu->sauvegarderMeilleur("meilleursScores");
        }

        else if(partieEnCours.getEtat()==RECOMMENCER){
            joueur.singes().initialiseDistanceSinges();
            partieEnCours.cheminVisible=initialiseParcoursDepart(parcoursPossibles);
            partieEnCours.resetPartie();
            menu.updateDistance(partieEnCours);
            menu.updateScore(partieEnCours);
            recommencer(partieEnCours);
        }
        else if(partieEnCours.getEtat()==RECHARGER){
            menu.updateScore(partieEnCours);
            menu.updateDistance(partieEnCours);
            partieEnCours.setEtat(JEU);
        }

    /*********************************
     * JEU
     *********************************/

/*----------test evenements clavier----------*/

        else{
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            SDL_Event e;
            while(windowManager.pollEvent(e)) {
                switch(e.type){
                    case SDL_QUIT:
                        done = true;
                        break;
                    case SDL_KEYDOWN:
                        if(e.key.keysym.sym == SDLK_q){
                            if((distanceAuVirage>0.95 || distanceAuVirage==0.0) && positionLaterale!=-1){
                                joueur.mvtGauche();
                                positionLaterale=joueur.getPositionHorizontale();
                                listeCameras.at(1)->moveLeft(1.5f);
                                virage=false;
                            }
                            else{
                                sensVirage=1;
                                virage=true;
                            }
                        }
                        if(e.key.keysym.sym == SDLK_d)
                            if ((distanceAuVirage>0.95 || distanceAuVirage==0.0) &&positionLaterale!=1){
                                joueur.mvtDroite();
                                positionLaterale=joueur.getPositionHorizontale();
                                listeCameras.at(1)->moveLeft(-1.5f);
                                virage=false;
                            }
                            else{
                                sensVirage=-1;
                                virage=true;
                            }
                        if(e.key.keysym.sym == SDLK_z){
                            if(std::abs(x-largeur)<0.02){
                                x=0;
                                joueur.saut();
                                EstCeQuePersoSaute = true;
                            }
                        }
                        if(e.key.keysym.sym == SDLK_s){

                            //le joueur peut se baisser puis sauter 
                            //mais s'il est en l'air il ne peut pas se baisser!
                            if(joueur.getPositionVerticale()==0 && std::abs(xBaisse-largeur)<0.02){
                                xBaisse=0;
                                joueur.glissade();
                                EstCeQuePersoBaisse = true;
                            }
                        }
                        if(e.key.keysym.sym == SDLK_ESCAPE){
                            partieEnCours.setEtat(PAUSE);
                        }

                        //CHEAT CODE
                        if(e.key.keysym.sym == SDLK_b){
                            CHEATCODE="b";
                        }
                        if(e.key.keysym.sym == SDLK_i){
                            CHEATCODE+="i";
                            if(CHEATCODE=="biri"){
                                partieEnCours.incrementeScore(100);
                                menu.updateScore(partieEnCours);
                            }
                        }
                        if(e.key.keysym.sym == SDLK_r){
                            CHEATCODE+="r";
                        }
                    // changement de caméras 
                    if(e.key.keysym.sym == SDLK_c){
                        if(indiceCam == 0) indiceCam = 1;
                        else indiceCam = 0;
                    }
                    if(e.key.keysym.sym == SDLK_l){
                        indiceCam = 0;
                        listeCameras.at(0)->reset();
                    }

                    break;
                }
            }

        if(windowManager.isKeyPressed(SDLK_RIGHT)){
            listeCameras.at(indiceCam)->rotateLeft(valIncremCameraRotationRIGHT);
        }
        if(windowManager.isKeyPressed(SDLK_LEFT)){
            listeCameras.at(indiceCam)->rotateLeft(valIncremCameraRotationLEFT);

        }
        //Pas besoin de rotateUp pour la Trackball d'où le .at(1) --> correspond à la freeflycamera
        if(windowManager.isKeyPressed(SDLK_UP)){
            listeCameras.at(1)->rotateUp(valIncremCameraRotationUP);
        }
        if(windowManager.isKeyPressed(SDLK_DOWN)){
            listeCameras.at(1)->rotateUp(valIncremCameraRotationDOWN);
        }

        //pour l'usage de souris (peu adapté au gameplay donc on peut garder les touches du clavier si on préfère)
        glm::vec2 souris=glm::vec2(0,0);
        if(windowManager.isMouseButtonPressed(SDL_BUTTON_LEFT)){
            souris=windowManager.getMousePosition();

            float up=-souris.y/height+0.5; //pour passer des pixels au repère
            float left=souris.x/width-0.5;
                        
            listeCameras.at(indiceCam)->rotateLeft(-0.5*left); //0.5 pour éviter que la caméra bouge trop vite...

            if(indiceCam == 1) listeCameras.at(indiceCam)->rotateUp(0.5*up); 

        }
        //Pas besoin de MoveFront pour la Freefly d'où le .at(0) --> correspond à la trackballcamera
        if(windowManager.isKeyPressed(SDLK_w)){
            mouvementHorizontalTranslation = -1;
            listeCameras.at(0)->moveFront(valIncremCameraBACK);
        }
        if(windowManager.isKeyPressed(SDLK_x)){
            mouvementHorizontalTranslation = 1;
            listeCameras.at(0)->moveFront(valIncremCameraFRONT);
        }
        VMatrix=listeCameras.at(indiceCam)->getViewMatrix();

            program.use();

/*----------position du joueur----------*/

            if(x<=largeur){
                x+=0.02;
            }

            //le joueur revient au sol après son saut
            if(saut(x)<=0.01 && EstCeQuePersoSaute==true){
                joueur.sol();
                EstCeQuePersoSaute = false;
            }

            if(xBaisse<=largeur){
                xBaisse+=0.02;
            }

            //le joueur se redresse après un moment
            if(baisser()==1 && EstCeQuePersoBaisse==true){
                joueur.sol();
                EstCeQuePersoBaisse = false;
            }

            positionVerticale=saut(x);
            listeCameras.at(1)->moveUp(positionVerticale);
            if(std::abs(x-largeur)<0.02 && std::abs(xBaisse-largeur)<0.02){
                joueur.sol();
            }
            taille=baisser();
            positionVerticaleGlissade = -saut(xBaisse);
            if(taille != 1.0) listeCameras.at(1)->moveUp(positionVerticaleGlissade*0.2f);


/*----------dessin du terrain, des lumières, du personnage----------*/

            setLumieresPositions(lumScene, lumScenePonct, program, VMatrix);
            setLumieresIntensites(lumScene, lumScenePonct, program);
            drawTerrain(program,sols, murs, pieces, obstacles, angle, menu, partieEnCours, joueur, parcoursPossibles);

        // si l'on est du point de vue du personnage, on ne le dessine pas
        if(indiceCam != 1){
            drawPersonnage(program, personnages, 0, -90*M_PI/180.0,
                            1, taille, 1,
                            positionLaterale, positionVerticale+0.3);
        }

        //Skybox
        drawPersonnage(program, personnages, 2, -M_PI,
                2,2,2,
                0,0,0);

/*----------singes----------*/

        // 3 états : 0 --> il n'est pas dessiné, 1 --> il est dessiné et poursuit le joueur, 2 --> il mange le joueur
        if(etatSinges != 0){
                // le joueur a touché un obstacle, le singe se rapproche progressivement
                if(etatSinges == 1 && distanceSingesPerso > 0.8*largeur){
                    drawPersonnage(program, personnages, 1, -M_PI,
                                    1,taille*1,1,
                                    0, 0.5, distanceSingesPerso);
                    distanceSingesPerso -= 0.04;
                    NB_TOURS_SINGES = joueur.singes().getToursRestants();
                }
                // le joueur a percuté une deuxième fois un obstacle dans une des 5 cases suivantes --> le joueur meurt
                else if(etatSinges == 2) etat = MORT; 
                // le singe a fini de se rapprocher, il suit le joueur de très près pendant les 5 prochaines cases
                // NB_TOURS_SINGES est décrémenté dans la fonction drawTerrain() à chaque case (?)
                if(distanceSingesPerso <= 0.8*largeur){
                    drawPersonnage(program, personnages, 1, -M_PI,
                                    1,taille*1,1,
                                    0, 0.5, distanceSingesPerso);
                }         
        }
        // cas où le perso a touché un obstacle mais n'en a pas retouché un les 5 cases qui ont suivies
        // etatSinges retourne à 0 (dans drawTerrain()) quand le nombre de tours restants = 0 
        else if(etatSinges == 0 && poursuite1 == true){
            // le singe recule, operation inverse de celle faite pour etatSinge = 1
            if(distanceSingesPerso < 2*largeur){
                drawPersonnage(program, personnages, 1, -M_PI,
                                    1,taille*1,1,
                                    0, 0.5, distanceSingesPerso);
                    distanceSingesPerso += 0.02;
            }
            else{ 
                poursuite1 = false; poursuite2 = false;
                } // une fois reculé, on remet tout à false, le singe n'est plus dessiné
        }
        
    /*----------menu qui affiche le score actuel----------*/

        program_menu.use();
        menu.Draw(program_menu);

    windowManager.swapBuffers();
        }

    }

    return EXIT_SUCCESS;
}
