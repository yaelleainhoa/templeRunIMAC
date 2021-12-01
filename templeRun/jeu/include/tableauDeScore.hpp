#ifndef MENU_H
#define MENU_H

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include <string>
#include <glm/glm.hpp>
#include <glimac/Program.hpp>

using namespace glimac;

struct Vertex2DUV{
    glm::vec2 m_position;
    glm::vec2 m_coord_tex;

    Vertex2DUV(glm::vec2 position, glm::vec2 coord_tex){
    m_position=position;
    m_coord_tex=coord_tex;
    }
};

class TableauDeScore {
    public:
        SDL_Surface *fondTableauDeScore = NULL;
        SDL_Surface *indicationDistance = NULL;
        SDL_Surface *indicationScore = NULL;
        SDL_Surface *indicationMeilleurScore = NULL;
        TTF_Font *font;
        SDL_Color textColor;
        GLuint texture = 0;

        TableauDeScore(TTF_Font *font, SDL_Color &textColor):
            font(font), textColor(textColor){};
        ~TableauDeScore()=default;
        void Draw(Program &program);

        void apply_surface( int x, int y, SDL_Surface* source);

        void creationTableauDeScore(int score, int meilleurScore, int distance);

        void tableauEnTexture(float x, float y);
        
        private:
            //  render data
        unsigned int VAO, VBO, IBO;

}; 

#endif
