#include "./../includes/Personnage.hpp"


//-------methodes class Joueur--------------
void Joueur::mvtGauche()
{
    if(position_vertical-1>0)
    {  
        position_vertical--;
    }
}
void Joueur::mvtDroite()
{
    if(position_vertical+1<2)
    {  
        position_vertical++;
    }
}

//--------methodes classe Singes--------------
