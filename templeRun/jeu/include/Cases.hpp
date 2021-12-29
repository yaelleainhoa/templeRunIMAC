#ifndef CASES_HPP

#define CASES_HPP
#include "Objets.hpp"
#include <vector>

class ssCase//A FAIRE : RENDRE CASE ET SSCASE AMIS -> passer ajoute ObjetSSCase en protected
{
    private:
    //---------attributs----------------------------
	std::vector<Objet> objets ; //max de taille 2 (1 piece, 1 obstacle)
	int positionLat ; //(ne sert à rien ?)

    public:
    //----------méthodes-----------------------------
    std::vector<Objet> getObjet() const {return objets;};
    void AjouteObjetSsCase(Objet const &newObjet);
  
    //constructeurs/destructeurs:
    ssCase(int const pos , std::vector<Objet> obj=std::vector<Objet>())
        :positionLat(pos), objets(obj){};
    ssCase(const ssCase &copie)
        : objets(copie.objets){};
    
    ~ssCase()=default;
};

class Case 
{
    public:
    //------------------attributs-------------------------------
	ssCase ssCaseGauche ;//position laterale : -1
	ssCase ssCaseMilieu ;//position laterale : 0
	ssCase ssCaseDroite ;//position laterale : 1

    private:
    int indText;//ajouter dans set text des obstacles si il y a des trous (constructeur aussi)

    //--------------------méthodes------------------------------
    public:
    int getText() const {return indText;};
    void setText(int const text);
    
    void ajouterObjetCase(Objet const &objet, int const position1=0, int const position2=-1);
        //position2 pour le cas des objets de tailles 2
public:
  
    //constructeurs/destructeurs:
    Case(int text, std::vector<Objet> objG={"",{}},std::vector<Objet> objC={"",{}},std::vector<Objet> objD={"",{}})
        :ssCaseGauche(-1, objG),ssCaseMilieu(0, objC),ssCaseDroite(1, objD){setText(text);};
    Case(const Case &copie)
        : indText(copie.indText), ssCaseGauche(copie.ssCaseGauche), ssCaseMilieu(copie.ssCaseMilieu), ssCaseDroite(copie.ssCaseDroite){};
    
    ~Case()=default;
};

#endif
