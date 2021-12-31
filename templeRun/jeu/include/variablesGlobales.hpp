#pragma once

#include "camera.hpp"
#include "lumiere.hpp"

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
extern int DEBUTDEPARTIE;

extern float largeur;
extern float vitesse;
extern float hauteur;
extern float positionLaterale;
extern float positionVerticale;
extern float positionVerticaleGlissade;
extern float x;
extern float xBaisse;
extern float taille;
extern int score;
extern int etat;

extern int meilleurScore;
extern int distance;

extern int casesDerrierePersonnage;
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
extern int casTerrain;

extern float rotationPersonnage;

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
extern float hauteurInitFreeflyCamera;

extern std::string nomDePartie;
extern int indiceChemin;
extern int indiceTest;

extern LumieresScenes lumScenePonct;

extern int NB_TOURS_SINGES;

extern bool testAFaire;

extern int indiceDepart;

extern uint etatSinges;
extern bool poursuite1;
extern bool poursuite2;
extern float distanceSingesPerso;

extern bool EstCeQuePersoSaute;
extern bool EstCeQuePersoBaisse;
extern float rotationPiece;
