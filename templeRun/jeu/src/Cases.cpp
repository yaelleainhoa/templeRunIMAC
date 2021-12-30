#include "../include/Cases.hpp"
#include "../include/Objets.hpp"
#include <iostream>

//------classe ssCase------------------------------------------------

//ajoute un objet à la sous case
void ssCase::AjouteObjetSsCase(Objet const &newObjet)
{
    if(objets.empty())
    {
        objets.push_back(newObjet);
    }
    else if (objets.size()==1 && !(objets[0]==newObjet))//on verifie que l'objet n'est pas déjà ajouté
    {
       objets.push_back(newObjet);
    }
    
    else
    {
        std::cerr << "[ERROR]:trop d'objets dans la case ou l'objet est deja present (l'objet ne sera pas ajouté)" <<std::endl;
    }
}

//----------Classe Case---------------------------------------

//ajoute l'objet dans la ou les sous case correspondantes

void Case::ajouterObjetCase(Objet const &objet, int const position1, int const position2)
{
    if(objet.getTaille()==3)
    {
        ssCaseGauche.AjouteObjetSsCase(objet);
        ssCaseMilieu.AjouteObjetSsCase(objet);
        ssCaseDroite.AjouteObjetSsCase(objet);
    }
    else if(objet.getTaille()==2)
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
        else if(position1==0)
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
    Obstacle trou(0);//0 est l'id_objet du trou
    //Au cas ou on ajoute la texture de case correspondante à un trou on ajoute un obstacle correspondant dans la case ( pour les test)
    if(text==1)//trou gauche
        {ajouterObjetCase(trou, -1);}
    if(text==2)//trou milieu
        {ajouterObjetCase(trou, 0);}
    if(text==3)//trou droite
        {ajouterObjetCase(trou, 1);}
}