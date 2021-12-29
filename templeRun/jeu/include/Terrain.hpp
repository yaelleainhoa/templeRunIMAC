#ifndef TERRAIN_HPP

#define TERRAIN_HPP
#include <iostream>
#include <deque>
#include "Jeu.hpp"
#include "Cases.hpp"
#include "Objets.hpp"
#include <random>
#include <time.h>

std::vector<Case*> creerCasesSansDanger(Partie &partie);
std::vector<Case*> creerCasesAvecDanger(Partie &partie);


#endif