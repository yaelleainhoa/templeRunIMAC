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
int meilleurScore=100;
int distance=0;
std::string nomPartie="test en attendant";

#include "include/trackballCamera.hpp"
#include "include/freeflyCamera.hpp"
#include "include/model.hpp"
#include "include/texture.hpp"
#include "include/lumiere.hpp"
#include "include/renderingTerrain.hpp"
#include "include/rendering.hpp"
#include "include/jeu.hpp"
#include "include/fenetresTextuelles.hpp"

#define GLM_SWIZZLE
#include <glm/glm.hpp>

float largeur=1.5;
float vitesse=2.0;
float hauteur=2.0;

int LimitFrontOK = 0; 
bool virage = false;

// int numeroCase=0;
// float positionLaterale=0.0;
// float positionVerticale=0.0;
float x=largeur;
// int score=0;
int etat=DEBUT;
std::string nomDePartie;
std::string CHEATCODE;
GLuint width = 800, height=600 ;

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
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,1,1), glm::vec3(10.0,0.0,10.8)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,0,1), glm::vec3(10.8,0.0,0.0)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,1,0,1), glm::vec3(10.8,0.0,0.0)));

    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieres"), lumScene.getSize());
    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieresPonct"), lumScenePonct.getSize());

    setLumieresIntensites(lumScene, lumScenePonct, program);


    // creation d'un vecteur de caméras pour simplifier le changement de caméra
    std::vector<Camera*> listeCameras;
    listeCameras.push_back(new TrackBallCamera);
    listeCameras.push_back(new FreeflyCamera);

    //indice pour le vecteur de caméras : quand indiceCam = 0 c'est la TrackballCamera
    // quand indiceCam = 1 c'est la FreeFly
    int indiceCam = 0;

    bool LimitOK = true;
    bool LimitUpOK = true;




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
            nom(etat, program_menu, windowManager, menuNom, done, nomDePartie);
        }

        else if(etat==ANCIENNESPARTIES){
            recharger(etat, program_menu, windowManager, menuAnciennesParties, done);
        }

        else if(etat==MEILLEURSSCORES){
            meilleursScores(etat, program_menu, windowManager, menuMeilleursScores, done);
        }

        else if(etat==WARNING){
            warning(etat, program_menu, windowManager, menuWarning, done, nomDePartie);
        }
        

        //Etat de jeu
        else{
            if(etat==RECOMMENCER){
                tableauDeSols.clear();
                for(int i=0; i<10; i++){
                tableauDeSols.push_back(1);}

                positionLaterale=0.0;
                positionVerticale=0.0;
                score=0;
                x=largeur;
            }
            if(etat==RECHARGER){
                tableauDeSols.clear();
                for(int i=0; i<10; i++){
                tableauDeSols.push_back(0);}

                positionLaterale=0.0;
                positionVerticale=0.0;
                score=0;
                x=largeur;
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

                        //CHEAT CODE
                        if(e.key.keysym.sym == SDLK_b){
                            CHEATCODE="b";
                        }
                        if(e.key.keysym.sym == SDLK_i){
                            CHEATCODE+="i";
                            if(CHEATCODE=="biri"){
                                score+=100;
                            }
                        }
                        if(e.key.keysym.sym == SDLK_r){
                            CHEATCODE+="r";
                        }
                    // changement de caméras 
                    if(e.key.keysym.sym == SDLK_t){
                        std::cout  << "indieCam = "<< indiceCam << std::endl;
                        if(indiceCam == 0) indiceCam = 1;
                        else indiceCam = 0;
                        std::cout  << "indieCam = "<< indiceCam << std::endl;
                    }
                    if(e.key.keysym.sym == SDLK_v){
                        virage = true;
                    }
                    if(e.key.keysym.sym == SDLK_r){
                         listeCameras.at(indiceCam)->rotateLeft(90.0, LimitOK);
                    }
                        break;
                }
            }

            /*********************************
             * HERE SHOULD COME THE RENDERING CODE
             *********************************/
        if(windowManager.isKeyPressed(SDLK_RIGHT))listeCameras.at(indiceCam)->rotateLeft(-0.5, LimitOK);
        if(windowManager.isKeyPressed(SDLK_LEFT)) listeCameras.at(indiceCam)->rotateLeft(0.5, LimitOK);
        if(windowManager.isKeyPressed(SDLK_UP)) listeCameras.at(indiceCam)->rotateUp(-0.5,LimitUpOK);
        if(windowManager.isKeyPressed(SDLK_DOWN)) listeCameras.at(indiceCam)->rotateUp(0.5, LimitUpOK);
        if(windowManager.isKeyPressed(SDLK_w)) listeCameras.at(indiceCam)->moveFront(-0.5, LimitFrontOK);
        if(windowManager.isKeyPressed(SDLK_x)) listeCameras.at(indiceCam)->moveFront(0.5, LimitFrontOK);

        VMatrix=listeCameras.at(indiceCam)->getViewMatrix();

            program.use();

            x+=0.02;
            positionVerticale=saut();//x*vitesse, largeur, hauteur, vitesse);

            //on envoie la position de la lumière au shader, qui change quand la cam bouge
            lumScenePonct.changePositionAt(0,glm::vec4(x,0,0,1));
            setLumieresPositions(lumScene, lumScenePonct, program, VMatrix);


            drawTerrain(program, sols, tableauDeSols, murs, numeroCase, ModelMatrix, VMatrix, ProjMatrix, virage, angle, listeCameras);

            ModelMatrix = glm::mat4(1.0f);
            ModelMatrix = glm::translate(ModelMatrix, glm::vec3(positionLaterale, positionVerticale+0.5, 0.0f)); // translate it down so it's at the center of the scene
            ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));	
            ourModel.Draw(program, ModelMatrix, VMatrix, ProjMatrix);


            program_menu.use();
            menu.creation();
            menu.Draw(program_menu);

            // Update the display
            windowManager.swapBuffers();
        }

    }

    ourModel.destroy();
    destroyTerrain(sols, murs);


    return EXIT_SUCCESS;
}
