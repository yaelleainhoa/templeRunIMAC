#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/TrackballCamera.hpp>

#define GLM_SWIZZLE
#include <glm/glm.hpp>

using namespace glimac;

struct lumiere{
    glm::vec4 m_pos;
    glm::vec3 m_intensite;

    lumiere(glm::vec4 pos, glm::vec3 intensite)
    :m_pos(pos),
    m_intensite(intensite)
    {}
};

struct lumiereScene{
    std::vector<glm::vec4> m_positions;
    std::vector<glm::vec3> m_intensites;

    lumiereScene(){
        std::vector<glm::vec4> positions;
        std::vector<glm::vec3> intensites;
        m_positions=positions;
        m_intensites=intensites;

    }
    ;
    void addLumiere(lumiere lum){
        m_positions.push_back(lum.m_pos);
        m_intensites.push_back(lum.m_intensite);
    }
};

void creerUneTexture(GLuint &texture, std::unique_ptr<Image> &image){
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void creerDeuxTextures(GLuint &texture0, GLuint &texture1, std::unique_ptr<Image> &image0, std::unique_ptr<Image> &image1){
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture0);
    glGenTextures(1, &texture1);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image0->getWidth(), image0->getHeight(), 0, GL_RGBA, GL_FLOAT, image0->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

     glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image1->getWidth(), image1->getHeight(), 0, GL_RGBA, GL_FLOAT, image1->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void setLumieresIntensitees(lumiereScene &lumScene, lumiereScene &lumScenePonct, Program &program){
    for(int i=0; i<lumScene.m_positions.size();i++){
        char charIntensite[30];
        std::string strIntensite = "uIntensites["+std::to_string(i)+"]";
        strcpy(charIntensite, strIntensite.c_str());
        glUniform3fv(glGetUniformLocation(program.getGLId(), charIntensite), 1, glm::value_ptr(lumScene.m_intensites[i]));
    }

    for(int i=0; i<lumScene.m_positions.size();i++){
        char charIntensite[30];
        std::string strIntensite = "uIntensitesPonct["+std::to_string(i)+"]";
        strcpy(charIntensite, strIntensite.c_str());
        glUniform3fv(glGetUniformLocation(program.getGLId(), charIntensite), 1, glm::value_ptr(lumScenePonct.m_intensites[i]));
    }
}

void setLumieresPositions(lumiereScene &lumScene, lumiereScene &lumScenePonct, Program &program, glm::mat4 &VMatrix){
    for(int i=0; i<lumScene.m_positions.size();i++){
        char charPosition[30];
        std::string strPosition = "uPositions["+std::to_string(i)+"]";
        strcpy(charPosition, strPosition.c_str());
        glUniform4fv(glGetUniformLocation(program.getGLId(), charPosition), 1, glm::value_ptr(lumScene.m_positions[i]*VMatrix));
    }

for(int i=0; i<lumScenePonct.m_positions.size();i++){
        char charPositionPonct[30];
        std::string strPositionPonct = "uPositionsPonct["+std::to_string(i)+"]";
        strcpy(charPositionPonct, strPositionPonct.c_str());
        glUniform4fv(glGetUniformLocation(program.getGLId(), charPositionPonct), 1, glm::value_ptr(lumScenePonct.m_positions[i]*VMatrix));
    }

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

    std::unique_ptr<Image> imageTerre = loadImage("/home/yaelle/Documents/S2/Synthèse image/GLImac-Template/assets/textures/EarthMap.jpg");

    if(imageTerre==NULL){
        std::cout<<"error"<<std::endl;
    }

    std::unique_ptr<Image> imageLune = loadImage("/home/yaelle/Documents/S2/Synthèse image/GLImac-Template/assets/textures/MoonMap.jpg");

    if(imageLune==NULL){
        std::cout<<"error"<<std::endl;
    }


    std::unique_ptr<Image> imageNuages = loadImage("/home/yaelle/Documents/S2/Synthèse image/GLImac-Template/assets/textures/CloudMap.jpg");

    if(imageNuages==NULL){
        std::cout<<"error"<<std::endl;
    }


    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                    applicationPath.dirPath() + "shaders/lumieresvec.fs.glsl");
                    program.use();

    GLint loc_MVPMatrix=glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint loc_MVMatrix=glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint loc_NormalMatrix=glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    GLint loc_shininess=glGetUniformLocation(program.getGLId(), "shininess");

    GLint loc_texture=glGetUniformLocation(program.getGLId(), "uTexture");
    GLint loc_textureNuages=glGetUniformLocation(program.getGLId(), "uTextureNuages");





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
    glm::mat4 MVMatrix=VMatrix; //pour l'instant l'objet est au centre, aucune transformation
    glm::mat4 NormalMatrix=glm::transpose(glm::inverse(MVMatrix));

    glm::mat4 lune_MVMatrix=MVMatrix;
    glm::mat4 lune_NormalMatrix=MVMatrix;

    glm::mat4 terre_MVMatrix=MVMatrix;
    glm::mat4 terre_NormalMatrix=MVMatrix;


    Sphere sphere(1,32,16);
    const GLuint INDEX_ATTR_POSITION=0, INDEX_ATTR_NORMAL=1,INDEX_ATTR_TEXTCOORDS=2;

    GLuint lune, terre, nuages;
    creerUneTexture(lune, imageLune);
    creerDeuxTextures(terre, nuages, imageTerre, imageNuages);

    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,sphere.getVertexCount()*sizeof(ShapeVertex),sphere.getDataPointer(),GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(INDEX_ATTR_POSITION);
    glEnableVertexAttribArray(INDEX_ATTR_NORMAL);
    glEnableVertexAttribArray(INDEX_ATTR_TEXTCOORDS);
    //Ici on bind a nouveau le vbo pour qu'on voit quelles données le vao décrit (ici vertices)
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //Mtn on peut décrire les données du vbo
    glVertexAttribPointer(INDEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),0);
    glVertexAttribPointer(INDEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),(const GLvoid*) (3*sizeof(GLfloat)));
    glVertexAttribPointer(INDEX_ATTR_TEXTCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),(const GLvoid*) (6*sizeof(GLfloat)));
    //On a fini avec le VBO donc on debind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //idem avec le vaos
    glBindVertexArray(0);


    std::vector<glm::vec3> axes;
    std::vector<float> pos_depart;
    for(int i=0; i<32;i++){
        axes.push_back(glm::sphericalRand(radius));
        pos_depart.push_back(glm::linearRand(min, max));
    }

    //ajout des lumières (directionnelles) à la scène
    lumiereScene lumScene;
    lumScene.addLumiere(lumiere(glm::vec4(1,1,1,0), glm::vec3(0.0,0.8,0.8)));
    lumScene.addLumiere(lumiere(glm::vec4(0,1,0,0), glm::vec3(0.8,0.8,0.0)));

    //ajout des lumières de type ponctuelle
    lumiereScene lumScenePonct;
    lumScenePonct.addLumiere(lumiere(glm::vec4(1,0,1,1), glm::vec3(0.0,0.0,0.8)));
    lumScenePonct.addLumiere(lumiere(glm::vec4(1,0,0,1), glm::vec3(0.8,0.0,0.0)));
    lumScenePonct.addLumiere(lumiere(glm::vec4(1,1,0,1), glm::vec3(5.8,0.0,0.0)));

    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieres"), lumScene.m_positions.size());
    glUniform1i(glGetUniformLocation(program.getGLId(), "nbLumieresPonct"), lumScenePonct.m_positions.size());


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

        glBindVertexArray(vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,terre);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D,nuages);

        glUniform1f(loc_texture,0);
        glUniform1f(loc_textureNuages,1);

        terre_MVMatrix=glm::rotate(VMatrix, windowManager.getTime(), glm::vec3(0,1,0));
        terre_NormalMatrix=glm::transpose(glm::inverse(terre_MVMatrix));
        glUniformMatrix4fv(loc_MVMatrix,1,GL_FALSE,glm::value_ptr(terre_MVMatrix));
        glUniformMatrix4fv(loc_MVPMatrix,1,GL_FALSE,glm::value_ptr(ProjMatrix * terre_MVMatrix));
        glUniformMatrix4fv(loc_NormalMatrix,1,GL_FALSE,glm::value_ptr(terre_NormalMatrix));
        glUniform1f(loc_shininess,10);


        glDrawArrays(GL_TRIANGLES,0,sphere.getVertexCount());

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);    
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);  


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, lune);
        glUniform1i(loc_texture,0);
        for (int i=1;i<33;i++){
            lune_MVMatrix=glm::rotate(VMatrix, pos_depart[i]+windowManager.getTime(), axes[i]);
            lune_MVMatrix=glm::translate(lune_MVMatrix, glm::vec3(-2,0,0));
            lune_MVMatrix=glm::scale(lune_MVMatrix,glm::vec3(0.2,0.2,0.2));
            lune_NormalMatrix=glm::transpose(glm::inverse(lune_MVMatrix));
            glUniform1f(loc_shininess,10);
            glUniformMatrix4fv(loc_MVMatrix,1,GL_FALSE,glm::value_ptr(lune_MVMatrix));
            glUniformMatrix4fv(loc_MVPMatrix,1,GL_FALSE,glm::value_ptr(ProjMatrix * lune_MVMatrix));
            glUniformMatrix4fv(loc_NormalMatrix,1,GL_FALSE,glm::value_ptr(lune_NormalMatrix));
            glDrawArrays(GL_TRIANGLES,0,sphere.getVertexCount());
        }
        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1,&vao);
    return EXIT_SUCCESS;
}
