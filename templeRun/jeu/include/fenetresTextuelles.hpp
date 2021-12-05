#ifndef FENETRESTEXTUELLES_H
#define FENETRESTEXTUELLES_H

#include <string>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <SDL/SDL.h>

#include "SDL/SDL_ttf.h"

#include "jeu.hpp"

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
        void creationAffichageMeilleursScores(std::vector<Partie> meilleuresParties);
};

class AffichageAnciennesPartiesSauvegardees : public FenetreTextuelle{
    public:
            AffichageAnciennesPartiesSauvegardees(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
        void creationAffichageAnciennesPartiesSauvegardees(std::vector<Partie> anciennesParties);
};

class EntrerNomDeLaPartie : public FenetreTextuelle{
    public:
            EntrerNomDeLaPartie(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
        void creationEntrerNomDeLaPartie(std::string &nomPartie);
};

class Warning : public FenetreTextuelle{
    public:
            Warning(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
        void creationWarning(int type=0);
};

void debut(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done);

void pause(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done);

void nom(int &etat, Program &program, SDLWindowManager &windowManager, EntrerNomDeLaPartie &menu, bool &done, std::string &nomDePartie);

void warning(int &etat, Program &program, SDLWindowManager &windowManager, Warning &menu, bool &done, std::string &nomDePartie);

void recharger(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done);

void meilleursScores(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done);

#endif
