#ifndef RENDERINGTERRAIN_HPP
#define RENDERINGTERRAIN_HPP

#include <iostream>
#include <deque>
#include <vector>
#include "model.hpp"
#include "camera.hpp"
#include "Cases.hpp"
#include "fenetresTextuelles.hpp"
#include "moteurJeu.hpp"

/*---fonctions pour calcul----*/
//la distance entre une case (dont on envoie la matrice model) et le joueur (la position 0)
float distanceCase(const glm::mat4 &Case);

//renvoie la position verticale du joueur s'il saute, la trajectoire se basant sur un polynome de Lagrange
//puisqu'on souhaite juste qu'il passe par 3 points
float saut(float &x);

//la taille du joueur qui se remet à 0 après un certain temps, comme pour le saut
float baisser();


/*--fonctions pour dessiner le terrain---*/

//ici on initialise tous les modeles relatifs au dessin du terrain
void setTerrain(std::string path, std::vector<Model> &sols, std::vector<Model> &murs, std::vector<Model> &pieces, std::vector<Model> &obstacles);

//Pour tous les objets tracés (qui suivent la rotation du terrain ou non, l'avancement du terrain)
//signe indique la rotation (0 s'il n'y en a pas, et -1 ou 1 s'il tourne à gauche ou droite)
//rotation objet sert pour les pièces qui tournent sur elles mêmes
//rouge sert aux obstacles, elle vaut 0 par défaut mais vaut 1 si l'obstacle est touché
void drawObject(Program &program, std::vector<Model> &typeObjet,
                int idText,
                float posX, float poxY, int posZ=0,
                float translation=0, float signe=0, int caseRotation=0, float rotationObjet=0.0f,
                float scaleX=1.0f, float scaleY=1.0f, float scaleZ=1.0f, int rouge=0);
            
//la fonction ressemble à celle d'au dessus, mais sert aux objets qui restent au centre 
//ils n'ont donc pas besoin de rotation du terrain et d'avancement
void drawPersonnage(Program &program, std::vector<Model> &typeObjet, int idText,  
                    float rotationModel,
                    float scaleX, float scaleY, float scaleZ,
                    float posX, float poxY, float posZ=0, int rouge=0);


//dessine les obstacles et pièce sur une sous case
void drawObjetssCase(Program &program, const ssCase &ssCaseObjets, std::vector<Model> &pieces,
                std::vector<Model> &obstacles,
                float translation, float signe,
                int index, int caseRotation, int cas, int positionJoueur);

//dessine les obstacles et pièce sur une case
void drawObjetCase(Program &program, const Case &caseObjets, std::vector<Model> &pieces,
                std::vector<Model> &obstacles,
                float translation, float signe,
                int index, int caseRotation, int positionJoueur);
                
//dessine les cases sans les objets : le sol, les buissons, les trottoirs
void drawCase(Program &program, std::vector<Model> &sols, 
                std::vector<Model> &murs, 
                float translation, float signe,
                int index, int caseRotation, int indiceTexture);

//dessine les lampadaires et met à jour la position des lumières ponctuelles
void drawLampadaires(Program &program, std::vector<Model> &murs, 
                    float translation, float signe,
                    int i, int caseRotation, int indexCoupleLampadaire);

void drawCaseDeTransitionVirage(Program &program,
                std::vector<Model> &murs, 
                float translation);

void drawCaseDeTransition(Program &program,
                std::vector<Model> &sols, 
                float translation, Partie &partieEnCours);

//regarde si la case la plus proche est assez proche pour être testée (voir si 
//le personnage attrape une pièce ou n'arrive pas à éviter un obstacle) et appelle la fonction de test
void testObstacles(Program &program, float translation, std::vector<Model> &pieces, 
                    std::vector<Model> &obstacles, Case &caseTest, Joueur &joueur, 
                    Partie &partie, TableauDeScore &tableauDeScore);

#endif