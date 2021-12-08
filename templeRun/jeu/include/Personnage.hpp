#ifndef PERSONNAGE_HPP

#define PERSONNAGE_HPP

class Joueur
{
    private :
    //-----------------attributs---------------------
    int position_vertical;
    int position_horizontal;

    public:
    //-----------------methodes-----------------------
    int getPositionVerticale(){return position_vertical;};
    int getPositionHorizontale(){return position_horizontal;};
    void glissade(){position_vertical=0;};
    void saut(){position_vertical=2;};
    void mvtGauche();
    void mvtDroite();

    //constructeurs/destructeurs
    Joueur():position_vertical(1), position_horizontal(1){};
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
    void deplacement(int nbCase){distance_perso+=nbCase;};

    Singes();
    ~Singes()=default;
};

#endif