#include"./../includes/Jeu.hpp"
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

//----------methode partie-------------------
//REGARDER cheminVisible & comment on crée les fichiers de sauvegardes ?

int Partie::sauvegarder(const std::string &filename) const{
	//open the file
	std::ofstream myfile;
	myfile.open(filename, std::ios::out | std::ios::binary);
	
    if(!myfile.is_open()){
        std::cerr << "error: can not create file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

	//écrit les paramètres de la partie
    
    myfile << nomPartie <<  score<< distance << etat<< &cheminVisible<<std::endl;
	myfile.close();

	return EXIT_SUCCESS;
}


int Partie::load(const std::string &filename){

	//open the file
	std::ifstream myfile;
	myfile.open(filename, std::ios::in | std::ios::binary);
    if(!myfile.is_open()){
        std::cerr << "error: can not open file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

	// lecture des parametres de la partie
	myfile >> nomPartie >> score >> distance >> etat >> &cheminVisible;

	// close file
	myfile.close();
	return EXIT_SUCCESS;
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

Jeu::Jeu(std::vector<std::string> parties , int initScore=0 )
{
	for(int i=0; i<parties.size(); i++)
	{
		ajoutePartieSauvergardee(parties[i]);
	}
	meilleurScore=initScore;
}
