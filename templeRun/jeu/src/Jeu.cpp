#include"../include/Jeu.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

//----------methode partie-------------------
//REGARDER cheminVisible & comment on crée les fichiers de sauvegardes ?

int Partie::sauvegarder() const{
	const std::string filename="../saves/"+getName()+".txt";

	//vide le fichier au cas ou il y a deja une sauvegarde pour ce nom de partie
	std::remove(filename.c_str());	
	//open the file
	std::ofstream myfile(filename.c_str());
	myfile.open(filename, std::ios::out | std::ios::binary);
	
    if(!myfile.is_open()){
        std::cerr << "error: can not create file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

	//écrit les paramètres de la partie
    
    myfile << score<< distance << etat<< cheminVisible<<std::endl;
	myfile.close();

	return EXIT_SUCCESS;
}

Partie charger(std::string nomPartie){
	const std::string &filename= "../saves/"+nomPartie+".txt";
	//open the file
	std::ifstream myfile;

	myfile.open(filename, std::ios::in | std::ios::binary);
    if(!myfile.is_open()){
        std::cerr << "error: can not open file: " << filename << std::endl;
        EXIT_FAILURE;
    }

	// lecture des parametres de la partie
	int score;
	int etat;
	int distance;

	myfile 	>>score 
			>> distance 
			>> etat ;//>> partieLoad.cheminVisible;
	Partie partieLoad(nomPartie,score, distance, etat);
//load les parametres des cases visibles 
	// close file
	myfile.close();

	return partieLoad;
	EXIT_SUCCESS;
}

//--------methodes Jeu-------------------------

void Jeu::ajoutePartieSauvergardee(Partie const newPartie)
{
	if(!any_of(partiesSauvegardees.begin(), partiesSauvegardees.end(), [&](const auto & x){return x==newPartie;}))
	{	
		partiesSauvegardees.push_back(newPartie.getName());
	}
	newPartie.sauvegarder(); 
}


