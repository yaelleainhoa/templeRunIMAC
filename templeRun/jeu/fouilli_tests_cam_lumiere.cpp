#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glimac/model.hpp>
#include <glimac/texture.hpp>
#include <glimac/lumiere.hpp>


#define GLM_SWIZZLE
#include <glm/glm.hpp>

float largeur=0.5;

using namespace glimac;

float distance(const glm::mat4 ModelMatrix){
    glm::vec4 M = glm::normalize(ModelMatrix[3]);
    glm::vec3 pos = glm::vec3(M.x, M.y, M.z);
    return glm::distance(glm::vec3(0), pos);
}

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

    std::unique_ptr<Image> imageTerre = loadImage(applicationPath.dirPath() + "textures/EarthMap.jpg");

    if(imageTerre==NULL){
        std::cout<<"error"<<std::endl;
    }

    std::unique_ptr<Image> imageLune = loadImage(applicationPath.dirPath() + "textures/MoonMap.jpg");

    if(imageLune==NULL){
        std::cout<<"error"<<std::endl;
    }


    std::unique_ptr<Image> imageNuages = loadImage(applicationPath.dirPath() + "textures/CloudMap.jpg");

    if(imageNuages==NULL){
        std::cout<<"error"<<std::endl;
    }


    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    glEnable(GL_DEPTH_TEST);
    GLuint width = 800, height=600 ;
    const float radius=2, min=0, max=360;

    glm::mat4 VMatrix=glm::mat4(1);
    glm::mat4 ProjMatrix= glm::perspective(glm::radians(70.f), (float)width/height, 0.1f, 100.0f);
    glm::mat4 ModelMatrix=glm::mat4(1);


    Sphere sphere(1,32,16);

    GLuint lune, terre, nuages;
    // creerUneTexture(lune, imageLune);
    // creerUneTexture(terre, imageTerre);


    Model ourModel(applicationPath.dirPath() + "models/pompom/pompom.obj");
    Model sphereModel(applicationPath.dirPath() + "models/mars/planet.obj");
    Model caseModel(applicationPath.dirPath() + "models/case/case.obj");
    Model murModel(applicationPath.dirPath() + "models/mur/mur.obj");

    //ajout des lumières (directionnelles) à la scène
    LumieresScenes lumScene;
    lumScene.addLumiere(Lumiere(glm::vec4(1,1,1,0), glm::vec3(0.0,0.8,0.8)));
    lumScene.addLumiere(Lumiere(glm::vec4(0,1,0,0), glm::vec3(0.8,0.8,0.0)));

    //ajout des lumières de type ponctuelle
    LumieresScenes lumScenePonct;
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,1,1), glm::vec3(0.0,0.0,0.8)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,0,0,1), glm::vec3(0.8,0.0,0.0)));
    lumScenePonct.addLumiere(Lumiere(glm::vec4(1,1,0,1), glm::vec3(5.8,0.0,0.0)));

    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieres"), lumScene.getSize());
    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieresPonct"), lumScenePonct.getSize());


    //on envoie les intensités de chaque lumière (en dehors de la boucle puisque l'intensité propre à la lumière ne change pas)
    setLumieresIntensitees(lumScene, lumScenePonct, program);

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

        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        ModelMatrix = glm::scale(ModelMatrix, glm::vec3(1.0f, 1.0f, 1.0f));	

        glm::mat4 MVMatrix=VMatrix*ModelMatrix;
        glm::mat4 NormalMatrix=glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"),1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"),1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"),1,GL_FALSE,glm::value_ptr(NormalMatrix));

        ourModel.Draw(program);

        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(-3*largeur/2.0, 0.0f, 0.0f)); // translate it down so it's at the center of the scene

        MVMatrix=VMatrix*ModelMatrix;
        NormalMatrix=glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"),1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"),1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"),1,GL_FALSE,glm::value_ptr(NormalMatrix));

        murModel.Draw(program);

        ModelMatrix = glm::mat4(1.0f);
        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(3*largeur/2.0, 0.0f, 0.0f)); // translate it down so it's at the center of the scene

        MVMatrix=VMatrix*ModelMatrix;
        NormalMatrix=glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"),1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"),1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"),1,GL_FALSE,glm::value_ptr(NormalMatrix));

        murModel.Draw(program);


        ModelMatrix = glm::mat4(1.0f);
        MVMatrix=VMatrix*ModelMatrix;
        NormalMatrix=glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"),1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"),1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"),1,GL_FALSE,glm::value_ptr(NormalMatrix));

        caseModel.Draw(program);

        // Update the display
        windowManager.swapBuffers();
    }

    ourModel.destroy();
    sphereModel.destroy();

    return EXIT_SUCCESS;
}
