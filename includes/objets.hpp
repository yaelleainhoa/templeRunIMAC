#ifndef OBJETS_HPP

#define OBJETS_HPP

class Objet
{
    private:
    //attributs
    int mvt; // {0,1,2,null} mvt pour survivre ou recup la piece

    public:
    //methodes
    bool passe() // ⇒ si pos_joueur = mvt alors ok 
            //⇒ (mvt jamais null) [bool]
    int getMvt();
    Objet(int mvt);
    ~Objet();
}


class Piece : public Objet
{ //passe() jamais 1
    private:
    //attributs
    int const valeur;

    //methode
    public:
    Piece();
    Piece(int valeur, int mvt);
    ~Piece();
}

class Obstacle : public Objet
{   //passe() jamais null
    private:
    //attributs
    int const type;
    int const gravité;
    int const taille; //instancié grace au type d'obstacle

    //methodes
    public:
    Obstacle();
    Obstacle(int type, int gravite);
    ~Obstacle();
}

#endif

