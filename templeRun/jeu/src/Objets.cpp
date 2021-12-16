#include "../include/Objets.hpp"

//---------méthodes classe "Objet"--------------
bool Objet::passe(Joueur joueur)
{
    return joueur.getPositionVerticale()==getMvt();
}

//---------Méthodes sous classe "Piece"--------------
Piece::Piece(int const t, int const mvt)
{
    typeObjet=0;//l'objet est une piece
    id_objet =t;//type de piece 
    if (t==0)
    {
        valeur=10;
        Objet(1,mvt);
    }
    if (t==1)
    {
        valeur=20;
        Objet(1,mvt);
    }
    if (t==2)
    {
        valeur=50;
        Objet(1,mvt);
    }
}

//---------Méthodes sous classe "obstacle"--------------
Obstacle::Obstacle(int const t)
{
    typeObjet=1;//l'objet est un obstacle
    id_objet =t;//type d(obstacle)
    if (t==0 ||  t==1 || t==2 )//trous
    {
        gravite=1;//mort direct
        {Objet(1,1);}
    }
    if  (t==3 || t==4 || t==5)//changer les autres test en fonction des textures
    {
        gravite=0;
        if(t==2)
            {Objet(2,0);}
        if(t==3)
            {Objet(1,2);}
        else
            {Objet(1,3);}//exemple
    }   
};