#include <includes/Jeu.hpp>
/*#include <includes/Objets.hpp>
#include <includes/Personnage.hpp>
#include <includes/Cases.hpp>*/
#include <vector>
#include <iostream>



int main()
{

    //--------------tests Jeu.hpp
    Partie partie1(partie1);
    std::vector<Partie> parties;
    parties.push_back(partie1);

    Jeu jeu(parties);
    Partie partie2(partie2);
    jeu.ajoutePartieSauvergardee(partie2);
    partie2.incrementeScore(2);
    jeu.setMeilleurScore(partie2.getScore());

    std::cout<<jeu.getMeilleurScore()<<std::endl;

    //test methodes parties
    

}