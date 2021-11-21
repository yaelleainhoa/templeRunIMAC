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

using namespace glimac;

SDL_Surface *fondTableauDeScore = NULL; 
SDL_Surface *indicationDistance = NULL; 
SDL_Surface *indicationScore = NULL; 
SDL_Surface *indicationMeilleurScore = NULL; 

TTF_Font *font; 

SDL_Color textColor = { 255, 255, 255 };

void clean_up() { //Libération des surfaces 
	//SDL_FreeSurface( background ); 
	SDL_FreeSurface( indicationDistance ); 
    SDL_FreeSurface( indicationScore ); 
    SDL_FreeSurface( indicationMeilleurScore ); 

	//Fermeture des Fonts qu'on a utilisé 
	TTF_CloseFont( font ); 

	//On quitte SDL_ttf 
	TTF_Quit(); 

	//On quitte SDL 
	SDL_Quit(); 
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) { 
	SDL_Rect offset; 

	offset.x = x; 
	offset.y = y;

    SDL_BlitSurface( source, NULL, destination, &offset ); 
}

struct Vertex2DUV{
    glm::vec2 m_position;
    glm::vec2 m_coord_tex;

    Vertex2DUV(glm::vec2 position, glm::vec2 coord_tex){
    m_position=position;
    m_coord_tex=coord_tex;
    }
};

void creationTableau(int score, int meilleurScore, int distance, SDL_Surface* &fondTableauDeScore){
    //taille de la surface du tableau
    fondTableauDeScore = SDL_CreateRGBSurface(SDL_SWSURFACE, 300, 300, 32, 0, 0, 0, 0);

    //si on veut donner une couleur de fond
    //SDL_FillRect(fondTableauDeScore, NULL, SDL_MapRGB(fondTableauDeScore->format, 0, 255, 255));

    //les messages à afficher sont des char
    std::string strScore = "Score : "+std::to_string(score)+" points";
    std::string strMeilleurScore = "Meilleur score : "+std::to_string(meilleurScore)+" points";
    std::string strDistance = "Distance : "+std::to_string(distance)+" (?)";

    //creation des message 
    indicationDistance = TTF_RenderText_Blended( font, strDistance.c_str(), textColor ); 
    indicationScore = TTF_RenderText_Blended( font, strScore.c_str(), textColor ); 
    indicationMeilleurScore = TTF_RenderText_Blended( font, strMeilleurScore.c_str(), textColor ); 

    //on ajoute les messages au tableau
    apply_surface( 20, 20, indicationDistance, fondTableauDeScore ); 
    apply_surface( 20, 35, indicationScore, fondTableauDeScore ); 
    apply_surface( 20, 50, indicationMeilleurScore, fondTableauDeScore ); 
}

void tableauEnTexture(GLuint &texture, SDL_Surface* fondTableauDeScore){
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, fondTableauDeScore->w, fondTableauDeScore->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, fondTableauDeScore->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    //Initialize TTF
    if( TTF_Init() == -1 ) { 
		return false; 
	} 

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/tex2D.vs.glsl",
                    applicationPath.dirPath() + "shaders/tex2D.fs.glsl");
                    program.use();

    font = TTF_OpenFont( (applicationPath.dirPath() + "fonts/retro.ttf").c_str(), 15 ); 
    GLint texture=glGetUniformLocation(program.getGLId(), "uTexture");
 

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/
    glEnable(GL_BLEND);

    creationTableau(30,40,2,fondTableauDeScore);
    GLuint tableau;
    tableauEnTexture(tableau, fondTableauDeScore);

    GLuint vbo;
    glGenBuffers(1,&vbo);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    Vertex2DUV vertices[]{
        Vertex2DUV(glm::vec2(-0.5,0.25),glm::vec2(0.0,0.25)),
        Vertex2DUV(glm::vec2(0.5,0.25),glm::vec2(1,0.25)),
        Vertex2DUV(glm::vec2(0.5,0.5),glm::vec2(1.0,0.0)),
        Vertex2DUV(glm::vec2(-0.5,0.5),glm::vec2(0.0,0.0))
    };
    glBufferData(GL_ARRAY_BUFFER,4*sizeof(Vertex2DUV),vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    GLuint ibo;
    glGenBuffers(1,&ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    uint32_t index[]={0,1,2,
                    0,2,3};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(uint32_t), index, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    GLuint vao;
    int INDEX_ATTR_POSITION=0;
    int INDEX_ATTR_TEXTURE=1;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(INDEX_ATTR_POSITION);
    glEnableVertexAttribArray(INDEX_ATTR_TEXTURE);
    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
    glVertexAttribPointer(INDEX_ATTR_POSITION, 2, GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),0);
    glVertexAttribPointer(INDEX_ATTR_TEXTURE, 2, GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(const GLvoid*) (2*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        glBindTexture(GL_TEXTURE_2D, tableau);
        glBindVertexArray(vao);
        glUniform1i(texture,0);
        glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT,0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);


        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1,&vao);
    glDeleteTextures(1, &tableau);
    clean_up();
    return EXIT_SUCCESS;
}
