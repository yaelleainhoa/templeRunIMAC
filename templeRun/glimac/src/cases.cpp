#include "glimac/cases.hpp"

//------classe ssCase------------------------------------------------

//ajoute un objet à la sous case
void ssCase::AjouteObjet(Objet const newObjet)
{
    objets.push_back(newObjet);
}

//----------Classe Case---------------------------------------

//ajoute l'objet dans la ou les sous case correspondantes

void Case::ajouterObjet(Objet objet, int const position1, int const position2)
{
    if(objet.getTaille()==3)
    {
        ssCaseGauche.AjouteObjet(objet);
        ssCaseMilieu.AjouteObjet(objet);
        ssCaseDroite.AjouteObjet(objet);
    }
    if(objet.getTaille()==2)
    {
        if((position1==0) || (position1==1 && position2==0))
        {
            ssCaseGauche.AjouteObjet(objet);
            ssCaseMilieu.AjouteObjet(objet);
        }
        if((position1==2) || (position1==1 && position2==2))
        {
            ssCaseMilieu.AjouteObjet(objet);
            ssCaseDroite.AjouteObjet(objet);
        }
    }
    else
    {
        if(position1==0)
        {
            ssCaseGauche.AjouteObjet(objet);
        }
        if(position1==1)
        {
            ssCaseMilieu.AjouteObjet(objet);
        }
        else{
            ssCaseDroite.AjouteObjet(objet);
        }
    }
}
