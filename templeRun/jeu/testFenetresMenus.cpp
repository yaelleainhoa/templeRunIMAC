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

    TrackBallCamera cam;

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

    Program program_menu = loadProgram(applicationPath.dirPath() + "shaders/tex2D.vs.glsl",
                    applicationPath.dirPath() + "shaders/tex2D.fs.glsl");

    TTF_Font *font = TTF_OpenFont( (applicationPath.dirPath() + "/assets/fonts/retro.ttf").c_str(), 15 ); 
    TTF_Font *fontMenu = TTF_OpenFont( (applicationPath.dirPath() + "/assets/fonts/retro.ttf").c_str(), 45 ); 

    if(!font){
        std::cout<<applicationPath.dirPath()+ "assets/fonts/retro.ttf"<<std::endl;
    }
    SDL_Color textColor = { 255, 255, 255 };

    Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                    applicationPath.dirPath() + "shaders/lumieresvec.fs.glsl");
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

    Piece piece10(0,0);//id=0-> val=10, mvt=1
    Piece piece20(1,0);
    Piece piece50(2,0);
   // Obstacle obstaclePasGrav(1); //gravité=1,taille=2, mvt=0

    Case case1(0);//aucun trou
    Case case0(0);
    Case case2(0);
    Case case3(1);
    //case1.ajouterObjetCase(piece10,1);
    case0.ajouterObjetCase(piece10,-1);
    case2.ajouterObjetCase(piece20, 1);
    case3.ajouterObjetCase(piece50,0);

    std::deque<Case> parcoursTest=creerCasesAvecDanger();
    /*parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case3);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case0);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case0);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);
    parcoursTest.push_back(case1);*/


    Partie partie1("partie1", parcoursTest);

    std::cout <<"parcours test : ---------------------------------------------------------\n";
    std::cout<<"size:  "<<parcoursTest.size()<<std::endl;
    for(int i=0; i<parcoursTest.size(); i++)
    {
        if(!parcoursTest[i].ssCaseGauche.getObjet().empty())
        {   std::vector<Objet> objets = parcoursTest[i].ssCaseGauche.getObjet();
            std::cout <<"--------Gauche------------"<<std::endl;
            for(int j=0; j<objets.size(); j++)
            {
                std::cout <<"type objet :"<<objets[j].getTypeObjet()<<std::endl;
                std::cout <<"id objet :"<<objets[j].getIdObjet()<<std::endl;
                std::cout <<"mvt objet :"<<objets[j].getTypeObjet()<<std::endl;
            }
            std::cout<<std::endl;
            objets = parcoursTest[i].ssCaseMilieu.getObjet();
            std::cout <<"--------Milieu------------"<<std::endl;
            for(int j=0; j<objets.size(); j++)
            {
                std::cout <<"type objet :"<<objets[j].getTypeObjet()<<std::endl;
                std::cout <<"id objet :"<<objets[j].getIdObjet()<<std::endl;
                std::cout <<"mvt objet :"<<objets[j].getTypeObjet()<<std::endl;
            }
            std::cout<<std::endl;
            objets = parcoursTest[i].ssCaseDroite.getObjet();
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
    partie1.setEtat(1);

    std::deque<Partie> parties;
    Jeu jeu(parties);

    Joueur joueur1;

    //Creations des fenetres textuelles
    TableauDeScore menu(font, textColor);
    menu.setTableauDeScore(partie1, jeu);
    menu.creation();

    MenuPause menuPause(fontMenu, textColor);
    menuPause.creation();

    MenuDebutDePartie menuDebut(fontMenu, textColor);
    menuDebut.creation();

    Mort menuMort(fontMenu, textColor);
    menuMort.creation();

    EntrerNomDeLaPartie menuNom(fontMenu, textColor);
    menuNom.creation();

    Warning menuWarning(fontMenu, textColor);
    menuWarning.creation();

    // std::vector<Partie> parties;
    // for(int i=0; i<5; i++){
    //     Partie partie("yoyo");
    //     parties.push_back(partie);
    // }

    // AffichageAnciennesPartiesSauvegardees menuAnciennesParties(fontMenu, textColor);
    // menuAnciennesParties.setAnciennesParties(parties);
    // menuAnciennesParties.creation();

    // AffichageMeilleursScores menuMeilleursScores(fontMenu, textColor);
    // menuMeilleursScores.setMeilleursParties(parties);
    // menuMeilleursScores.creation();
    

    //Creations des matrices
    ProjMatrix= glm::perspective(glm::radians(70.f), (float)width/height, 0.1f, 100.0f);

    //Creations des objets (à mettre dans une fonction setObjets())
    std::vector<Model> personnages;
    Model ourModel(applicationPath.dirPath() + "assets/models/poussette/poussette.obj");
    Model sphereModel(applicationPath.dirPath() + "assets/models/mars/planet.obj");
    Model skybox(applicationPath.dirPath() + "assets/models/skybox/skybox.obj");
    personnages.push_back(ourModel);
    personnages.push_back(sphereModel);
    personnages.push_back(skybox);

    //creation du terrain
    std::vector<Model> sols;
    std::vector<Model> murs;
    std::vector<Model> pieces;
    std::vector<Model> obstacles;

    // std::deque<int> tableauDeSols;
    // for(int i=0; i<20; i++){
    //     tableauDeSols.push_back(i%3+1);}

    setTerrain(applicationPath.dirPath(), sols, murs, pieces, obstacles);


    //Creation de lumières

    //directionnelles
    LumieresScenes lumScene;
    lumScene.addLumiere(Lumiere(glm::vec4(0,1,0,0), glm::vec3(0.2,0.2,0.6)));

    //ponctuelles
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,1,1), glm::vec3(252/255.0*5, 186/255.0*5, 3/255.0*5)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,0,1), glm::vec3(252/255.0*5, 186/255.0*5, 3/255.0*5)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,1,1), glm::vec3(252/255.0*5, 186/255.0*5, 3/255.0*5)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,0,1), glm::vec3(252/255.0*5, 186/255.0*5, 3/255.0*5)));

    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieres"), lumScene.getSize());
    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieresPonct"), lumScenePonct.getSize());

    setLumieresIntensites(lumScene, lumScenePonct, program);


    // creation d'un vecteur de caméras pour simplifier le changement de caméra
    listeCameras.push_back(new TrackBallCamera);
    listeCameras.push_back(new FreeflyCamera);

    //indice pour le vecteur de caméras : quand indiceCam = 0 c'est la TrackballCamera
    // quand indiceCam = 1 c'est la FreeFly
    //int indiceCam = 0;




    // Application loop:
    bool done = false;
    while(!done) {
        //Etat menu du début
        if(etat==DEBUT){
            debut(etat, program_menu, windowManager, menuDebut, done);
        }

        //Etat de pause
        else if(etat==PAUSE){
            pause(etat, program_menu, windowManager, menuPause, done);
        }

        else if(etat==SAUVEGARDER){
            nom(etat, program_menu, windowManager, menuNom, done);
        }

        else if(etat==ANCIENNESPARTIES){
            debut(etat, program_menu, windowManager, menuDebut, done);//recharger(etat, program_menu, windowManager, menuAnciennesParties, done);
        }

        else if(etat==MEILLEURSSCORES){
            debut(etat, program_menu, windowManager, menuDebut, done);//meilleursScores(etat, program_menu, windowManager, menuMeilleursScores, done);
        }

        else if(etat==WARNING){
            warning(etat, program_menu, windowManager, menuWarning, done);
        }

        else if(etat==MORT){
            mort(etat, program_menu, windowManager, menuMort, done);
        }
        

        //Etat de jeu
        else{
            if(etat==RECOMMENCER){
                recommencer();
            }
            if(etat==RECHARGER){
                recharger();
            }
            // Event loop:
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            SDL_Event e;
            while(windowManager.pollEvent(e)) {
                switch(e.type){
                    case SDL_QUIT:
                        done = true; // Leave the loop after this iteration
                        break;
                    case SDL_KEYDOWN:
                        if(e.key.keysym.sym == SDLK_q){
                            if (positionLaterale!=-1){
                                positionLaterale-=1;
                                joueur1.mvtGauche();
                            }
                        }
                        if(e.key.keysym.sym == SDLK_d)
                            if (positionLaterale!=1){
                                positionLaterale+=1;
                                joueur1.mvtDroite();
                            }
                        if(e.key.keysym.sym == SDLK_z){
                            x=0;
                            joueur1.saut();
                        }
                        if(e.key.keysym.sym == SDLK_s){
                            xBaisse=0;
                            joueur1.glissade();
                        }
                        if(e.key.keysym.sym == SDLK_m){
                            etat=MORT;
                        }
                        if(e.key.keysym.sym == SDLK_ESCAPE){
                            etat=PAUSE;
                        }

                        //CHEAT CODE
                        if(e.key.keysym.sym == SDLK_b){
                            CHEATCODE="b";
                        }
                        if(e.key.keysym.sym == SDLK_i){
                            CHEATCODE+="i";
                            if(CHEATCODE=="biri"){
                                partie1.incrementeScore(1000);
                                menu.updateScore(partie1);
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
                        indiceCam = 1;
                        listeCameras.at(1)->reset();
                    }

                    break;
                }
            }
//std::cout << "distanceAuVirage = "<< distanceAuVirage << std::endl;
            /*********************************
             * HERE SHOULD COME THE RENDERING CODE
             *********************************/
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

            if(x<2*largeur){
                x+=0.02;
            }
            // if(saut()==0){
            //     joueur1.sol();
            // }
            if(xBaisse<2*largeur){
                xBaisse+=0.02;
            }
            // if(baisser()==1){
            //     joueur1.sol();
            // }
            positionVerticale=saut();
            taille=baisser();

            // std::cout<<"position verticale : "<<joueur1.getPositionVerticale()<<std::endl;
            // std::cout<<"position horizontale : "<<joueur1.getPositionHorizontale()<<std::endl;

            //on envoie la position de la lumière au shader, qui change quand la cam bouge
            setLumieresPositions(lumScene, lumScenePonct, program, VMatrix);

            drawTerrain(program,sols, murs, pieces, obstacles, angle, menu, parcoursTest, joueur1, partie1, menu);

        // point de vue camera comme si l'on était dans les yeux du personnage : du coup pas besoin de tracer le personnage
        if(indiceCam != 1){
            drawPersonnage(program, personnages, 0, -90*M_PI/180.0,
                            1, taille, 1,
                            positionLaterale, positionVerticale+0.3);
        }
        
        drawPersonnage(program, personnages, 2, 0,
                        1,1,1,
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

    ourModel.destroy();
    destroyTerrain(sols, murs, pieces, obstacles);


    return EXIT_SUCCESS;
}
