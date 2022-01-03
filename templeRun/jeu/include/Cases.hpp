#ifndef CASES_HPP

#define CASES_HPP
#include "Objets.hpp"
#include <vector>
#include <assert.h>

class ssCase
{
    private:
    //---------attributs----------------------------
	std::vector<Objet> objets ; //max de taille 2 (1 piece, 1 obstacle max par case)
	int positionLat ;//plus simple pour les test

    public:
    //----------méthodes-----------------------------
    inline std::vector<Objet> getObjet() const {return objets;};
    inline void attrapeObjetAt(const int i){objets[i].attrapeObjet();};
    void AjouteObjetSsCase(Objet const &newObjet);
  
    //constructeurs/destructeurs:
    //par défaut
    ssCase(int const pos ,std::vector<Objet> obj={"",{}})
        :positionLat(pos), objets(obj){};
    //par recopie
    ssCase(const ssCase &copie)
        : objets(copie.objets){};
    
    ~ssCase()=default;
};

class Case 
{
    public:
    //------------------attributs-------------------------------
	ssCase ssCaseGauche ;//position laterale = -1
	ssCase ssCaseMilieu ;//position laterale = 0
	ssCase ssCaseDroite ;//position laterale = 1

    private:
    int indText;//indice de la texture de la case : 0="normale", 1=trou à gauche, 2=trou au milieu, 3=trou à droite, 4=rotation 

    //--------------------méthodes------------------------------
    public:
    int getText() const {return indText;};
    void setText(int const text);
    
    void ajouterObjetCase(Objet const &objet, int const position1=0, int const position2=-1);
        //position2 pour le cas des objets de tailles 2
public:
  
    //constructeurs/destructeurs:
    Case(int text, std::vector<Objet> objG=std::vector<Objet>(),std::vector<Objet> objC=std::vector<Objet>(),std::vector<Objet> objD=std::vector<Objet>())
        :ssCaseGauche(-1, objG),ssCaseMilieu(0, objC),ssCaseDroite(1, objD){setText(text);};
    Case(const Case &copie)
        : indText(copie.indText), ssCaseGauche(copie.ssCaseGauche), ssCaseMilieu(copie.ssCaseMilieu), ssCaseDroite(copie.ssCaseDroite){};
    
    ~Case()=default;
};

#endif
