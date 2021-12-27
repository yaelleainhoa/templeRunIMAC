#ifndef ETATDUJEU_H
#define ETATDUJEU_H

#include <string>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <SDL/SDL.h>

#include "SDL/SDL_ttf.h"

#include "fenetresTextuelles.hpp"
#include "variablesGlobales.hpp"

//#include "Jeu.hpp"

using namespace glimac;

void debut(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done);

void pause(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done);

void nom(int &etat, Program &program, SDLWindowManager &windowManager, EntrerNomDeLaPartie &menu, bool &done, Partie &partie);

void warning(int &etat, Program &program, SDLWindowManager &windowManager, Warning &menu, bool &done);

void rechargerParties(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, std::deque<Partie> &partiesSauvegardees);

void meilleursScores(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, std::vector<Partie> &meilleuresParties);

void mort(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done);

void recharger(Partie &partieACharger);

void recommencer();

#endif
