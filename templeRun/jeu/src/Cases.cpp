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
        if((position1==-1) || (position1==0 && position2==-1))
        {
            ssCaseGauche.AjouteObjetSsCase(objet);
            ssCaseMilieu.AjouteObjetSsCase(objet);
        }
        if((position1==1) || (position1==0 && position2==1))
        {
            ssCaseMilieu.AjouteObjetSsCase(objet);
            ssCaseDroite.AjouteObjetSsCase(objet);
        }
    }
    else//objet de taille 1
    {
        if(position1==-1)
        {
            ssCaseGauche.AjouteObjetSsCase(objet);
        }
        if(position1==0)
        {
            ssCaseMilieu.AjouteObjetSsCase(objet);
        }
        else{
            ssCaseDroite.AjouteObjetSsCase(objet);
        }
    }
}

void Case::setText(int const text)
{
    indText=text;
    //Au cas ou on ajoute la texture de case correspondante à un trou on ajoute un obstacle correspondant dans la case ( pour les test)
    if(text==1)//trou gauche
    {
        Obstacle trouG(0);//0 est l'id_objet du trou à gauche
        ajouterObjetCase(trouG, -1);
    }
    if(text==2)//trou milieu
    {       
        Obstacle trouM(1);//1 est l'id_objet du trou au milieu
        ajouterObjetCase(trouM, 0);
    }
    if(text==3)//trou droite
    {
        Obstacle trouD(2);//2 est l'id_objet du trou à droite
        ajouterObjetCase(trouD, 1);
    }
}