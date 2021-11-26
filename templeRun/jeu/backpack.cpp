#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include "include/trackballCamera.hpp"
#include "include/model.hpp"
#include "../glimac/src/stb_image.h"


#define GLM_SWIZZLE
#include <glm/glm.hpp>

float largeur=0.5;

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
    Program program = loadProgram(applicationPath.dirPath() + "shaders/model_loading.vs.glsl",
                    applicationPath.dirPath() + "shaders/model_loading.fs.glsl");
    program.use();

    std::unique_ptr<Image> imageTerre = loadImage(applicationPath.dirPath() + "assets/textures/EarthMap.jpg");

    if(imageTerre==NULL){
        std::cout<<"error"<<std::endl;
    }

    std::unique_ptr<Image> imageLune = loadImage(applicationPath.dirPath() + "assets/textures/MoonMap.jpg");

    if(imageLune==NULL){
        std::cout<<"error"<<std::endl;
    }


    std::unique_ptr<Image> imageNuages = loadImage(applicationPath.dirPath() + "assets/textures/CloudMap.jpg");

    if(imageNuages==NULL){
        std::cout<<"error"<<std::endl;
    }


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);

    Model ourModel(applicationPath.dirPath() + "assets/models/pompom/pompom.obj");

    GLuint width = 800, height=600 ;
    const float radius=2, min=0, max=360;

    glm::mat4 VMatrix=glm::mat4(1);
    glm::mat4 ProjMatrix= glm::perspective(glm::radians(70.f), (float)width/height, 0.1f, 100.0f);
    glm::mat4 ModelMatrix=glm::mat4(1);

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
        if(windowManager.isKeyPressed(SDLK_RIGHT))cam.rotateLeft(-0.1);
        if(windowManager.isKeyPressed(SDLK_LEFT)) cam.rotateLeft(0.1);
        if(windowManager.isKeyPressed(SDLK_UP)) cam.rotateUp(-0.1);
        if(windowManager.isKeyPressed(SDLK_DOWN)) cam.rotateUp(0.1);
        if(windowManager.isKeyPressed(SDLK_z)) cam.moveFront(-0.1);
        if(windowManager.isKeyPressed(SDLK_d)) cam.moveFront(0.1);

        VMatrix=cam.getViewMatrix();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	

        glm::mat4 MVMatrix=VMatrix*model;
        glm::mat4 NormalMatrix=glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"),1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"),1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"),1,GL_FALSE,glm::value_ptr(NormalMatrix));

        ourModel.Draw(program);
        // Update the display
        windowManager.swapBuffers();
    }
    ourModel.destroy();
    return EXIT_SUCCESS;
}
