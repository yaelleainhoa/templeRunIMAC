#include "../include/Cases.hpp"
#include "../include/Objets.hpp"

//------classe ssCase------------------------------------------------

//ajoute un objet à la sous case
void ssCase::AjouteObjetSsCase(Objet const newObjet)
{
    objets.push_back(newObjet);
}

//----------Classe Case---------------------------------------

//ajoute l'objet dans la ou les sous case correspondantes

void Case::ajouterObjetCase(Objet objet, int const position1, int const position2)
{
    if(objet.getTaille()==3)
    {
        ssCaseGauche.AjouteObjetSsCase(objet);
        ssCaseMilieu.AjouteObjetSsCase(objet);
        ssCaseDroite.AjouteObjetSsCase(objet);
    }
    if(objet.getTaille()==2)
    {
        if((position1==0) || (position1==1 && position2==0))
        {
            ssCaseGauche.AjouteObjetSsCase(objet);
            ssCaseMilieu.AjouteObjetSsCase(objet);
        }
        if((position1==2) || (position1==1 && position2==2))
        {
            ssCaseMilieu.AjouteObjetSsCase(objet);
            ssCaseDroite.AjouteObjetSsCase(objet);
        }
    }
    else
    {
        if(position1==0)
        {
            ssCaseGauche.AjouteObjetSsCase(objet);
        }
        if(position1==1)
        {
            ssCaseMilieu.AjouteObjetSsCase(objet);
        }
        else{
            ssCaseDroite.AjouteObjetSsCase(objet);
        }
    }
}
