#ifndef PERSONNAGE_HPP

#define PERSONNAGE_HPP

class Joueur
{
    private :
    //-----------------attributs---------------------
    int position_vertical; //-1,0 ou 1
    int position_horizontal; //-1,0 ou 1

    public:
    //-----------------methodes-----------------------
    int getPositionVerticale(){return position_vertical;};
    int getPositionHorizontale(){return position_horizontal;};
    void glissade(){position_vertical=-1;};
    void saut(){position_vertical=1;};
    void mvtGauche();
    void mvtDroite();

    //constructeurs/destructeurs
    Joueur(int vert=1,int hori=1):position_vertical(vert), position_horizontal(hori){};
    Joueur(Joueur const &copie)=default;
    ~Joueur()=default;
};


class Singes
{
    private:

    //attributs
    int distance_perso;
    int tours_restants; //(tours restants avant de reculer à nouveau)

    //methodes
    public:
    int getDistancePerso(){return distance_perso;};
    int getToursRestants(){return tours_restants;};
    void deplacement(int nbCase){distance_perso+=nbCase; tours_restants=5;};//5 cases avant de retourner à sa case 

    Singes(int dis=1):distance_perso(dis){};
    Singes(Singes &copie):distance_perso(copie.distance_perso),tours_restants(copie.tours_restants){};
    ~Singes()=default;
};

#endif