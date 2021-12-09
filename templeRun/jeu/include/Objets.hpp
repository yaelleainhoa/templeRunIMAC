#ifndef OBJETS_HPP

#define OBJETS_HPP

#include "Personnage.hpp"

class Objet
{
    //---------------attributs---------------------
    protected:
    int taille; // 1 ou 3 instancié grace au type d'objet (1 si pièce)
    int mvt; // {0,1,2,null} mvt pour survivre ou recup la piece

    public:
    //---------------methodes------------------------
    bool passe(Joueur joueur) ;// ⇒ si pos_joueur = mvt alors ok 
            //⇒ (mvt jamais null) [bool]
    int getMvt(){return mvt;};
    int getTaille(){return taille;};
    //constructeurs/destructeurs
    Objet(int const t, int m)//si mvt=3 on ne peut passer nul part sur la sous case
        :taille(t), mvt(m){};
    Objet(const Objet &copie)=default;
    
    ~Objet()=default;
};


class Piece : public Objet
{ //passe() jamais 1

    private:
    //-----------attributs------------------
    int valeur;

    //-----------methodes-------------------
    public:
    int getValeur(){return valeur;};
    //constructeurs/destructeurs
    Piece(int const val, int const mvt)
        :valeur(val),Objet(1,mvt){};
    Piece(const Piece &copie)
        :valeur(copie.valeur),Objet(copie.taille,copie.mvt){};

    ~Piece()=default;
};

class Obstacle : public Objet
{   //passe() jamais null
    private:
    //------------attributs-----------------
    int type;
    int gravite;//1 a une autre chance , 0 meurt direct
    
    //------------methodes------------------
    public:
    int getGravite(){return gravite;};
    int getType(){return type;};
    //constructeurs/destructeurs
    Obstacle(int const t):
        Objet(0,1), type(t), gravite(0){};
    Obstacle(const Obstacle &copie)=default;

    ~Obstacle()=default;
};

#endif