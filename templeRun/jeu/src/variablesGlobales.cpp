#include "../include/variablesGlobales.hpp"

int DEBUT=0;
int PAUSE=1;
int JEU=2;
int MEILLEURSSCORES=3;
int RECHARGER=4;
int RECOMMENCER=5;
int NOMPARTIE=6;
int ANCIENNESPARTIES=7;
int SAUVEGARDER=8;
int WARNING=9;
int MORT=10;

int casesDerrierePersonnage=3;
float largeur=1.5;
float vitesse=2.0;
float hauteur=2.0;
float positionLaterale=0.0;
float positionVerticale=0.0;
float positionVerticaleGlissade=0.0;
float x=largeur;
float xBaisse=largeur;
float taille=1;
int score=0;
int etat = DEBUT;

int meilleurScore=100;
int distance=0;

int indiceBoucle=0;
float angleActuel=0;
float angleRotation = 90.0f*M_PI/180.0;
int numCaseRot = casesDerrierePersonnage-1;
float phiStable; //a quoi il sert??
bool virage = false;
bool alreadyRotated = false;
float distanceAuVirage = 1;
int sensVirage = 1;
int sensRotation = 1;
int casTerrain=2;

float rotationPersonnage = 0;

float valIncremCameraRotationUP = 0.5;
float valIncremCameraRotationDOWN = -0.5;

float valIncremCameraRotationLEFT = 0.5;
float valIncremCameraRotationRIGHT = -0.5;

float valIncremCameraFRONT = 0.5;
float valIncremCameraBACK = -0.5;
int mouvementHorizontalTranslation = 0;

int indiceCam=0;

glm::mat4 ModelMatrix=glm::mat4(1);
glm::mat4 VMatrix=glm::mat4(1);
glm::mat4 ProjMatrix=glm::mat4(1);

std::vector<Camera*> listeCameras;
float hauteurInitFreeflyCamera = 2.0f;

std::string nomDePartie=" ";
int indiceChemin=0;
int indiceTest=0;

LumieresScenes lumScenePonct;

//int NB_TOURS_SINGES=-1;

bool testAFaire=true;

int indiceDepart=0;

uint etatSinges = 0;
bool poursuite1 = false;
bool poursuite2 = false;
float distanceSingesPerso = 0;

bool EstCeQuePersoSaute = false;
bool EstCeQuePersoBaisse = false;
