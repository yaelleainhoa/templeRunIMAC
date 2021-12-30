#include "../include/Objets.hpp"

//---------méthodes classe "Objet"--------------
bool Objet::passe(Joueur joueur)
{
    return (joueur.getPositionVerticale()==getMvt());
}

Objet& Objet::operator=(const Objet &obj)
{
    Objet objet(obj);
    return objet;
}

//---------Méthodes sous classe "Piece"--------------

Piece::Piece(int const id, int const mvt)
:Piece(0, id, mvt,10)//Piece(int type, int id, int m, int val)/
{   
    if (id==1)
        {valeur=20;}
    if(id==2)
        {valeur=50;}
}

//---------Méthodes sous classe "obstacle"--------------
Obstacle::Obstacle(int const id)
    :Obstacle(1,id,1,1,0)//trou
{   
    // tancarville
    // if(id==0){
    //     taille = 3;
    //     mvt = -1;
    //     gravite = 1;
    // }
    //velo
    if(id==1)
    {   
        taille=2;
        mvt=1;
        gravite=1;
    }
    // exemple avec la pomme
    if(id==2)
        {mvt=1;
        taille=1;
        gravite=1;}
    if(id==3)
        {mvt=0;
        gravite=1;
        }//exemple 
    if(id==4){
        mvt = 0;
        gravite = 1;
    }    
}