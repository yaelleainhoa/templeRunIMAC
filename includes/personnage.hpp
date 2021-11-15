#ifndef PERSONNAGE_HPP

#define PERSONNAGE_HPP

class Joueur
{
    private :
    //attributs
    int position_vertical;
    int position_horizontal;

    public:
    //methode
    int getPositionVerticale();
    int getPositionHorizontale();
    void glissade();
    void saut();
    void mvtGauche();
    void mvtDroite();

    Joueur();
    ~Joueur();
};


class Singes
{
    private:

    //attributs
    int distance_perso;
    int tours_restants; //(tours restants avant de reculer à nouveau)

    //methodes
    void deplacement(int nbCase);

    Singes();
    ~Singes();
};

#endif