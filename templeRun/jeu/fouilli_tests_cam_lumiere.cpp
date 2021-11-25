#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Cone.hpp>
#include <glimac/TrackballCamera.hpp>

#define GLM_SWIZZLE
#include <glm/glm.hpp>

float largeur=0.5;

using namespace glimac;

struct Vertex3DUV{
    glm::vec3 m_position;
    glm::vec3 m_normals;
    glm::vec2 m_coord_tex;

    Vertex3DUV(glm::vec3 position, glm::vec3 normals, glm::vec2 coord_tex){
    m_position=position;
    m_normals=normals;
    m_coord_tex=coord_tex;
    }
};

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
        const std::string strIntensite = "uIntensites["+std::to_string(i)+"]";
        glUniform3fv(glGetUniformLocation(program.getGLId(), strIntensite.c_str()), 1, glm::value_ptr(lumScene.m_intensites[i]));
    }

    for(int i=0; i<lumScene.m_positions.size();i++){
        const std::string strIntensitePonct = "uIntensitesPonct["+std::to_string(i)+"]";
        glUniform3fv(glGetUniformLocation(program.getGLId(), strIntensitePonct.c_str()), 1, glm::value_ptr(lumScenePonct.m_intensites[i]));
    }
}

void setLumieresPositions(lumiereScene &lumScene, lumiereScene &lumScenePonct, Program &program, glm::mat4 &VMatrix){
    for(int i=0; i<lumScene.m_positions.size();i++){
        const std::string strPosition = "uPositions["+std::to_string(i)+"]";
        glUniform4fv(glGetUniformLocation(program.getGLId(), strPosition.c_str()), 1, glm::value_ptr(lumScene.m_positions[i]*VMatrix));
    }

for(int i=0; i<lumScenePonct.m_positions.size();i++){
        const std::string strPositionPonct = "uPositionsPonct["+std::to_string(i)+"]";
        glUniform4fv(glGetUniformLocation(program.getGLId(), strPositionPonct.c_str()), 1, glm::value_ptr(lumScenePonct.m_positions[i]*VMatrix));
    }

}

void creerBuffers_sphere(GLuint &vbo, GLuint &vao, Sphere &sphere){
    const GLuint INDEX_ATTR_POSITION=0, INDEX_ATTR_NORMAL=1,INDEX_ATTR_TEXTCOORDS=2;

    //VBO
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,sphere.getVertexCount()*sizeof(ShapeVertex),sphere.getDataPointer(),GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(INDEX_ATTR_POSITION);
    glEnableVertexAttribArray(INDEX_ATTR_NORMAL);
    glEnableVertexAttribArray(INDEX_ATTR_TEXTCOORDS);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(INDEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),0);
    glVertexAttribPointer(INDEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),(const GLvoid*) (3*sizeof(GLfloat)));
    glVertexAttribPointer(INDEX_ATTR_TEXTCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),(const GLvoid*) (6*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

glm::vec3 pointsEnVecteur(glm::vec3 p1, glm::vec3 p2){
    glm::vec3 point;
    point.x=p2.x-p1.x;
    point.y=p2.y-p1.y;
    point.z=p2.z-p1.z;
    return point;
}

void creerBuffers_case(GLuint &vbo, GLuint &vao, GLuint &ibo){
    const GLuint INDEX_ATTR_POSITION=0, INDEX_ATTR_NORMAL=1,INDEX_ATTR_TEXTCOORDS=2;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glm::vec3 points[]{
        glm::vec3(-3*largeur/2,0,-largeur/2),
        glm::vec3(-largeur/2,0,-largeur/2),
        glm::vec3(largeur/2,0,-largeur/2),
        glm::vec3(3*largeur/2,0,-largeur/2),
        glm::vec3(-3*largeur/2,0,largeur/2),
        glm::vec3(-largeur/2,0,largeur/2),
        glm::vec3(largeur/2,0,largeur/2),
        glm::vec3(3*largeur/2,0,largeur/2)
    };
    glm::vec3 normals[]{
        glm::normalize(glm::cross(pointsEnVecteur(points[0], points[3]), pointsEnVecteur(points[0], points[4]))),
        glm::normalize(glm::cross(pointsEnVecteur(points[4], points[7]), pointsEnVecteur(points[3], points[5]))),
    };
    Vertex3DUV vertices[]{
        Vertex3DUV(points[0],glm::vec3(0,1,0), glm::vec2(0.0,0)),
        Vertex3DUV(points[1],glm::vec3(0,1,0), glm::vec2(1.0/3.0,0)),
        Vertex3DUV(points[2],glm::vec3(0,1,0), glm::vec2(2.0/3.0,0.0)),
        Vertex3DUV(points[3],glm::vec3(0,1,0), glm::vec2(1.0,0.0)),
        Vertex3DUV(points[4],glm::vec3(0,1,0), glm::vec2(0.0,1.0)),
        Vertex3DUV(points[5],glm::vec3(0,1,0), glm::vec2(1.0/3.0, 1.0)),
        Vertex3DUV(points[6],glm::vec3(0,1,0), glm::vec2(2.0/3.0, 1.0)),
        Vertex3DUV(points[7],glm::vec3(0,1,0), glm::vec2(1.0,1.0))
    };
    glBufferData(GL_ARRAY_BUFFER,8*sizeof(Vertex3DUV),vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glGenBuffers(1,&ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    uint32_t index[]={0,1,4,
                    1,4,5,
                    1,2,5,
                    2,5,6,
                    2,3,6,
                    3,6,7};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 18*sizeof(uint32_t), index, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(INDEX_ATTR_POSITION);
    glEnableVertexAttribArray(INDEX_ATTR_NORMAL);
    glEnableVertexAttribArray(INDEX_ATTR_TEXTCOORDS);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
    glVertexAttribPointer(INDEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV),0);
    glVertexAttribPointer(INDEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV),(const GLvoid*) (3*sizeof(GLfloat)));
    glVertexAttribPointer(INDEX_ATTR_TEXTCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DUV),(const GLvoid*) (6*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
}

void drawCase(GLuint &vao, GLuint& texture, glm::mat4 &VMatrix, glm::mat4 &MMatrix, glm::mat4 &ProjMatrix, float shininess, Program &program, SDLWindowManager &windowManager){
        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D,texture);
        glUniform1f(glGetUniformLocation(program.getGLId(), "uTexture"),0);

        glm::mat4 MVMatrix=VMatrix*MMatrix;
        glm::mat4 NormalMatrix=glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"),1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"),1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"),1,GL_FALSE,glm::value_ptr(NormalMatrix));
        glUniform1f(glGetUniformLocation(program.getGLId(), "shininess"),10);

        glDrawElements(GL_TRIANGLES, 3*6, GL_UNSIGNED_INT,0);
        glBindVertexArray(0);
}

void drawSphere(GLuint &vao, GLuint& texture, glm::mat4 &VMatrix, glm::mat4 &ModelMatrix, 
                glm::mat4 &ProjMatrix, float shininess, Sphere &sphere, Program &program, 
                SDLWindowManager &windowManager){
        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D,texture);
        glUniform1f(glGetUniformLocation(program.getGLId(), "uTexture"),0);

        glm::mat4 MVMatrix=VMatrix*ModelMatrix;
        glm::mat4 NormalMatrix=glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"),1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"),1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"),1,GL_FALSE,glm::value_ptr(NormalMatrix));
        glUniform1f(glGetUniformLocation(program.getGLId(), "shininess"),10);

        glDrawArrays(GL_TRIANGLES,0,sphere.getVertexCount());
        glBindVertexArray(0);
}

void creerBuffers_cone(GLuint &vbo, GLuint &vao, Cone &cone){
    const GLuint INDEX_ATTR_POSITION=0, INDEX_ATTR_NORMAL=1,INDEX_ATTR_TEXTCOORDS=2;

    //VBO
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,cone.getVertexCount()*sizeof(ShapeVertex),cone.getDataPointer(),GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(INDEX_ATTR_POSITION);
    glEnableVertexAttribArray(INDEX_ATTR_NORMAL);
    glEnableVertexAttribArray(INDEX_ATTR_TEXTCOORDS);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(INDEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),0);
    glVertexAttribPointer(INDEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),(const GLvoid*) (3*sizeof(GLfloat)));
    glVertexAttribPointer(INDEX_ATTR_TEXTCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex),(const GLvoid*) (6*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void drawCone(GLuint &vao, GLuint& texture, glm::mat4 &VMatrix, glm::mat4 &ModelMatrix, 
                glm::mat4 &ProjMatrix, float shininess, Cone &cone, Program &program, 
                SDLWindowManager &windowManager){
        glBindVertexArray(vao);
        glBindTexture(GL_TEXTURE_2D,texture);
        glUniform1f(glGetUniformLocation(program.getGLId(), "uTexture"),0);

        glm::mat4 MVMatrix=VMatrix*ModelMatrix;
        glm::mat4 NormalMatrix=glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVMatrix"),1,GL_FALSE,glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uMVPMatrix"),1,GL_FALSE,glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program.getGLId(), "uNormalMatrix"),1,GL_FALSE,glm::value_ptr(NormalMatrix));
        glUniform1f(glGetUniformLocation(program.getGLId(), "shininess"),10);

        glDrawArrays(GL_TRIANGLES,0,cone.getVertexCount());
        glBindVertexArray(0);
}

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
    Cone cone(1, 1, 20, 30);

    GLuint lune, terre, nuages;
    creerUneTexture(lune, imageLune);
    creerUneTexture(terre, imageTerre);
    //creerDeuxTextures(terre, nuages, imageTerre, imageNuages);

    GLuint vbo, vao, vbo_case, vao_case, ibo_case, vbo_cone, vao_cone;
    creerBuffers_sphere(vbo, vao, sphere);
    creerBuffers_case(vbo_case, vao_case, ibo_case);
    creerBuffers_cone(vbo_cone, vao_cone, cone);


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
        if(windowManager.isKeyPressed(SDLK_RIGHT))cam.rotateLeft(-0.01);
        if(windowManager.isKeyPressed(SDLK_LEFT)) cam.rotateLeft(0.01);
        if(windowManager.isKeyPressed(SDLK_UP)) cam.rotateUp(-0.01);
        if(windowManager.isKeyPressed(SDLK_DOWN)) cam.rotateUp(0.01);
        if(windowManager.isKeyPressed(SDLK_z)) cam.moveFront(-0.01);
        if(windowManager.isKeyPressed(SDLK_d)) cam.moveFront(0.01);

        VMatrix=cam.getViewMatrix();


        //on envoie la position de la lumière au shader, qui change quand la cam bouge
        setLumieresPositions(lumScene, lumScenePonct, program, VMatrix);
        ModelMatrix=glm::rotate(glm::mat4(1), windowManager.getTime(), glm::vec3(0,1,0));
        ModelMatrix=glm::scale(ModelMatrix, glm::vec3(0.2,0.2,0.2));

        drawSphere(vao, terre, VMatrix, ModelMatrix, ProjMatrix, 10, sphere, program, windowManager);

        for (int i=1;i<33;i++){
            ModelMatrix=glm::rotate(glm::mat4(1), pos_depart[i]+windowManager.getTime(), axes[i]);
            ModelMatrix=glm::translate(ModelMatrix, glm::vec3(-2,0,0));
            ModelMatrix=glm::scale(ModelMatrix,glm::vec3(0.2,0.2,0.2));
            drawSphere(vao, lune, VMatrix, ModelMatrix, ProjMatrix, 10, sphere, program, windowManager);
        }


        //ModelMatrix=glm::translate(glm::mat4(1), glm::vec3(0,0,-windowManager.getTime()));
        for(int i=-20; i<20; i++){
            ModelMatrix=glm::translate(glm::mat4(1), glm::vec3(0,0,-(largeur*i+windowManager.getTime()/2)));
            if(distance(ModelMatrix)<0.5){
                drawCase(vao_case, lune, VMatrix, ModelMatrix, ProjMatrix, 10, program, windowManager);

            }
            else{
                drawCase(vao_case, terre, VMatrix, ModelMatrix, ProjMatrix, 10, program, windowManager);

            }
        }

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1,&vao);
    return EXIT_SUCCESS;
}
