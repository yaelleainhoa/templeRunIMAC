#include "include/Jeu.hpp"
/*#include "include/Objets.hpp"
#include "include/Personnage.hpp"
#include "include/Cases.hpp"*/
#include <vector>
#include <iostream>
#include <fstream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>


int main()
{

    //--------------tests Jeu------------------------
    Partie partie1("partie1");
    std::vector<std::string> parties;
    parties.push_back("partie1");
    partie1.incrementeDistance(50);
    partie1.incrementeScore(10);
    std::cout <<"partie1"<<std::endl
        <<"distance partie1 (50): "<<partie1.getDistance()<< "\n" 
        << partie1.getName()<<std::endl;
    partie1.setEtat(1);
    std::cout <<"etat (1): "<<partie1.getEtat()<<std::endl;
    std::cout <<"score(10): "<<partie1.getScore()<<std::endl;
    
   partie1.sauvegarder();

   Partie partiLoad(charger("partie1"));
    std::cout <<"load: \n nom:"<< partiLoad.getName()<<
                "\ndistance: " << partiLoad.getDistance()<<
                "\netat: " << partiLoad.getEtat()<<
                "\nscore: "<< partiLoad.getScore()<<std::endl;
//   partie1.supprimer();

/*
    Jeu jeu(parties);
    Partie partie2(partie1);
    jeu.ajoutePartieSauvergardee(partie2);
    
    partie2.incrementeScore(2);
    jeu.setMeilleurScore(partie2.getScore());

    std::cout<<"meilleur score (2): "<<jeu.getMeilleurScore()<<std::endl;

    //test methodes parties

*/
}