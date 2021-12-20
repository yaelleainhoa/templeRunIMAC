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
Piece::Piece(int const t, int const mvt)
{
    if (t==0)
    {
        Piece(0,t,mvt, 10);//Objet(int type=0, int id=0,int const t=1, int m=0) 
    }
    if (t==1)
    {
        Piece(0,t,mvt, 20);
    }
    if (t==2)
    {
        Piece(0,t,mvt,50);
    }
}

//---------Méthodes sous classe "obstacle"--------------
Obstacle::Obstacle(int const t)
{
    if (t==0 ||  t==1 || t==2 )//trous
        {Obstacle(1,t,1,1,1);}//Objet(int type=0, int id=0,int const t=1, int m=0)
    if(t==2)
        {Obstacle(1,t,2,0,0);}
    if(t==3)
        {Obstacle(1,t,1,2,0);}
    else
        {Obstacle(1,t,1,3,0);}//exemple 
};