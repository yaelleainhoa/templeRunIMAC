#ifndef RENDERINGTERRAIN_H
#define RENDERINGTERRAIN_H

#include <iostream>
#include <deque>
#include <vector>
#include "../include/model.hpp"
#include "./../include/camera.hpp"

void setTerrain(std::string path, std::vector<Model> &sols, std::vector<Model> &murs);
void drawTerrain(Program &program, std::vector<Model> &sols, std::deque<int> &tableauDeSols, 
std::vector<Model> &murs, int &numeroCase, glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix, 
float time, bool &virage, float &angle, std::vector<Camera*> &listeCameras);

#endif