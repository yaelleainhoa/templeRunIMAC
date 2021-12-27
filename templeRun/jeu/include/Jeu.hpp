#ifndef JEU_HPP

#define JEU_HPP
#include "Cases.hpp"
#include <vector>
#include <string>
#include <map>
#include <deque>

class Partie
{
    private:
    //---------attributs---------------
    std::string nomPartie;
    int score;
    int distance;
    int etat;//0=pause, 1=en cours, 2=fini(mort)
    
    public:
    std::deque<Case> cheminVisible; //(pointeur vers la première case ? pile?file? file à deux bouts?)

    //----------methodes-----------------
    int getScore() const {return score;};
    int getDistance() const {return distance;};
    int getEtat() const {return etat;};
    void setEtat(int const newEtat) {etat=newEtat; std::cout<< "etat = "<<etat<<std::endl;};
    std::string getName() const {return nomPartie;};

    void incrementeScore(int const val) {score+=val;};
    void incrementeDistance(int const val=1){distance+=val;};

    /// \brief save a vector in a file
    /// \return EXIT_SUCCESS if the file is save correctly, else EXIT_FAILURE 
    int sauvegarder() const;

        //constructeurs/destructeurs
    Partie(std::string nom,const std::deque<Case> chem, int mscore=0,int mdistance=0,int metat=0)
        :nomPartie(nom),cheminVisible(chem), score(mscore),distance(mdistance),etat(metat){};
    Partie(std::string nom, Partie const &copie)
        :nomPartie(nom),cheminVisible(copie.cheminVisible),score(copie.getScore()),distance(copie.getDistance()),etat(copie.getEtat()){};
    ~Partie()=default;
};

/// \brief load a vector from a file, the size of the vector should be already the good one ...
/// \return EXIT_SUCCESS if the file is save correctly, else EXIT_FAILURE 
Partie charger(std::string nomPartie);
void supprimer(std::string nomPartie);

class Jeu
{
    private:
    //-----------------attributs--------------------------------
    std::deque <Partie> partiesSauvegardees;//vecteurs des noms des parties saves
    std::vector<Partie> meilleuresParties; //vecteur des 5(?) meilleures parties

    public:
    //------------------methodes-------------------------- 
    void ajoutePartieSauvergardee(Partie const &newPartie);
    void ajouteMeilleurePartie(Partie const &newPartie);
    std::vector<Partie> getListeMeilleuresParties() const {return meilleuresParties;};
    std::deque<Partie> getPartiesSauvegardees() const {return partiesSauvegardees;};
    int nbPartiesSauvegardees() const{return partiesSauvegardees.size();};
    void displayPartiesSauvegardrees() const;
    void displayMeilleuresParties() const;
        //constructeurs/destructeurs
    Jeu(std::deque<Partie> parties , int initScore=0 );
    ~Jeu()=default;
};


#endif