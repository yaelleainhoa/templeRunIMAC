#ifndef PERSONNAGE_HPP

#define PERSONNAGE_HPP
#include <iostream>
class Singes
{
    private:

    //attributs
    int distance_perso;
    int tours_restants; //(tours restants avant de reculer à nouveau)

    //methodes
    public:
    int getDistancePerso() const{return distance_perso;};
    int getToursRestants()const {return tours_restants;};
    void deplacement(int const nbCase){distance_perso+=nbCase; tours_restants=5;};//5 cases avant de retourner à sa case 

    Singes(int dis=2, int tours=-1):distance_perso(dis),tours_restants(tours) {};
    Singes(Singes const &copie):distance_perso(copie.distance_perso),tours_restants(copie.tours_restants){};
    ~Singes()=default;
};

class Joueur
{
    private :
    //-----------------attributs---------------------
    int position_vertical; //-1,0 ou 1
    int position_horizontal; //-1,0 ou 1
    Singes _singes;
    public:

    //-----------------methodes-----------------------
    int getPositionVerticale() const{return position_vertical;};//(-1,0,1)
    int getPositionHorizontale() const{return position_horizontal;};//(-1,0,1)
    Singes singes(){return _singes;};
    void glissade(){position_vertical=-1;};
    void saut(){position_vertical=1;};
    void sol(){position_vertical=0;};
    void mvtGauche();
    void mvtDroite();

    //constructeurs/destructeurs
    Joueur(int vert=0,int hori=0):position_vertical(vert), position_horizontal(hori),_singes(2){};
    Joueur(Joueur const &copie)=default;
    ~Joueur()=default;
};

#endif