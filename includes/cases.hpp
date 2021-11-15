#ifndef CASES_HPP

#define CASES_HPP
#include <objets.hpp>

class ssCase
{
    private:
	Objet objet ; //init = null (piece ou obstacle)
	int positionLatérale ; //(ne sert à rien ?)

    public:
    Objet getObjet();
    void setObjet(Objet objet);
    ssCase();
    ~ssCase();
};

class Case 
{
    private:
    //attributs
	ssCase ssCaseGauche ;
	ssCase ssCaseMilieu ;
	ssCase ssCaseDroite ;

    //metodes
    void ajouterObjet(Objet objet, int position);

    Case();
    ~Case();
};

#endif
