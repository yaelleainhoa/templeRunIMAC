#ifndef RENDERINGTERRAIN_H
#define RENDERINGTERRAIN_H

#include <iostream>
#include <deque>
#include <vector>
#include "../include/model.hpp"
#include "./../include/camera.hpp"
#include "cases.hpp"
#include "rendering.hpp"

float distanceCase(const glm::mat4 ModelMatrix);

float saut();

float distanceCase(const glm::mat4 ModelMatrix);
float saut();

void setTerrain(std::string path, std::vector<Model> &sols, std::vector<Model> &murs);
void destroyTerrain(std::vector<Model> &sols, std::vector<Model> &murs);

void drawObject(Program &program, float posX, float poxY,
                glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,
                std::vector<Model> &typeObjet, int idText, float translation, float signe, int caseRotation,
                int index, float scaleX, float scaleY, float scaleZ, float rotationObjet);

void drawCase(Program &program, std::vector<Model> &sols, 
                std::deque<int> &tableauDeSols, std::vector<Model> &murs, 
                glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,
                float translation, float signe,
                int index, int caseRotation);

void drawCaseDeTransition(Program &program,
                std::vector<Model> &murs, 
                glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,float translation, std::vector<Camera*> &listeCameras);

void drawTerrain(Program &program, std::vector<Model> &sols, std::deque<int> &tableauDeSols, 
std::vector<Model> &murs, glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix, 
/*float time,*/float &angle, std::vector<Camera*> &listeCameras);

// void drawObjetCase(Program &program, const Case caseObjets, std::vector<Model> &pieces,
//                 std::vector<Model> &obstacles,
//                 glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,
//                 float translation, float signe,
//                 int index, int caseRotation)

// void drawObjetssCase(Program &program, const ssCase ssCaseObjets, std::vector<Model> &pieces,
//                 std::vector<Model> &obstacles,
//                 glm::mat4 &ModelMatrix, glm::mat4 &VMatrix, glm::mat4 &ProjMatrix,
//                 float translation, float signe,
//                 int index, int caseRotation, int cas)

#endif