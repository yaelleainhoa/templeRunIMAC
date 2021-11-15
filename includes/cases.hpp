#ifndef CASES_HPP

#define CASES_HPP
#include <objets.hpp>
#include <vector>

class ssCase
{
    private:
    //attributs
	std::vector<Objet> objets ; //init = null (piece ou obstacle)
	int positionLat ; //(ne sert à rien ?)

    public:
    //méthodes
    std::vector<Objet> getObjet() const;
    void setObjet(Objet const newObjet);

    ssCase(int const pos , std::vector<Objet> obj=std::vector<Objet>())
        :positionLat(pos), objets(obj){};
    
    ~ssCase()=default;
};

class Case 
{
    private:
    //attributs
	ssCase ssCaseGauche ;
	ssCase ssCaseMilieu ;
	ssCase ssCaseDroite ;

    //méthodes
    void ajouterObjet(Objet const objet, int const position1=0, int const position2=0);
        //position2 pour le cas des objets de tailles 2 qd
    public:
    Case();
    ~Case()=default;
};

#endif
