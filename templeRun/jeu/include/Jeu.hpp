#ifndef JEU_HPP

#define JEU_HPP
#include "Cases.hpp"
#include <vector>
#include <string>
#include <map>
#include <deque>
#include <utility>
#include "variablesGlobales.hpp"

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
    void setEtat(int const newEtat) {etat=newEtat;};
    void setNom(std::string nom){nomPartie = nom;};
    std::deque<Case> getChemin(){return cheminVisible;};
    std::string getName() const {return nomPartie;};

    //exclusivement pour les chargements de partie ou recommencement de partie
    void resetPartie(){score=0; distance=0;};
    void setScore(int scoreAutrePartie){score=scoreAutrePartie;};
    void setDistance(int distanceAutrePartie){distance=distanceAutrePartie;};
    void setChemin(std::deque<Case> &chemin){cheminVisible=chemin;};

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
int chargerParties(std::string partiesACharger, std::deque <Partie> &partiesSauvegardees);
// std::vector<Partie> chargerMeilleuresParties(std::string partiesACharger, std::vector<Partie> &meilleuresParties);
int chargerMeilleuresParties(std::string partiesACharger, std::vector<std::pair<std::string, int>> &meilleursScores);


class Jeu
{
    private:
    //-----------------attributs--------------------------------
    std::deque <Partie> partiesSauvegardees;//vecteurs des noms des parties saves
    std::vector<std::pair<std::string, int>> meilleursScores;
    int meilleurScore;

    public:
    //------------------methodes-------------------------- 
    Partie partieEnCours; //peut etre à changer et mettre des variables plutot(?)
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
    Jeu(Partie &partie, std::string partiesACharger, std::string meilleuresPartiesACharger,int initScore=0):partieEnCours(partie){
        chargerParties(partiesACharger, partiesSauvegardees);
        chargerMeilleuresParties(meilleuresPartiesACharger, meilleursScores);
    };
    ~Jeu()=default;
};


#endif