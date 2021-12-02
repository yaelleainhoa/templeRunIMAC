#ifndef JEU_HPP

#define JEU_HPP
#include <Cases.hpp>
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

    void incrementeScore(int const val) {score+=val;};
    void incrementeDistance(int const val=1){distance+=val;};
    std::string getName() const {return nomPartie;};

    /// \brief save a vector in a file
    /// \param filemane : name of the file (including path) where to save the vector data
    /// \return EXIT_SUCCESS if the file is save correctly, else EXIT_FAILURE 
    int sauvegarder(const std::string &filename) const;
//(regarder si le fichier existe deja si oui ecraser la sauvergarde sinon le créer) -> a chercher

    /// \brief load a vector from a file, the size of the vector should be already the good one ...
    /// \param filemane : name of the file (including path) to open and load the vector data
    /// \return EXIT_SUCCESS if the file is save correctly, else EXIT_FAILURE 
    
    int Partie::load(const std::string &filename);

        //constructeurs/destructeurs
    Partie(std::string nom):nomPartie(nom),score(0),distance(0),etat(0){};
    Partie(Partie const &copie)=default;
    ~Partie()=default;
};


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
    Jeu(std::vector<Partie> parties , int initScore=0 ){};
    ~Jeu()=default;
};


#endif