#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>

#include <SDL/SDL.h>
#include "SDL/SDL_ttf.h"
#include <string>
#include <deque>

#include "../glimac/src/stb_image.h"

#include "include/variablesGlobales.hpp"

//rendu
#include "include/trackballCamera.hpp"
#include "include/freeflyCamera.hpp"
#include "include/model.hpp"
#include "include/texture.hpp"
#include "include/lumiere.hpp"
#include "include/renderingTerrain.hpp"
#include "include/fenetresTextuelles.hpp"
#include "include/etatDuJeu.hpp"
#include "include/Jeu.hpp"
#include "include/Objets.hpp"
#include "include/Personnage.hpp"
#include "include/Cases.hpp"

//jeu
// #include "include/Jeu.hpp"

#define GLM_SWIZZLE
#include <glm/glm.hpp>


std::string CHEATCODE;
GLuint width = 800, height=600 ;

//singes
std::vector<float> distanceSingePerso;

using namespace glimac;


int main(int argc, char** argv) {

    //TrackBallCamera cam;

    if( TTF_Init() == -1 ) { 
		return false; 
	} 

    // Initialize SDL and open a window
    SDLWindowManager windowManager(width, height, "templeRun");

    // Initialize glew for OpenGL3+ support
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


    std::unique_ptr<Image> imageMenuPause = loadImage(applicationPath.dirPath()  + "assets/textures/menuPause.png");


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    const float radius=2, min=0, max=360;
    float angle = 0;



/*---ensuite, on instancie le chemin de base, qui sera changé si on décide de charger une ancienne partie
et qu'on réutilise si le joueur souhaite recommencer une partie---*/

    Piece piece10(0,0);//id=0-> val=10, mvt=1
    Piece piece20(1,0);
    Piece piece50(2,0);
    Obstacle obstaclePasGrav(2); //gravité=1,taille=1, mvt=0
    Obstacle velo(1);
    
    Obstacle obstaclePasGrav(1); //gravité=1,taille=2, mvt=0

    Case case1(0);//aucun trou
    Case case0(0);
    Case case2(0);
    Case case3(1);
    Case case4(0);
    Case case5(0);
    
    case0.ajouterObjetCase(piece10,-1);
    case2.ajouterObjetCase(piece20, 1);
    case3.ajouterObjetCase(piece50,0);
    case4.ajouterObjetCase(obstaclePasGrav,0);
    case5.ajouterObjetCase(velo,1);
    case1.ajouterObjetCase(piece10,-1);
    std::deque<Case> parcoursDepart;
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);
    parcoursDepart.push_back(case1);

    std::deque<Case> parcoursTest=creerCasesAvecDanger();
    /*parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case4);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case3);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case0);
    //parcoursTest.push_back(case5);
    parcoursTest.push_back(case4);
    parcoursTest.push_back(case1);
    //parcoursTest.push_back(case5);
    
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case4);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case0);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case4);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);*/
    Partie partieEnCours("partieEnCours", parcoursDepart);
    partieEnCours.setEtat(DEBUT);


    Partie partie1("partie1", parcoursTest);
    int compteur = 0;
    std::cout <<"parcours test : ---------------------------------------------------------\n";
    for(int i=0; i<parcoursTest.size(); i++)
    {
        if(!(parcoursTest[i].ssCaseGauche.getObjet().empty()))
        {   std::vector<Objet> objets = parcoursTest[i].ssCaseGauche.getObjet();
            std::cout <<"--------Gauche------------"<<std::endl;
            for(int j=0; j<objets.size(); j++)
            {   
                if(objets[j].getTypeObjet() == 1 && objets[j].getIdObjet() == 0) compteur++;
                std::cout <<"type objet :"<<objets[j].getTypeObjet()<<std::endl;
                std::cout <<"id objet :"<<objets[j].getIdObjet()<<std::endl;
                std::cout <<"mvt objet :"<<objets[j].getTypeObjet()<<std::endl;
            }
            std::cout<<std::endl;
        }
        if(!(parcoursTest[i].ssCaseMilieu.getObjet().empty()))
        { 
            std::vector<Objet> objets = parcoursTest[i].ssCaseMilieu.getObjet();
            std::cout <<"--------Milieu------------"<<std::endl;
            for(int j=0; j<objets.size(); j++)
            {
                std::cout <<"type objet :"<<objets[j].getTypeObjet()<<std::endl;
                std::cout <<"id objet :"<<objets[j].getIdObjet()<<std::endl;
                std::cout <<"mvt objet :"<<objets[j].getTypeObjet()<<std::endl;
            }
            std::cout<<std::endl;
        }
        if(!(parcoursTest[i].ssCaseDroite.getObjet().empty()))
        { 
            std::vector<Objet> objets = parcoursTest[i].ssCaseDroite.getObjet();
            std::cout <<"--------Droite------------"<<std::endl;
            for(int j=0; j<objets.size(); j++)
            {
                std::cout <<"type objet :"<<objets[j].getTypeObjet()<<std::endl;
                std::cout <<"id objet :"<<objets[j].getIdObjet()<<std::endl;
                std::cout <<"mvt objet :"<<objets[j].getTypeObjet()<<std::endl;
            }
            std::cout<<std::endl;
        }
        
    }
    std::cout << "compteur de tancarvilles = " << compteur << std::endl;
    partie1.setEtat(1);
/*--- avant tout, on instancie le Jeu, pour ça, on récupère les parties sauvegardées et les meilleurs parties---*/
    // std::vector<Partie> partiesMeilleursScores;
    // std::deque<Partie> partiesSauvegardees;
    /*------------SAUVEGARDES------------------*/
    // Partie partieSauvegardees1 = charger("longuepartie");
    // Partie partieSauvegardees2 = charger("intersection");
    // Partie partieSauvegardees3 = charger("intersection");
    // Partie partieSauvegardees4 = charger("intersection");
    // Partie partieSauvegardees5 = charger("intersection");

    // partiesSauvegardees.push_back(partieSauvegardees1);  
    // partiesSauvegardees.push_back(partieSauvegardees2);  
    // partiesSauvegardees.push_back(partieSauvegardees3);  
    // partiesSauvegardees.push_back(partieSauvegardees4);  
    // partiesSauvegardees.push_back(partieSauvegardees5); 

    Joueur joueur1;
    distanceSingesPerso = joueur1.singes().getDistancePerso();
    // /*------------MEILLEURS SCORES------------------*/
    // Partie meilleurePartie1 = charger("intersection");
    // Partie meilleurePartie2 = charger("intersection");
    // Partie meilleurePartie3 = charger("intersection");
    // Partie meilleurePartie4 = charger("intersection");
    // Partie meilleurePartie5 = charger("intersection");

    // partiesMeilleursScores.push_back(meilleurePartie1);
    // partiesMeilleursScores.push_back(meilleurePartie2);
    // partiesMeilleursScores.push_back(meilleurePartie3);
    // partiesMeilleursScores.push_back(meilleurePartie4);
    // partiesMeilleursScores.push_back(meilleurePartie5);

    Jeu jeu("partiesSauvegardees", "meilleursScores");
    Joueur joueur;
    std::vector<std::pair<std::string, int>> partiesMeilleursScores=jeu.getListeMeilleuresParties();
    std::deque<Partie> partiesSauvegardees=jeu.getPartiesSauvegardees();

/*----- creation des fenetres textuelles du jeu-----*/
    TableauDeScore menu(font, textColor);
    menu.setTableauDeScore(partieEnCours, jeu);
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

    Warning menuWarning(fontMenu, textColor);
    menuWarning.creation();

    AffichageAnciennesPartiesSauvegardees menuAnciennesParties(fontMenu, textColor);
    menuAnciennesParties.setAnciennesParties(partiesSauvegardees);
    menuAnciennesParties.creation();

    AffichageMeilleursScores menuMeilleursScores(fontMenu, textColor);
    menuMeilleursScores.setMeilleursParties(partiesMeilleursScores);
    menuMeilleursScores.creation();
    

/*----- creation des matrices-----*/
    ProjMatrix= glm::perspective(glm::radians(70.f), (float)width/height, 0.1f, 100.0f);

/*----- creation des personnages et de la skybox-----*/
    std::vector<Model> personnages;
    Model personnage(applicationPath.dirPath() + "assets/models/poussette/poussette.obj");
    Model singe(applicationPath.dirPath() + "assets/models/singe/twingo.obj");
    Model skybox(applicationPath.dirPath() + "assets/models/skybox/skybox.obj");
    personnages.push_back(ourModel);
    // pour l'instant sphereModel c'est notre singe
    personnages.push_back(sphereModel);
    personnages.push_back(personnage);
    personnages.push_back(singe);
    personnages.push_back(skybox);

/*----- creation du terrain et objets-----*/
    std::vector<Model> sols;
    std::vector<Model> murs;
    std::vector<Model> pieces;
    std::vector<Model> obstacles;
    setTerrain(applicationPath.dirPath(), sols, murs, pieces, obstacles);


/*----- creation des lumières-----*/

    //DIRECTIONNELLES
    LumieresScenes lumScene;
    lumScene.addLumiere(Lumiere(glm::vec4(0,1,0,0), glm::vec3(0.2,0.2,0.6)));

    //PONCTUELLES
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,1,1), glm::vec3(252/255.0*5, 186/255.0*5, 3/255.0*5)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,0,1), glm::vec3(252/255.0*5, 186/255.0*5, 3/255.0*5)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,1,1), glm::vec3(252/255.0*5, 186/255.0*5, 3/255.0*5)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,0,1), glm::vec3(252/255.0*5, 186/255.0*5, 3/255.0*5)));

    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieres"), lumScene.getSize());
    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieresPonct"), lumScenePonct.getSize());

    setLumieresIntensites(lumScene, lumScenePonct, program);

/*----- creation d'un vecteur de caméras pour simplifier le changement de caméra---*/
    listeCameras.push_back(new TrackBallCamera); //indiceCam=0
    listeCameras.push_back(new FreeflyCamera); //indiceCam=1
 


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
            //voir si on ajoute un warning
            jeu.ajoutePartieSauvergardee(partieEnCours);
            jeu.sauvegarderJeu("partiesSauvegardees");
            jeu.ajouteMeilleurePartie(partieEnCours);
            jeu.sauvegarderMeilleur("meilleursScores");
            partieEnCours.setEtat(DEBUT);
        }

        else if(partieEnCours.getEtat()==ANCIENNESPARTIES){
            rechargerParties(program_menu, windowManager, menuAnciennesParties, done, partiesSauvegardees, partieEnCours);
        }

        else if(partieEnCours.getEtat()==MEILLEURSSCORES){
            meilleursScores(program_menu, windowManager, menuMeilleursScores, done, partieEnCours);
        }

        else if(partieEnCours.getEtat()==WARNING){
            warning(program_menu, windowManager, menuWarning, done, partieEnCours);
        }

        else if(partieEnCours.getEtat()==MORT){
            mort(program_menu, windowManager, menuMort, done, partieEnCours);
            jeu.ajouteMeilleurePartie(partieEnCours);
            jeu.sauvegarderMeilleur("meilleursScores");
        }

        else if(partieEnCours.getEtat()==RECOMMENCER){
            //jeu.partieEnCours.cheminVisible=parcoursDepart;
            partieEnCours.resetPartie(parcoursDepart);
            recommencer(partieEnCours);
        }
        else if(partieEnCours.getEtat()==RECHARGER){
            menu.updateScore(partieEnCours);
            menu.updateDistance(partieEnCours);
            partieEnCours.setEtat(JEU);
        }

/*-------------------------------------*/
/*--------------JEU--------------------*/
/*-------------------------------------*/

        else{
            // Event loop:
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            SDL_Event e;
            while(windowManager.pollEvent(e)) {
                switch(e.type){
                    case SDL_QUIT:
                        done = true;
                        break;
                    case SDL_KEYDOWN:
                        if(e.key.keysym.sym == SDLK_q){
                            if (positionLaterale!=-1){
                                positionLaterale-=1;
                                listeCameras.at(1)->moveLeft(1.5f);
                                joueur1.mvtGauche();
                                joueur.mvtGauche();
                            }
                        }
                        if(e.key.keysym.sym == SDLK_d)
                            if (positionLaterale!=1){
                                positionLaterale+=1;
                                listeCameras.at(1)->moveLeft(-1.5f);
                                joueur1.mvtDroite();
                                joueur.mvtDroite();
                            }
                        if(e.key.keysym.sym == SDLK_z){
                            x=0;
                            joueur1.saut();
                            EstCeQuePersoSaute = true;
                            if(std::abs(x-largeur)<0.02){
                                x=0;
                                joueur.saut();
                            }
                        }
                        if(e.key.keysym.sym == SDLK_s){
                            xBaisse=0;
                            joueur1.glissade();
                            EstCeQuePersoBaisse = true;
                            std::cout<<"position verticale dans fonction key : "<<joueur1.getPositionVerticale()<<std::endl;
                            //le joueur peut se baisser puis sauter 
                            //mais s'il est en l'air il ne peut pas se baisser!
                            if(joueur.getPositionVerticale()==0 && std::abs(xBaisse-largeur)<0.02){
                                xBaisse=0;
                                joueur.glissade();
                            }
                        }
                        if(e.key.keysym.sym == SDLK_m){
                            partieEnCours.setEtat(MORT);
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
                                partieEnCours.incrementeScore(1000);
                                menu.updateScore(partieEnCours);
                            }
                        }
                        if(e.key.keysym.sym == SDLK_r){
                            CHEATCODE+="r";
                        }
                    // changement de caméras 
                    if(e.key.keysym.sym == SDLK_c){
                        std::cout  << "indiceCam = "<< indiceCam << std::endl;
                        if(indiceCam == 0) indiceCam = 1;
                        else indiceCam = 0;
                        std::cout  << "indiceCam = "<< indiceCam << std::endl;
                    }
                    if(e.key.keysym.sym == SDLK_l){
                        indiceCam = 0;
                        listeCameras.at(0)->reset();
                    }

                    break;
                }
            }

        if(windowManager.isKeyPressed(SDLK_RIGHT)){
            if(distanceAuVirage>0.95 || distanceAuVirage==0.0){
                listeCameras.at(indiceCam)->rotateLeft(valIncremCameraRotationRIGHT);
                //phi = listeCameras.at(1)->getPhi();
                virage=false;
            }
            else{
                sensVirage=-1;
                virage=true;
            }
        }
        if(windowManager.isKeyPressed(SDLK_LEFT)){
            if(distanceAuVirage>0.95 || distanceAuVirage==0.0){
                listeCameras.at(indiceCam)->rotateLeft(valIncremCameraRotationLEFT);
                //phi = listeCameras.at(1)->getPhi();
                virage=false;
            }
            else{
                sensVirage=1;
                virage=true;
            }
        }
        //Pas besoin de rotateUp pour la Trackball d'où le .at(1) --> correspond à la freeflycamera
        if(windowManager.isKeyPressed(SDLK_UP)){
            listeCameras.at(1)->rotateUp(valIncremCameraRotationUP);
        }
        if(windowManager.isKeyPressed(SDLK_DOWN)){
            listeCameras.at(1)->rotateUp(valIncremCameraRotationDOWN);
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

            if(x<=largeur){
                x+=0.02;
            }
            // position du joueur remise à 0 après un saut, pour eviter les erreurs de singe (la positoin du joueur restait à 1 après un saut)
            if(saut(x)<=0.01 && EstCeQuePersoSaute==true){
                joueur1.sol();
                EstCeQuePersoSaute = false;
            }

            if(xBaisse<2*largeur){
            if(xBaisse<=largeur){
                xBaisse+=0.02;
            }
            // position du joueur remise à 0 après une glissade
            if(baisser()==1 && EstCeQuePersoBaisse==true){
                joueur1.sol();
                EstCeQuePersoBaisse = false;
            }

            positionVerticale=saut(x);
            listeCameras.at(1)->moveUp(positionVerticale);
            positionVerticale=saut();
            if(std::abs(x-largeur)<0.02 && std::abs(xBaisse-largeur)<0.02){
                joueur.sol();
            }
            taille=baisser();
            positionVerticaleGlissade = -saut(xBaisse);
            if(taille != 1.0) listeCameras.at(1)->moveUp(positionVerticaleGlissade*0.7f);

            //on envoie la position de la lumière au shader, qui change quand la cam bouge
            setLumieresPositions(lumScene, lumScenePonct, program, VMatrix);

            drawTerrain(program,sols, murs, pieces, obstacles, angle, menu, partieEnCours, joueur);

        // point de vue camera comme si l'on était dans les yeux du personnage : du coup pas besoin de tracer le personnage
        if(indiceCam != 1){
            drawPersonnage(program, personnages, 0, -90*M_PI/180.0,
                            1, taille, 1,
                            positionLaterale, positionVerticale+0.3);
        }
        // Gestion du Singe 
        // 3 états : 0 --> il n'est pas dessiné, 1 --> il est dessiné et poursuit le joueur, 2 --> il mange le joueur
        if(etatSinges != 0){
                // le joueur a touché un obstacle, le singe se rapproche progressivement
                if(etatSinges == 1 && distanceSingesPerso > 0.8*largeur){
                    drawPersonnage(program, personnages, 1, 0,
                                    0.05,taille*0.05,0.05,
                                    0, 0.5, distanceSingesPerso);
                    distanceSingesPerso -= 0.04;
                    NB_TOURS_SINGES = joueur1.singes().getToursRestants();
                }
                // le joueur a percuté une deuxième fois un obstacle dans une des 5 cases suivantes --> le joueur meurt
                else if(etatSinges == 2) etat = MORT; 
                // le singe a fini de se rapprocher, il suit le joueur de très près pendant les 5 prochaines cases
                // NB_TOURS_SINGES est décrémenté dans la fonction drawTerrain() à chaque case (?)
                if(distanceSingesPerso <= 0.8*largeur){
                    drawPersonnage(program, personnages, 1, 0,
                                    0.05,taille*0.05,0.05,
                                    0, 0.5, distanceSingesPerso);
                }         
        }
        // cas où le perso a touché un obstacle mais n'en a pas retouché un les 5 cases qui ont suivies
        // etatSinges retourne à 0 (dans drawTerrain()) quand le nombre de tours restants = 0 
        else if(etatSinges == 0 && poursuite1 == true){
            // le singe recule, operation inverse de celle faite pour etatSinge = 1
            if(distanceSingesPerso < 2*largeur){
                drawPersonnage(program, personnages, 1, 0,
                                    0.05,taille*0.05,0.05,
                                    0, 0.5, distanceSingesPerso);
                    distanceSingesPerso += 0.02;
            }else{ poursuite1 = false; poursuite2 = false;} // une fois reculer, on remet tout à false, le singe n'est plus dessiné
        }
        //skybox
        drawPersonnage(program, personnages, 2, 0,
                        2,2,2,
                        0,0,0);

            //création des singes
            // ModelMatrix = glm::mat4(1.0f);
            // ModelMatrix = glm::translate(ModelMatrix, glm::vec3(largeur*0.5, positionVerticale+0.5, 4.0f)); // translate it down so it's at the center of the scene
            // ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));	
            // sphereModel.Draw(program);

             program_menu.use();
             menu.Draw(program_menu);
            // distanceSingePerso.push_back(distanceCase(ModelMatrix));

            // ModelMatrix = glm::mat4(1.0f);
            // ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-largeur*0.5, positionVerticale+0.5, 4.0f));
            // ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.1f, 0.1f, 0.1f));	
            // sphereModel.Draw(program);

            // distanceSingePerso.push_back(distanceCase(ModelMatrix));        
            // for(float d : distanceSingePerso){
            //     if(std::abs(d) < 0.7){
            //         std::cout << "le perso est mort ! " << d << std::endl;
            //     }
            // }

            // Update the display
            windowManager.swapBuffers();
        }

    }

    personnage.destroy();
    destroyTerrain(sols, murs, pieces, obstacles);


    return EXIT_SUCCESS;
}
