#ifndef ETATDUJEU_H
#define ETATDUJEU_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


#include <glm/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <SDL/SDL.h>

#include "SDL/SDL_ttf.h"

#include "fenetresTextuelles.hpp"
#include "variablesGlobales.hpp"


#include "Jeu.hpp"

using namespace glimac;

void debut(Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, Partie &partieEnCours);

void pause(Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, Partie &partieEnCours);

void nom(Program &program, SDLWindowManager &windowManager, EntrerNomDeLaPartie &menu, bool &done, Partie &partieEnCours);

void rechargerParties(Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, std::deque<Partie> &partiesSauvegardees, Partie &partieJouee);

void meilleursScores(Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, Partie &partieEnCours);

void mort(Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done, Partie &partieEnCours);

void recharger(Partie &partieACharger, Partie &partieJouee);

void recommencer(Partie &partieEnCours);

#endif
