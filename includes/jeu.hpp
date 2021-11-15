#ifndef JEU_HPP

#define JEU_HPP
#include <vector>
#include <cases.hpp>
#include <string>

class Partie
{
    private:
    //attributs
    std::string const nomPartie; //(null par defaut)
    int score;
    int distance;
    int etat;
    
    public:
    const Case* cheminVisible; //(pointeur vers la première case ? pile?file? file à deux bouts?)

    //methodes
    void incrementeScore(int const val);
    void sauvegarder();
    int getScore() const;
    int getDistance() const;
    int getEtat() const;
    void setEtat(int etat);

    Partie(std::string nomPartie);
    ~Partie();
};


class Jeu 
{
    private:
    //attributs
    std::vector<Partie> partiesSauvegardees; //global jsp comment on fait
    int meilleurScore; //global aussi

    public:
    void ajoutePartieSauvergardee(Partie const newPartie);
    void setMeilleurScore(int const newMeilleurScore);
    int getMeilleurScore() const ;

    Jeu(std::vector<Partie> partiesSauvegardees= std::vector<Partie>() , int meilleurScore=0 );
    ~Jeu();
};


#endif