#ifndef PERSONNAGE_HPP

#define PERSONNAGE_HPP
#include <iostream>
class Singes
{
    private:

    //attributs
    int distance_perso;
    int tours_restants; //(tours restants avant de reculer à nouveau) -> -1 qd aucun deplacement en cours 

    //methodes
    public:
    int getDistancePerso() const{return distance_perso;};
    inline const int getToursRestants(){return tours_restants;};
    inline void setToursRestants(const int & nbTours){tours_restants=nbTours;};
    inline void retireToursRestants(const int nbTours=1){tours_restants-=nbTours;};
    inline void initialiseDistanceSinges(){setToursRestants(5);};
    void deplacement(int const nbCase){distance_perso+=nbCase; //tours_restants=5;
                                    //std::cout << "distance singe apres deplacement ="<< tours_restants<< std::endl;
                                    };
                                    //5 cases avant de retourner à sa case 

    Singes(int dis=2, int tours=5):distance_perso(dis),tours_restants(tours) {};
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
    int getPositionVerticale(){return position_vertical;};//(-1,0,1)
    int getPositionHorizontale(){return position_horizontal;};//(-1,0,1)
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