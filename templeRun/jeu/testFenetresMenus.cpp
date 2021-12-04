#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/glm.hpp>


#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include <string>

#include "include/fenetresTextuelles.hpp"


#include <deque>

#include "../glimac/src/stb_image.h"

#include "include/trackballCamera.hpp"
#include "include/model.hpp"
#include "include/texture.hpp"
#include "include/lumiere.hpp"
#include "include/renderingTerrain.hpp"
#include "include/rendering.hpp"


#define GLM_SWIZZLE
#include <glm/glm.hpp>

float largeur=1.5;
float vitesse=2.0;
float hauteur=2.0;
int numeroCase=0;
float positionLaterale=0.0;
float positionVerticale=0.0;
float x=largeur;
int score=0;
int DEBUT=0, PAUSE=1, JEU=2, MEILLEURSSCORES=3, RECHARGER=4;
int etat=DEBUT;
GLuint width = 800, height=600 ;


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
                        etat=JEU;
                    }
                    if(e.key.keysym.sym == SDLK_r){
                        etat=RECHARGER;
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
                    etat=DEBUT;
                }
                if(e.key.keysym.sym == SDLK_m){
                    etat=MEILLEURSSCORES;
                }
                break;
        }
    }

    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    program.use();
    menu.Draw(program);

    // Update the display
    windowManager.swapBuffers();
}

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


    //Creations des fenetres textuelles
    TableauDeScore menu(font, textColor);
    menu.creationTableauDeScore(30,40,2);

    MenuPause menuPause(fontMenu, textColor);
    menuPause.creationMenuPause();

    MenuDebutDePartie menuDebut(fontMenu, textColor);
    menuDebut.creationMenuDebutDePartie();
    

    //Creations des matrices
    glm::mat4 VMatrix=glm::mat4(1);
    glm::mat4 ProjMatrix= glm::perspective(glm::radians(70.f), (float)width/height, 0.1f, 100.0f);
    glm::mat4 ModelMatrix=glm::mat4(1);


    //Creations des objets (à mettre dans une fonction setObjets())
    Model ourModel(applicationPath.dirPath() + "assets/models/pompom/pompom.obj");
    Model sphereModel(applicationPath.dirPath() + "assets/models/mars/planet.obj");

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
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,1,1), glm::vec3(0.0,0.0,10.8)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,0,1), glm::vec3(10.8,0.0,0.0)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,1,0,1), glm::vec3(10.8,0.0,0.0)));

    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieres"), lumScene.getSize());
    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieresPonct"), lumScenePonct.getSize());

    setLumieresIntensitees(lumScene, lumScenePonct, program);


    // Application loop:
    bool done = false;
    while(!done) {
        //Etat menu du début
        if(etat==DEBUT){
            debut(etat, program_menu, windowManager, menuDebut, done);
        }

        //Etat de pause
        if(etat==PAUSE){
            pause(etat, program_menu, windowManager, menuPause, done);
        }
        

        //Etat de jeu
        else if(etat==JEU){
            // Event loop:
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            SDL_Event e;
            while(windowManager.pollEvent(e)) {
                switch(e.type){
                    case SDL_QUIT:
                        done = true; // Leave the loop after this iteration
                        break;
                    case SDL_KEYDOWN:
                        if(e.key.keysym.sym == SDLK_q)
                            positionLaterale-=largeur;
                        if(e.key.keysym.sym == SDLK_d)
                            positionLaterale+=largeur;
                        if(e.key.keysym.sym == SDLK_z){
                            x=0;
                        }
                        if(e.key.keysym.sym == SDLK_m){
                            score++;
                        }
                        if(e.key.keysym.sym == SDLK_ESCAPE){
                            etat=PAUSE;
                        }
                        break;
                }
            }

            /*********************************
             * HERE SHOULD COME THE RENDERING CODE
             *********************************/
            if(windowManager.isKeyPressed(SDLK_RIGHT))cam.rotateLeft(-0.02);
            if(windowManager.isKeyPressed(SDLK_LEFT)) cam.rotateLeft(0.02);
            if(windowManager.isKeyPressed(SDLK_UP)) cam.rotateUp(-0.02);
            if(windowManager.isKeyPressed(SDLK_DOWN)) cam.rotateUp(0.02);
            if(windowManager.isKeyPressed(SDLK_w)) cam.moveFront(-0.05);
            if(windowManager.isKeyPressed(SDLK_x)) cam.moveFront(0.05);

            VMatrix=cam.getViewMatrix();

            program.use();

            x+=0.02;
            positionVerticale=saut(x*vitesse, largeur, hauteur, vitesse);

            //on envoie la position de la lumière au shader, qui change quand la cam bouge
            setLumieresPositions(lumScene, lumScenePonct, program, VMatrix);


            drawTerrain(program, sols, tableauDeSols, murs, numeroCase, ModelMatrix, VMatrix, ProjMatrix, 
            largeur, windowManager.getTime(), vitesse);

            ModelMatrix = glm::mat4(1.0f);
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(positionLaterale, positionVerticale+0.5, 0.0f)); // translate it down so it's at the center of the scene
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));	
            ourModel.Draw(program, ModelMatrix, VMatrix, ProjMatrix);


            program_menu.use();
            menu.creationTableauDeScore(3,score,3);
            menu.Draw(program_menu);

            // Update the display
            windowManager.swapBuffers();
        }
    }

    ourModel.destroy();
    sphereModel.destroy();


    return EXIT_SUCCESS;
}
