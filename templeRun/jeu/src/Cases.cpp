#include "../include/Cases.hpp"
#include "../include/Objets.hpp"
#include <iostream>

//------classe ssCase------------------------------------------------

//ajoute un objet à la sous case
void ssCase::AjouteObjetSsCase(Objet const &newObjet)
{
    if(objets.empty())//si le vecteur d'objet est vide on ajoute directement le newObjet à celui-ci
    {
        objets.push_back(newObjet);
    }
    else if (objets.size()==1 && !(objets[0]==newObjet))//si il y a deja un objet on vérifie que l'objet n'est pas déjà ajouté
    {
       objets.push_back(newObjet);
    }
    else//en  vérité ici on a uniquement le cas size()==2 (ie le vecteur est rempli)
    {
        std::cerr << "[ERROR]:trop d'objets dans la case ou l'objet est deja present (l'objet ne sera pas ajouté)" <<std::endl;
    }
}

//----------Classe Case---------------------------------------

//ajoute l'objet dans la ou les sous case correspondantes
void Case::ajouterObjetCase(Objet const &objet, int const position1, int const position2)
//position2 ne sert que dans le cas precis ou l'objet est de taille 2 et sa position1 est 0
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
    //on verifie que la texture à ajouter est possible
    assert(text<=4 && "error : Les indices de textures doivent etre entre 0 et 4!!\n");
    indText=text;
    
    //Au cas ou on ajoute la texture de case correspondante à un trou on ajoute un obstacle correspondant dans la case ( pour les test)
    if(text==1)//trou gauche
        {Obstacle trou(0);//0 est l'id_objet du trou
        ajouterObjetCase(trou, -1);}
    if(text==2)//trou milieu
        {Obstacle trou(0);
        ajouterObjetCase(trou, 0);}
    if(text==3)//trou droite
        {Obstacle trou(0);
        ajouterObjetCase(trou, 1);}
}