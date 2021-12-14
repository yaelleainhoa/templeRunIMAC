#include "../include/Personnage.hpp"


//-------methodes class Joueur--------------
void Joueur::mvtGauche()
{
    if(position_horizontal>-1)
    {  
        position_horizontal--;
    }
}
void Joueur::mvtDroite()
{
    if(position_horizontal<1)
    {  
        position_horizontal++;
    }
}

//--------methodes classe Singes--------------
