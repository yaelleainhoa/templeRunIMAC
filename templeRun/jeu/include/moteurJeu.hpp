#ifndef MOTEURJEU_HPP

#define MOTEURJEU_HPP

#include "Jeu.hpp"
#include "Objets.hpp"
#include "Personnage.hpp"
#include "Cases.hpp"
#include <vector>
#include <deque>
#include <iostream>
#include <fstream>
#include "variablesGlobales.hpp"
#include <random>
#include <time.h>

void testMvtssCase(ssCase courante, Joueur joueur, Partie &partie );
void testMvt(Case courante, Joueur joueur, Partie &partie );
std::deque<Case> creerCasesAvecDanger();//creation de Cases avec obstacles 

std::deque<Case> creerCasesSansDanger();//creation de Cases sans obstacle

#endif