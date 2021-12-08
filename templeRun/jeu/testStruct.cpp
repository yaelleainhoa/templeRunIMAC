#include "include/Jeu.hpp"
/*#include "include/Objets.hpp"
#include "include/Personnage.hpp"
#include "include/Cases.hpp"*/
#include <vector>
#include <iostream>
#include <fstream>


int main()
{

    //--------------tests Jeu------------------------
    Partie partie1("partie1");
    std::vector<std::string> parties;
    parties.push_back("partie1");

    Jeu jeu(parties);
    Partie partie2(partie1);
    jeu.ajoutePartieSauvergardee(partie2);
    partie2.incrementeScore(2);
    jeu.setMeilleurScore(partie2.getScore());

    std::cout<<"meilleur score (2): "<<jeu.getMeilleurScore()<<std::endl;

    //test methodes parties
    partie1.incrementeDistance(50);
    std::cout <<"distance partie1 (50): "<<partie1.getDistance()<< " " << partie1.getName()<<std::endl;
    partie1.setEtat(1);
    std::cout <<"etat (1): "<<partie1.getEtat()<<std::endl;
    
    partie1.sauvegarder();
    Partie partiLoad(load(partie1));
    std::cout <<"load: \n nom:"<< partiLoad.getName()<<
                "\ndistance: " << partiLoad.getDistance()<<
                "\netat: " << partiLoad.getEtat()<<
                "\nscore: "<< partiLoad.getScore()<<std::cout;


}