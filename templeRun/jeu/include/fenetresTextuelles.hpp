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

#include "variablesGlobales.hpp"
#include "Jeu.hpp"

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

        //applique la SDL_Surface source sur fondFenetreTextuelle 
        //à la position (x,y) sur cette fenetre
        void apply_surface( int x, int y, SDL_Surface* source);

        //applique la SDL_Surface créee sur une surface
        void fenetreEnTexture(float x, float y, float longueur, float largeur);

        //crée les messages selon le type de fenetre textuelle et l'applique sur fondFenetreTextuelle
        virtual void creation() = 0;
        
}; 

class TableauDeScore : public FenetreTextuelle {
    private:
        int score;
        int meilleureScore;
        int distance;
    public:
        TableauDeScore(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
        void setTableauDeScore(const Partie &partie);
        void creation() override;
        void updateScore(const Partie &partie){score=partie.getScore(); creation();};
        void updateDistance(const Partie &partie){distance=partie.getDistance(); creation();};;

};

class MenuPause : public FenetreTextuelle{
    public:
            MenuPause(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
        void creation() override;
};

class MenuDebutDePartie : public FenetreTextuelle{
    public:
            MenuDebutDePartie(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
    void creation() override;
};

class AffichageMeilleursScores : public FenetreTextuelle{
    private:
        std::vector<std::pair<std::string, int>> meilleursScoresJeu;
    public:
            AffichageMeilleursScores(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
            inline void setMeilleursParties(std::vector<std::pair<std::string, int>> &scores){meilleursScoresJeu=scores;};
            void creation() override;
};

class AffichageAnciennesPartiesSauvegardees : public FenetreTextuelle{
    private:
        std::deque<Partie> anciennesParties;
    public:
            AffichageAnciennesPartiesSauvegardees(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
            inline void setAnciennesParties(std::deque<Partie>& parties){anciennesParties=parties;};
            void creation() override;
};

class EntrerNomDeLaPartie : public FenetreTextuelle{
    private:
        std::string nomPartie;
    public:
            EntrerNomDeLaPartie(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
            inline void setNomPartie(const std::string& partie){nomPartie=partie;};
            void creation() override;
            void updateNom(const std::string &nouveauNom){nomPartie=nouveauNom; creation();};
};

class Mort : public FenetreTextuelle{
    public:
            Mort(TTF_Font *font, SDL_Color &textColor)
            :FenetreTextuelle(font, textColor){};
        void creation();
};

#endif
