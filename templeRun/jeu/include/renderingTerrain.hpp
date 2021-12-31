#ifndef RENDERINGTERRAIN_H
#define RENDERINGTERRAIN_H

#include <iostream>
#include <deque>
#include <vector>
#include "model.hpp"
#include "camera.hpp"
#include "Cases.hpp"
#include "rendering.hpp"
#include "fenetresTextuelles.hpp"
#include "moteurJeu.hpp"

float distanceCase(const glm::mat4 &Case);
float saut(float &x);
float baisser();

void setTerrain(std::string path, std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, std::vector<Model> &obstacles);
void destroyTerrain(std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, std::vector<Model> &obstacles);

void drawObject(Program &program, std::vector<Model> &typeObjet,
                int idText,
                float posX, float poxY, int posZ=0,
                float translation=0, float signe=0, int caseRotation=0, float rotationObjet=0.0f,
                float scaleX=1.0f, float scaleY=1.0f, float scaleZ=1.0f, int rouge=0);
            
void drawPersonnage(Program &program, std::vector<Model> &typeObjet, int idText,  
                    float rotationModel,
                    float scaleX, float scaleY, float scaleZ,
                    float posX, float poxY, float posZ=0, int rouge=0);

void drawObjetssCase(Program &program, const ssCase &ssCaseObjets, std::vector<Model> &pieces,
                std::vector<Model> &obstacles,
                float translation, float signe,
                int index, int caseRotation, int cas, int positionJoueur);


void drawObjetCase(Program &program, const Case &caseObjets, std::vector<Model> &pieces,
                std::vector<Model> &obstacles,
                float translation, float signe,
                int index, int caseRotation, int positionJoueur);
                
void drawCase(Program &program, std::vector<Model> &sols, 
                std::vector<Model> &murs, 
                float translation, float signe,
                int index, int caseRotation, int indiceTexture);

void tracerLampadaires(Program &program, std::vector<Model> &murs, 
                    float translation, float signe,
                    int i, int caseRotation, int indexCoupleLampadaire);

void drawCaseDeTransitionVirage(Program &program,
                std::vector<Model> &murs, 
                float translation);

void drawCaseDeTransition(Program &program,
                std::vector<Model> &sols, 
                float translation, Partie &partieEnCours);

void testObstacles(Program &program, float translation, std::vector<Model> &pieces, 
                    std::vector<Model> &obstacles, Partie &partie, TableauDeScore &tableauDeScore);

void drawTerrain(Program &program, 
                std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, 
                std::vector<Model> &obstacles, float &angle, TableauDeScore &menu, Partie &partieEnCours,
                Joueur &joueur,const std::vector<std::deque<Case>> &parcoursPossibles);


#endif