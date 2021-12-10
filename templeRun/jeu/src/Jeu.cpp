#include"../include/Jeu.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


//----------methode partie-------------------
//REGARDER cheminVisible & comment on crée les fichiers de sauvegardes ?

int Partie::sauvegarder() const{
	std::string filename= "/home/lisa/Documents/S3/templeRunIMAC/templeRun/jeu/saves/" + nomPartie+".txt";

	std::cout<<"save\n"<<filename<<std::endl;

	//vide le fichier au cas ou il y a deja une sauvegarde pour ce nom de partie
	std::remove(filename.c_str());	
	//open the file
	std::ofstream myfile;
	myfile.open(filename);
	
    if(!myfile.is_open()){
        std::cerr << "error: can not create file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

	//écrit les paramètres de la partie
    myfile << score<<std::endl;
	myfile<< distance<<std::endl;
	myfile << etat<<std::endl;
	myfile<< cheminVisible<<std::endl;

	myfile.close();

	return EXIT_SUCCESS;
}

void Partie::supprimer()
{
	std::string filename= "/home/lisa/Documents/S3/templeRunIMAC/templeRun/jeu/saves/" + nomPartie+".txt";
	std::cout<<filename<<std::endl;

	//vide le fichier au cas ou il y a deja une sauvegarde pour ce nom de partie
	std::remove(filename.c_str());
}


Partie charger(std::string nomPartie){

	std::string filename= "/home/lisa/Documents/S3/templeRunIMAC/templeRun/jeu/saves/" + nomPartie+".txt";
	//open the file
	std::ifstream myfile;

	myfile.open(filename);
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
	if(!any_of(partiesSauvegardees.begin(), partiesSauvegardees.end(), [&](const auto & x){return x==newPartie.getName();}))
	{	
		partiesSauvegardees.push_back(newPartie.getName());
	}
	newPartie.sauvegarder(); 
}


