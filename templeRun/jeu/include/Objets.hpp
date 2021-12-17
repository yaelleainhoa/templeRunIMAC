#ifndef OBJETS_HPP

#define OBJETS_HPP

#include "Personnage.hpp"

class Objet
{
    //---------------attributs---------------------
    protected:
    int taille; // 1 ou 3 instancié grace au type d'objet (1 si pièce)
    int mvt; // {-1,0,1,null} mvt pour survivre ou recup la piece
    int const typeObjet;//piece =0 ou obstacle=1 (à faire)
    int const id_objet;//id de la texture correspondant à l'objet 
                 //(dans le tableau des textures de piece ou d'obstacle selon le type)

    public:
    //---------------methodes------------------------
    bool passe(Joueur joueur) ;// ⇒ si pos_joueur = mvt alors ok 
            //⇒ (mvt jamais null) [bool]
    int getMvt() const {return mvt;};
    int getTaille() const {return taille;};
    virtual int getTypeObjet() const {return typeObjet;};
    virtual int getIdObjet() const {return id_objet;};
    bool estPiece(){return id_objet==0;};//fct débiles mais plus clairs à l'utilisation
    bool estObstacle(){return id_objet==1;};//elle aussi
    //constructeurs/destructeurs
    Objet(int type=0, int id=0,int const t=1, int m=0)//si mvt=3 on ne peut passer nul part sur la sous case
        :typeObjet(type), id_objet(id), taille(t), mvt(m){};
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
    Piece(int const id_objet, int const mvt);
    Piece(const Piece &copie)
        :valeur(copie.valeur),Objet(copie.taille,copie.mvt){};

    ~Piece()=default;
};

class Obstacle : public Objet
{   //passe() jamais null
    private:
    //------------attributs-----------------
    //id_text 0: trous à gauche , 1 trou au milieu, 2 trou à droite 
    int gravite;//1 a une autre chance , 0 meurt direct
    
    //------------methodes------------------
    public:
    int getGravite(){return gravite;};
    //constructeurs/destructeurs
    Obstacle(int const t);
    Obstacle(const Obstacle &copie)=default;

    ~Obstacle()=default;
};

#endif