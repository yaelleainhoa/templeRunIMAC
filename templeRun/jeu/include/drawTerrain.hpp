#ifndef DRAWTERRAIN_H
#define DRAWTERRAIN_H

#include "renderingTerrain.hpp"
#include "camera.hpp"


void drawTerrain(Program &program, 
                std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, 
                std::vector<Model> &obstacles, float &angle, TableauDeScore &menu, Partie &partieEnCours,
                Joueur &joueur,const std::vector<std::deque<Case>> &parcoursPossibles);


#endif