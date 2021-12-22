#include <GL/glew.h>
#include <iostream>
#include <deque>
#include <vector>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>

#include "../glimac/src/stb_image.h"

#include "include/variablesGlobales.hpp"
//float phiStable = M_PI;

#include "include/camera.hpp"
#include "include/trackballCamera.hpp"
#include "include/freeflyCamera.hpp"
#include "include/model.hpp"
#include "include/texture.hpp"
#include "include/lumiere.hpp"
#include "include/renderingTerrain.hpp"
#include "include/rendering.hpp"


#define GLM_SWIZZLE
#include <glm/glm.hpp>

//int etat=MORT;

//bool virage = false;


using namespace glimac;

int main(int argc, char** argv) {

    //TrackBallCamera cam;

    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                    applicationPath.dirPath() + "shaders/lumieresvec.fs.glsl");
    program.use();


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);
    GLuint width = 800, height=600 ;
    const float radius=2, min=0, max=360;
    float angle = 0;

    //Creations des matrices
    ProjMatrix= glm::perspective(glm::radians(70.f), (float)width/height, 0.1f, 100.0f);


    Model ourModel(applicationPath.dirPath() + "assets/models/pompom/pompom.obj");
    Model sphereModel(applicationPath.dirPath() + "assets/models/mars/planet.obj");

    std::vector<Model> sols;
    std::vector<Model> murs;

    std::deque<int> tableauDeSols;
    for(int i=0; i<10; i++){
    tableauDeSols.push_back(2);}

    //ajout des lumières (directionnelles) à la scène
    LumieresScenes lumScene;
    lumScene.addLumiere(Lumiere(glm::vec4(1,1,1,0), glm::vec3(0.3,0.3,0.3)));

    //ajout des lumières de type ponctuelle
    LumieresScenes lumScenePonct;
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,1,1), glm::vec3(0.0,0.0,10.8)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,0,1), glm::vec3(10.8,0.0,0.0)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,1,0,1), glm::vec3(10.8,0.0,0.0)));

    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieres"), lumScene.getSize());
    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieresPonct"), lumScenePonct.getSize());

    int numeroCase=0;
    float positionLaterale=0.0;
    float positionVerticale=0.0;
    float x=largeur;

    //on envoie les intensités de chaque lumière (en dehors de la boucle puisque l'intensité propre à la lumière ne change pas)
    setLumieresIntensites(lumScene, lumScenePonct, program);
    setTerrain(applicationPath.dirPath(), sols, murs);

    // creation d'un vecteur de caméras pour simplifier le changement de caméra
    std::vector<Camera*> listeCameras;
    listeCameras.push_back(new TrackBallCamera);
    listeCameras.push_back(new FreeflyCamera);

    //indice pour le vecteur de caméras : quand indiceCam = 0 c'est la TrackballCamera
    // quand indiceCam = 1 c'est la FreeFly
    int indiceCam = 0;

    // Application loop:
    bool done = false;
    while(!done) {
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
                         listeCameras.at(indiceCam)->rotateLeft(90.0);
                    }
                    break;
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        if(windowManager.isKeyPressed(SDLK_RIGHT))listeCameras.at(indiceCam)->rotateLeft(-0.5);
        if(windowManager.isKeyPressed(SDLK_LEFT)) listeCameras.at(indiceCam)->rotateLeft(0.5);
        if(windowManager.isKeyPressed(SDLK_UP)) listeCameras.at(indiceCam)->rotateUp(-0.5);
        if(windowManager.isKeyPressed(SDLK_DOWN)) listeCameras.at(indiceCam)->rotateUp(0.5);
        if(windowManager.isKeyPressed(SDLK_w)) listeCameras.at(indiceCam)->moveFront(-0.5);
        if(windowManager.isKeyPressed(SDLK_x)) listeCameras.at(indiceCam)->moveFront(0.5);

        VMatrix=listeCameras.at(indiceCam)->getViewMatrix();
        x+=0.02;
        positionVerticale=saut();

        //on envoie la position de la lumière au shader, qui change quand la cam bouge
        setLumieresPositions(lumScene, lumScenePonct, program);
        //std::cout << "virage ? " << virage << std::endl;
        drawTerrain(program, sols, tableauDeSols, murs, angle, listeCameras);
        //std::cout << "virage apres drawTerrain ? " << virage << std::endl;
     

        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(positionLaterale, positionVerticale+0.5, 0.0f)); // translate it down so it's at the center of the scene
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));
        ModelMatrix = glm::rotate(ModelMatrix, angle, glm::vec3(0.0,1.0,0.0));
        ourModel.Draw(program);

        // Update the display
        windowManager.swapBuffers();
    }

    ourModel.destroy();
    destroyTerrain(sols,murs);
    // détruit les caméras liées aux pointeurs pour éviter les fuites de mémoire
     for(size_t i=0; i<listeCameras.size(); ++i)
    		delete listeCameras[i];


    return EXIT_SUCCESS;
}
