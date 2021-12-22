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

#include "jeu.hpp"

using namespace glimac;

void debut(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done);

void pause(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done);

void nom(int &etat, Program &program, SDLWindowManager &windowManager, EntrerNomDeLaPartie &menu, bool &done);

void warning(int &etat, Program &program, SDLWindowManager &windowManager, Warning &menu, bool &done);

void recharger(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done);

void meilleursScores(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done);

void mort(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done);

void recharger();

void recommencer();

#endif
