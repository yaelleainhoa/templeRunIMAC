#ifndef JEU_HPP

#define JEU_HPP
#include "Cases.hpp"
#include <vector>
#include <string>
#include <map>
#include <deque>
#include <utility>
#include "variablesGlobales.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <filesystem> 	 	 	
#include <glimac/FilePath.hpp>


class Partie
{
    private:
    //---------attributs---------------
    std::string nomPartie;
    int score;
    int distance;
    int etat;//les différents etats sont enumérés dans variableGlobales.hpp/cpp
    int numeroCaseRotation;//distance à la prochaine case rotation
    int sensRotationVirage;//sens de la rotation
    int casDeTerrain;//début du jeu, pendant le jeu ou sur un virage -> permet de bien dessiner les cases derrière le joueur
    
    public:
    std::deque<Case> cheminVisible; //deque afin de pouvoir à la fois ajouter des cases devant le joueur et en enlever dèrriere 

    //----------méthodes-----------------
    //-> getter:
    inline int getScore() const {return score;};
    inline int getDistance() const {return distance;};
    inline int getEtat() const {return etat;};
    inline int getNumeroCaseRotation() const {return numeroCaseRotation;};
    inline int getSensRotation() const {return sensRotationVirage;};
    inline int getCasDeTerrain() const {return casDeTerrain;};
    inline std::deque<Case> getChemin() const {return cheminVisible;};
    inline std::string getName() const {return nomPartie;};
    //-> setter:
    inline void setEtat(int const &newEtat) {etat=newEtat;};
    inline void setNom(std::string const &nom){nomPartie = nom;};
    

    //exclusivement pour les chargements de partie ou recommencement de partie
    inline void resetPartie(){score=0; distance=0;};
    inline void setScore(int scoreAutrePartie){score=scoreAutrePartie;};
    inline void setDistance(int distanceAutrePartie){distance=distanceAutrePartie;};
    inline void setChemin(std::deque<Case> &chemin){cheminVisible=chemin;};

    inline void incrementeScore(int const val) {score+=val;};
    inline void incrementeDistance(int const val=1){distance+=val;};
    
    int sauvegarder() const;
    void sauvegarderSsCase(const ssCase &ssCase,std::ofstream &myfile) const;

        //constructeurs/destructeurs
    Partie(std::string nom, const std::deque<Case> &chem, int mscore=0,int mdistance=0,int metat=0, int mnumCaseRot=0, int msensRotation=0, int mcasTerrain=0)
        :nomPartie(nom),cheminVisible(chem), score(mscore),distance(mdistance),etat(metat), numeroCaseRotation(mnumCaseRot), sensRotationVirage(msensRotation), casDeTerrain(mcasTerrain){};
    Partie(std::string nom, Partie const &copie)
        :nomPartie(nom),cheminVisible(copie.cheminVisible),score(copie.getScore()),distance(copie.getDistance()),etat(copie.getEtat()){};
    ~Partie()=default;
};


Partie charger(std::string &nomPartie);
void supprimer(std::string &nomPartie);
int chargerParties(std::string partiesACharger, std::deque <Partie> &partiesSauvegardees);
int chargerMeilleuresParties(std::string partiesACharger, std::vector<std::pair<std::string, int>> &meilleursScores);


class Jeu
{
    private:
    //-----------------attributs--------------------------------
    static Jeu* instance;
    std::deque <Partie> partiesSauvegardees;//vecteurs des noms des parties saves
    std::vector<std::pair<std::string, int>> meilleursScores;
    //int meilleurScore;

    public:
    //------------------methodes-------------------------- 
    static Jeu* getInstance(){
        if(instance == nullptr){
            instance = new Jeu();
        }
        return instance;
    }
    void ajoutePartieSauvergardee(Partie const &newPartie);
    void ajouteMeilleurePartie(Partie const &newPartie);
    std::vector<std::pair<std::string, int>> getListeMeilleuresParties() const {return meilleursScores;};
    std::deque<Partie> getPartiesSauvegardees() const {return partiesSauvegardees;};
    int nbPartiesSauvegardees() const{return partiesSauvegardees.size();};
    void displayPartiesSauvegardrees() const;
    void displayMeilleuresParties() const;
    int sauvegarderJeu(std::string partiesASauvegarder);
    int sauvegarderMeilleur(std::string meilleuresPartiesASauvegarder);
    //constructeurs/destructeurs
    void chargerJeu(std::string partiesACharger, std::string meilleuresPartiesACharger,int initScore=0){
        chargerParties(partiesACharger, partiesSauvegardees);
        chargerMeilleuresParties(meilleuresPartiesACharger, meilleursScores);
    };
    ~Jeu()=default;
};


#endif