#ifndef JEU_HPP

#define JEU_HPP
#include "Cases.hpp"
#include <vector>
#include <string>

class Partie
{
    private:
    //---------attributs---------------
    std::string nomPartie;
    int score;
    int distance;
    int etat;//0=pause, 1=en cours, 2=fini(mort)
    
    public:
    const Case* cheminVisible; //(pointeur vers la première case ? pile?file? file à deux bouts?)

    //----------methodes-----------------
    int getScore() const {return score;};
    int getDistance() const {return distance;};
    int getEtat() const {return etat;};
    void setEtat(int const newEtat) {etat=newEtat;};
    std::string getName() const {return nomPartie;};

    void incrementeScore(int const val) {score+=val;};
    void incrementeDistance(int const val=1){distance+=val;};

    /// \brief save a vector in a file
    /// \return EXIT_SUCCESS if the file is save correctly, else EXIT_FAILURE 
    int sauvegarder() const;

    /// \brief load a vector from a file, the size of the vector should be already the good one ...
    /// \return EXIT_SUCCESS if the file is save correctly, else EXIT_FAILURE 


        //constructeurs/destructeurs
    Partie(std::string nom,int mscore=0,int mdistance=0,int metat=0):nomPartie(nom),score(mscore),distance(mdistance),etat(metat){};
    Partie(Partie const &copie)=default;
    ~Partie()=default;
};

Partie load(std::string nomPartie);


class Jeu 
{
    private:
    //-----------------attributs--------------------------------
    //std::vector<Partie> partiesSauvegardees;
    std::vector<std::string> partiesSauvegardees;//vecteurs des noms des parties saves
    int static meilleurScore; 

    public:
    //------------------methodes-------------------------- 
    void ajoutePartieSauvergardee(Partie const newPartie){};

    void static setMeilleurScore(int const newMeilleurScore){meilleurScore=newMeilleurScore;};
    int getMeilleurScore() const {return meilleurScore;};
        //constructeurs/destructeurs
    Jeu(std::vector<std::string> parties , int initScore=0 ){};
    ~Jeu()=default;
};


#endif