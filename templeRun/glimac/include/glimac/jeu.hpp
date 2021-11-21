#ifndef JEU_HPP

#define JEU_HPP
#include <vector>
#include <glimac/cases.hpp>
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
    void sauvegarder();

        //constructeurs/destructeurs
    Partie(std::string nom):nomPartie(nom),score(0),distance(0),etat(0){};
    Partie(Partie const &copie)=default;
    ~Partie()=default;
};


class Jeu 
{
    private:
    //attributs
    std::vector<Partie> partiesSauvegardees; //global jsp comment on fait
    int meilleurScore; //global aussi

    public:
    void ajoutePartieSauvergardee(Partie const newPartie){partiesSauvegardees.push_back(newPartie);};
    void setMeilleurScore(int const newMeilleurScore){meilleurScore=newMeilleurScore;};
    int getMeilleurScore() const {return meilleurScore;};

    Jeu(std::vector<Partie> parties= std::vector<Partie>() , int initScore=0 )
        :partiesSauvegardees(parties),meilleurScore(initScore){};
    ~Jeu()=default;
};


#endif