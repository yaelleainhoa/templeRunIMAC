#ifndef CASES_HPP

#define CASES_HPP
#include "objets.hpp"
#include <vector>

class ssCase
{
    private:
    //---------attributs----------------------------
	std::vector<Objet> objets ; //init = null (piece ou obstacle)
	int positionLat ; //(ne sert à rien ?)

    public:
    //----------méthodes-----------------------------
    std::vector<Objet> getObjet() const {return objets;};
    void AjouteObjet(Objet const newObjet);

    //constructeurs/destructeurs:
    ssCase(int const pos , std::vector<Objet> obj=std::vector<Objet>())
        :positionLat(pos), objets(obj){};
    ssCase(const ssCase &copie)
        : objets(copie.objets), positionLat(copie.positionLat){};
    
    ~ssCase()=default;
};

class Case 
{
    private:
    //------------------attributs-------------------------------
	ssCase ssCaseGauche ;
	ssCase ssCaseMilieu ;
	ssCase ssCaseDroite ;

    //--------------------méthodes------------------------------
    void ajouterObjet(Objet const objet, int const position1=0, int const position2=0);
        //position2 pour le cas des objets de tailles 2 qd
    public:

    //A REVOIR !!!    
    //constructeurs/destructeurs:
    Case(std::vector<Objet> objG=std::vector<Objet>(),std::vector<Objet> objC=std::vector<Objet>(),std::vector<Objet> objD=std::vector<Objet>())
        : ssCaseGauche(0, objG),ssCaseMilieu(1, objC),ssCaseDroite(2, objD){};
    Case(const Case &copie)
        : ssCaseGauche(copie.ssCaseGauche), ssCaseMilieu(copie.ssCaseMilieu), ssCaseDroite(copie.ssCaseDroite){};
    
    ~Case()=default;
};

#endif
