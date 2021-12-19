#include "include/Jeu.hpp"
#include "include/Objets.hpp"
#include "include/Personnage.hpp"
#include "include/Cases.hpp"
#include <vector>
#include <deque>
#include <iostream>
#include <fstream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>


int main()
{

    //--------------tests Jeu------------------------
    Objet objet1(0,0,1,0);
    std::vector<Objet> objets;
    objets.push_back(objet1);
    Case case1(1,objets,objets,objets);
    std::vector<Case> parcoursTest;
    parcoursTest.push_back(case1);
    Partie partie1("partie1", parcoursTest);

    partie1.incrementeDistance(50);
    partie1.incrementeScore(10);
    partie1.setEtat(1);
    std::cout <<"etat (1): "<<partie1.getEtat()<<std::endl;
    std::cout <<"score(10): "<<partie1.getScore()<<std::endl;
    

    std::deque<Partie> parties;
    Jeu jeu(parties);
    Partie partie2("bob",partie1);
    std::cout <<"name partie 2 : "<<partie2.getName()<< std::endl;
    jeu.ajoutePartieSauvergardee(partie1);
    jeu.ajoutePartieSauvergardee(partie2);
/*
   Partie partiLoad(charger("partie1"));
    std::cout <<"load: \n nom:"<< partiLoad.getName()<<
                "\ndistance: " << partiLoad.getDistance()<<
                "\netat: " << partiLoad.getEtat()<<
                "\nscore: "<< partiLoad.getScore()<<std::endl;

    */
    partie2.incrementeScore(40);
    Partie partie3("partie3", parcoursTest);
    partie3.incrementeScore(56);

    jeu.ajoutePartieSauvergardee(partie2);
    jeu.ajoutePartieSauvergardee(partie3);
    std::cout<<"nb partie sauvegardé (3): "<<jeu.nbPartiesSauvegardees()<<std::endl;
    jeu.displayPartiesSauvegardrees();

    jeu.ajouteMeilleurePartie(partie1);
    partie1.sauvegarder();

    jeu.ajouteMeilleurePartie(partie2);
        partie2.sauvegarder();

    jeu.ajouteMeilleurePartie(partie3);
        partie3.sauvegarder();

    std::cout << "meilleures parties : \n" << "nb : "<< jeu.getListeMeilleuresParties().size()<<std::endl;
    jeu.displayMeilleuresParties();

    std::cout << "--------------------test Cases --------------------------------------\n";

    Objet obj(1,2);

    std::cout<<"mouvement : "<< obj.getMvt() << "\ntaille: " << obj.getTaille()<<std::endl;

    Piece piece1(3,0);
    std::cout<<"mouvement : "<< piece1.getMvt() << "\ntaille: " << piece1.getTaille()<< "\nvaleur: " << piece1.getValeur()<<std::endl;

    Piece pieceCopie(piece1);
    std::cout<<"mouvement : "<< pieceCopie.getMvt() << "\ntaille: " << pieceCopie.getTaille()<< "\nvaleur: " << pieceCopie.getValeur()<<std::endl;

    Obstacle trou(0);
    std::cout<<"mouvement trou : "<< trou.getMvt() << "\ntaille trou: " << trou.getTaille()<< "\n gravité trou: " << trou.getGravite()<<std::endl;



    std::cout << "--------------------test Perso -----------------------------------\n";
    Joueur joueur1(1,1);
    std::cout<<"position vert :"  << joueur1.getPositionVerticale() 
            << "\nposition horizontale :"  << joueur1.getPositionHorizontale()  <<std::endl;

    joueur1.glissade();
    std::cout<<"glissade"<<std::endl;
    std::cout<<"position vert :"  << joueur1.getPositionVerticale() 
            << "\nposition horizontale :"  << joueur1.getPositionHorizontale()  <<std::endl;


    joueur1.mvtDroite();
    std::cout<<"mvtDroit"<<std::endl;
    std::cout<<"position vert :"  << joueur1.getPositionVerticale() 
            << "\nposition horizontale :"  << joueur1.getPositionHorizontale()  <<std::endl;

    
    joueur1.mvtDroite();
    std::cout<<"mvtDroit"<<std::endl;
    std::cout<<"position vert :"  << joueur1.getPositionVerticale() 
            << "\nposition horizontale :"  << joueur1.getPositionHorizontale()  <<std::endl;

std::cout << "--------------------test Singe-----------------------------------\n";
Singes sin(1);
    std::cout<<"singes"<<std::endl;
    std::cout<<"distance :"  << sin.getDistancePerso() <<std::endl;


}