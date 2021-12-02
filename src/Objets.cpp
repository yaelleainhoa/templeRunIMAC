#include "./../includes/Objets.hpp"

//---------méthodes classe "Objet"--------------

bool Objet::passe(Joueur joueur)
{
    return joueur.getPositionVerticale()==getMvt();
}


//---------Méthodes sous classe "Piece"--------------

Obstacle::Obstacle(int const t)
{
    type=t;
    if (t==0 || t==1)//changer conditions qd on aura les textures
    {
        gravite=1;
        if(t==0)
            {Objet(1,0);}
        else
            {Objet(1,3);}//exemple
    }
    if  (t==2 || t==3 || t==4)
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