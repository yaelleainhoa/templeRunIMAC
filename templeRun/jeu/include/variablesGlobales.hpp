#pragma once

#include "camera.hpp"

extern int DEBUT;
extern int PAUSE;
extern int JEU;
extern int MEILLEURSSCORES;
extern int RECHARGER;
extern int RECOMMENCER;
extern int NOMPARTIE;
extern int ANCIENNESPARTIES;
extern int SAUVEGARDER;
extern int WARNING;
extern int MORT;

extern float largeur;
extern float vitesse;
extern float hauteur;
extern float positionLaterale;
extern float positionVerticale;
extern float x;
extern int score;
extern int etat;

extern int meilleurScore;
extern int distance;

extern int indiceBoucle;
extern float angleActuel;
extern float angleRotation;
extern int numCaseRot;
extern float phiStable;
extern bool virage;
extern bool alreadyRotated;
extern float distanceAuVirage;
extern int sensVirage;
extern int sensRotation;
extern float angleActuelCam;

extern float valIncremCameraRotationUP;
extern float valIncremCameraRotationDOWN;

extern float valIncremCameraRotationLEFT;
extern float valIncremCameraRotationRIGHT;

extern float valIncremCameraFRONT;
extern float valIncremCameraBACK;
extern int mouvementHorizontalTranslation;

extern int indiceCam;

extern glm::mat4 ModelMatrix;
extern glm::mat4 VMatrix;
extern glm::mat4 ProjMatrix;

extern std::vector<Camera*> listeCameras;
