#include <GL/glew.h>
#include <iostream>
#include <deque>

#include <glimac/SDLWindowManager.hpp>
#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>

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

using namespace glimac;

int main(int argc, char** argv) {

    TrackBallCamera cam;

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

    glm::mat4 VMatrix=glm::mat4(1);
    glm::mat4 ProjMatrix= glm::perspective(glm::radians(70.f), (float)width/height, 0.1f, 100.0f);
    glm::mat4 ModelMatrix=glm::mat4(1);

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


    //on envoie les intensités de chaque lumière (en dehors de la boucle puisque l'intensité propre à la lumière ne change pas)
    setLumieresIntensitees(lumScene, lumScenePonct, program);
    setTerrain(applicationPath.dirPath(), sols, murs);


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        if(windowManager.isKeyPressed(SDLK_RIGHT))cam.rotateLeft(-0.05);
        if(windowManager.isKeyPressed(SDLK_LEFT)) cam.rotateLeft(0.05);
        if(windowManager.isKeyPressed(SDLK_UP)) cam.rotateUp(-0.05);
        if(windowManager.isKeyPressed(SDLK_DOWN)) cam.rotateUp(0.05);
        if(windowManager.isKeyPressed(SDLK_z)) cam.moveFront(-0.05);
        if(windowManager.isKeyPressed(SDLK_d)) cam.moveFront(0.05);

        VMatrix=cam.getViewMatrix();

        //on envoie la position de la lumière au shader, qui change quand la cam bouge
        setLumieresPositions(lumScene, lumScenePonct, program, VMatrix);


        drawTerrain(program, sols, tableauDeSols, murs, numeroCase, ModelMatrix, VMatrix, ProjMatrix, largeur, windowManager.getTime(), vitesse);

        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(0.2f, 0.2f, 0.2f));	
        sphereModel.Draw(program, ModelMatrix, VMatrix, ProjMatrix);

        // Update the display
        windowManager.swapBuffers();
    }

    ourModel.destroy();
    sphereModel.destroy();


    return EXIT_SUCCESS;
}
