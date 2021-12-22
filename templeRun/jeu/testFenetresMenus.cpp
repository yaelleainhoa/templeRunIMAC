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
#include "include/trackballCamera.hpp"
#include "include/freeflyCamera.hpp"
#include "include/model.hpp"
#include "include/texture.hpp"
#include "include/lumiere.hpp"
#include "include/renderingTerrain.hpp"
#include "include/jeu.hpp"
#include "include/fenetresTextuelles.hpp"
#include "include/etatDuJeu.hpp"

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


    //Creations des fenetres textuelles
    TableauDeScore menu(font, textColor);
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

    std::vector<Partie> parties;
    for(int i=0; i<5; i++){
        Partie partie("yoyo");
        parties.push_back(partie);
    }

    AffichageAnciennesPartiesSauvegardees menuAnciennesParties(fontMenu, textColor);
    menuAnciennesParties.setAnciennesParties(parties);
    menuAnciennesParties.creation();

    AffichageMeilleursScores menuMeilleursScores(fontMenu, textColor);
    menuMeilleursScores.setMeilleursParties(parties);
    menuMeilleursScores.creation();
    

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

    std::deque<int> tableauDeSols;
    for(int i=0; i<10; i++){
    tableauDeSols.push_back(2);}

    setTerrain(applicationPath.dirPath(), sols, murs);


    //Creation de lumières

    //directionnelles
    LumieresScenes lumScene;
    lumScene.addLumiere(Lumiere(glm::vec4(1,1,1,0), glm::vec3(0.3,0.3,0.3)));

    //ponctuelles
    LumieresScenes lumScenePonct;
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,1,1), glm::vec3(10.0,0.0,10.8)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,0,1), glm::vec3(10.8,0.0,0.0)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,1,0,1), glm::vec3(10.8,0.0,0.0)));

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
            recharger(etat, program_menu, windowManager, menuAnciennesParties, done);
        }

        else if(etat==MEILLEURSSCORES){
            meilleursScores(etat, program_menu, windowManager, menuMeilleursScores, done);
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
                            }
                        }
                        if(e.key.keysym.sym == SDLK_d)
                            if (positionLaterale!=1){
                                positionLaterale+=1;
                            }
                        if(e.key.keysym.sym == SDLK_z){
                            x=0;
                        }
                        if(e.key.keysym.sym == SDLK_s){
                            xBaisse=0;
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
                                score+=100;
                            }
                            menu.updateScore();
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
            if(xBaisse<2*largeur){
                xBaisse+=0.02;
            }
            positionVerticale=saut();
            taille=baisser();

            //on envoie la position de la lumière au shader, qui change quand la cam bouge
            lumScenePonct.changePositionAt(0,glm::vec4(x,0,0,1));
            setLumieresPositions(lumScene, lumScenePonct, program);


            drawTerrain(program, sols, tableauDeSols, murs, angle);

        // point de vue camera comme si l'on était dans les yeux du personnage : du coup pas besoin de tracer le personnage
        if(indiceCam != 1){
            drawPersonnage(program, positionLaterale, positionVerticale+0.3,
                personnages, 0, 1.0f, taille, 1.0f);
        }

            drawObject(program, 0, 0,
                personnages, 2, 0, 0, 0,0,1,1,1,0);

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
    destroyTerrain(sols, murs);


    return EXIT_SUCCESS;
}
