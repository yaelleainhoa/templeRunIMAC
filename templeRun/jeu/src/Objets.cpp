#include "../include/Objets.hpp"

//---------méthodes classe "Objet"--------------
bool Objet::passe(Joueur joueur)
{
    return (joueur.getPositionVerticale()==getMvt());
}

Objet& Objet::operator=(const Objet &obj)
{
    if(this!=&obj)
    {
        Objet objet(obj);
        return objet;
    }
    else {return *this;}

}

bool Objet::operator==(const Objet &obj)
{
    return(typeObjet==obj.typeObjet && id_objet==obj.id_objet && mvt==obj.mvt);
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
    :Obstacle(1,id,1,1,1)//trou
{
    if(id==3)//tancarville
    {   
        taille=3;
        mvt=-1;
        gravite=0;
    }
    if(id==4)//velo
    {
        gravite=0;
    }
}


