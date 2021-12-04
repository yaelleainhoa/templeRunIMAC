#ifndef FENETRESTEXTUELLES_H
#define FENETRESTEXTUELLES_H

#include <GL/glew.h>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDL/SDL_ttf.h"
#include <string>
#include <glm/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <iostream>

using namespace glimac;

struct Vertex2DUV{
    glm::vec2 m_position;
    glm::vec2 m_coord_tex;

    Vertex2DUV(glm::vec2 position, glm::vec2 coord_tex){
    m_position=position;
    m_coord_tex=coord_tex;
    }
};

class FenetreTextuelle {
    protected:
        SDL_Surface *fondFenetreTextuelle = NULL;
        TTF_Font *font;
        SDL_Color textColor;
        GLuint texture = 0;
        unsigned int VAO, VBO, IBO;

    public:
        FenetreTextuelle(TTF_Font *font, SDL_Color &textColor):
            font(font), textColor(textColor){};
        ~FenetreTextuelle()=default;
    
        void Draw(Program &program);

        void apply_surface( int x, int y, SDL_Surface* source);

        void fenetreEnTexture(float x, float y, float longueur, float largeur);
        

}; 

class TableauDeScore : public FenetreTextuelle {
    public:
        TableauDeScore(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
        void creationTableauDeScore(int score, int meilleurScore, int distance);

};

class MenuPause : public FenetreTextuelle{
    public:
            MenuPause(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
        void creationMenuPause();
};

class MenuDebutDePartie : public FenetreTextuelle{
    public:
            MenuDebutDePartie(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
        void creationMenuDebutDePartie();
};

class AffichageMeilleursScores : public FenetreTextuelle{
    public:
            AffichageMeilleursScores(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
        void creationAffichageMeilleursScores();
};

class AffichageAnciennesPartiesSauvegardees : public FenetreTextuelle{
    public:
            AffichageAnciennesPartiesSauvegardees(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
        void creationAffichageAnciennesPartiesSauvegardees();
};

class EntrerNomDeLaPartie : public FenetreTextuelle{
    public:
            EntrerNomDeLaPartie(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
        void creationEntrerNomDeLaPartie(std::string &nomPartie);
};

#endif
