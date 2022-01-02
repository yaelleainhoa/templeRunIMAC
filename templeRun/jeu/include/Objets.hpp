#ifndef OBJETS_HPP

#define OBJETS_HPP

#include "Personnage.hpp"

class Objet
{
    //---------------attributs---------------------
    protected:
    int taille; // 1 ou 3 (instancié grace au type d'objet (1 si pièce))
    int mvt; // {-1,0,1} mvt pour survivre ou récupérer la pièce
    int const typeObjet;//piece =0 ou obstacle=1
    int const id_objet;//id de la texture correspondant à l'objet 
                 //(dans le tableau des textures de piece ou d'obstacle selon le type)
    int attrape=0;//permet de savoir si l'objet à été touché 

    public:
    //---------------méthodes------------------------
    bool passe(Joueur joueur) ;
    inline int getMvt() const {return mvt;};
    inline int getTaille() const {return taille;};
    inline int getTypeObjet() const {return typeObjet;};
    inline int getIdObjet() const {return id_objet;};
    inline bool estPiece(){return typeObjet==0;};//fct débile mais plus claire à l'utilisation
    inline bool estObstacle(){return typeObjet==1;};//elle aussi
    inline void attrapeObjet(){attrape=1;};
    inline int estAttrape(){return attrape;};

    //constructeurs/destructeurs
    Objet(int type, int id,int const t, int m)
        :typeObjet(type), id_objet(id), taille(t), mvt(m){};
    Objet(const Objet &copie)=default;
    virtual ~Objet()=default;

    //surcharge d'opérateurs
    Objet& operator=(const Objet &obj);
    bool operator==(const Objet &obj);
};


class Piece : public Objet
{
    //-----------attributs------------------
    private:
    int valeur;

    //-----------methodes-------------------
    public:
    int getValeur(){return valeur;};

    //constructeurs/destructeurs
    Piece(int type, int id, int m, int val)//constructeur "complet"
        :Objet(type, id, 1,m), valeur(val){};
    Piece(int const id_objet, int const mvt);//constructeur "auto"
    Piece(const Piece &copie)
        :Piece(copie.typeObjet, copie.id_objet,copie.mvt, copie.valeur){};

    ~Piece()=default;
};

class Obstacle : public Objet
{   
    private:
    //------------attributs-----------------
    int gravite;//0 a une autre chance , 1 meurt direct
    //------------methodes------------------
    public:
    int getGravite(){return gravite;};

    //constructeurs/destructeurs
    Obstacle(int type, int id, int t, int m, int grav)//constructeur "complet"
        :Objet(type, id, t,m), gravite(grav){};
    Obstacle(int const t);//"auto"
    Obstacle(const Obstacle &copie)=default;

    ~Obstacle()=default;
};

#endif