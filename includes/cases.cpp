#include "cases.hpp"

//------classe ssCase------------------------------------------------

//recupere le vecteur des objets de la sous case
std::vector<Objet::Objet> ssCase::getObjet() const
{
    return objets;
}

//ajoute un objet à la sous case
void ssCase::setObjet(Objet::Objet const newObjet)
{
    objets.push_back(newObjet);
}


//----------Classe Case---------------------------------------

//ajoute l'objet dans la ou les sous case correspondantes

void Case::ajouterObjet(Objet::Objet objet, int const position1, int const position2)
{
    if(objet.getTaille()==3)
    {
        ssCaseGauche.setObjet(objet);
        ssCaseMilieu.setObjet(objet);
        ssCaseDroite.setObjet(objet);
    }
    if(objet.getTaille()==2)
    {
        if((position1==0) || (position1==1 && position2==0))
        {
            ssCaseGauche.setObjet(objet);
            ssCaseMilieu.setObjet(objet);
        }
        if((position1==2) || (position1==1 && position2==2))
        {
            ssCaseMilieu.setObjet(objet);
            ssCaseDroite.setObjet(objet);
        }
    }
    else
    {
        if(position1==0)
        {
            ssCaseGauche.setObjet(objet);
        }
        if(position1==1)
        {
            ssCaseMilieu.setObjet(objet);
        }
        else{
            ssCaseDroite.setObjet(objet);
        }
    }
}


Case::Case()
{
    ssCaseGauche=ssCase(0);
    ssCaseMilieu=ssCase(1);
    ssCaseDroite=ssCase(2);
}
        //ATTENTION PB SUR CELLE LA JSP POURQUOI !