#ifndef OBJETS_HPP

#define OBJETS_HPP

#include "Personnage.hpp"

class Objet
{
    //---------------attributs---------------------
    protected:
    int taille; // 1 ou 3 instancié grace au type d'objet (1 si pièce)
    int mvt; // {-1,0,1} mvt pour survivre ou recup la piece
    int const typeObjet;//piece =0 ou obstacle=1
    int const id_objet;//id de la texture correspondant à l'objet 
                 //(dans le tableau des textures de piece ou d'obstacle selon le type)

    public:
    //---------------methodes------------------------
    bool passe(Joueur joueur) ;// ⇒ si pos_joueur = mvt alors ok 
            //⇒ (mvt jamais null) [bool]
    int getMvt() const {return mvt;};
    int getTaille() const {return taille;};
    int getTypeObjet() const {return typeObjet;};
    int getIdObjet() const {return id_objet;};
    bool estPiece(){return typeObjet==0;};//fct débiles mais plus clairs à l'utilisation
    bool estObstacle(){return typeObjet==1;};//elle aussi
    //constructeurs/destructeurs
    Objet(int type, int id,int const t, int m)
        :typeObjet(type), id_objet(id), taille(t), mvt(m){};
    Objet(const Objet &copie)=default;
    virtual ~Objet()=default;

    Objet& operator=(const Objet &obj);
};


class Piece : public Objet
{ //passe() jamais 1
    private:
    //-----------attributs------------------
    int valeur;

    //-----------methodes-------------------
    public:
    int getValeur(){return valeur;};
    Piece(int type, int id, int m, int val)//constructeur "complet"
        :Objet(type, id, 1,m), valeur(val){};
    //constructeurs/destructeurs
    Piece(int const id_objet, int const mvt);//constructeur "auto"
    Piece(const Piece &copie)
        :Piece(copie.typeObjet, copie.id_objet,copie.mvt, copie.valeur){};

    ~Piece()=default;
};

class Obstacle : public Objet
{   //passe() jamais null
    private:
    //------------attributs-----------------
    //id_text 0: trous à gauche , 1 trou au milieu, 2 trou à droite 
    int gravite;//0 a une autre chance , 1 meurt direct
    Obstacle(int type, int id, int t, int m, int grav)//constructeur "complet"
        :Objet(type, id, t,m), gravite(grav){};
    //------------methodes------------------
    public:
    int getGravite(){return gravite;};
    //constructeurs/destructeurs

    Obstacle(int const t);
    Obstacle(const Obstacle &copie)=default;

    ~Obstacle()=default;
};

#endif