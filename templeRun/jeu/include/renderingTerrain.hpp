#ifndef RENDERINGTERRAIN_H
#define RENDERINGTERRAIN_H

#include <iostream>
#include <deque>
#include <vector>
#include "../include/model.hpp"
#include "./../include/camera.hpp"
#include "cases.hpp"
#include "rendering.hpp"

float distanceCase(const glm::mat4 Case);
float saut();
float baisser();

void setTerrain(std::string path, std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, std::vector<Model> &obstacles);
void destroyTerrain(std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, std::vector<Model> &obstacles);

void drawObject(Program &program, float posX, float poxY,
                std::vector<Model> &typeObjet, int idText, float translation, float signe, int caseRotation,
                int index, float scaleX, float scaleY, float scaleZ, float rotationObjet);
            
void drawPersonnage(Program &program, float posX, float poxY,
                std::vector<Model> &typeObjet, int idText, float scaleX=1.0f, float scaleY=1.0f, float scaleZ=1.0f);
                
void drawCase(Program &program, std::vector<Model> &sols, 
                std::deque<int> &tableauDeSols, std::vector<Model> &murs, 
                float translation, float signe,
                int index, int caseRotation, int indiceTexture);

void drawCaseDeTransition(Program &program,
                std::vector<Model> &murs, 
                float translation);

void drawTerrain(Program &program, std::vector<Model> &sols, std::deque<int> &tableauDeSols, 
std::vector<Model> &murs, float &angle);

// void drawObjetCase(Program &program, const Case caseObjets, std::vector<Model> &pieces,
//                 std::vector<Model> &obstacles,
//                 float translation, float signe,
//                 int index, int caseRotation)

// void drawObjetssCase(Program &program, const ssCase ssCaseObjets, std::vector<Model> &pieces,
//                 std::vector<Model> &obstacles,
//                 float translation, float signe,
//                 int index, int caseRotation, int cas)

#endif