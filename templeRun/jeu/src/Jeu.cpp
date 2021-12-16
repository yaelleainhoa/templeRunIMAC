#include"../include/Jeu.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <glimac/FilePath.hpp>


//----------methode partie-------------------
//REGARDER cheminVisible & comment on crée les fichiers de sauvegardes ?

int Partie::sauvegarder() const{
	std::string filename= "/home/lisa/Documents/S3/templeRunIMAC/templeRun/jeu/saves/" + nomPartie+".txt";

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

void supprimer(std::string nomPartie)
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

void Jeu::ajouteMeilleurePartie(Partie const newPartie)
{
	int size =meilleuresParties.size();
	if(size==0)//si la liste est vide on ajoute direct le score de la nouvelle partie
	{
		meilleuresParties.push_back(newPartie);
	}
	else{
		//on vérifie si on a pas deja enregistrer un meilleur score pour cette partie
		if(!any_of(meilleuresParties.begin(), meilleuresParties.end(), 
			[&](const auto & x){return (x.getName()==newPartie.getName() || x.getScore()==newPartie.getScore());}))
		{
				//Ajout ou non à aux meilleures parties 
				for(size_t i=0; i<size; i++)
				{
					if(newPartie.getScore() > meilleuresParties[i].getScore())
					//on insert la nouvelle partie
					{
						std::cout << newPartie.getScore()<< " --" <<  meilleuresParties[i].getScore() << std::endl;
						std::vector<Partie>::iterator pos = meilleuresParties.begin();
						meilleuresParties.insert(pos+i, newPartie);
						i=size;
					}
				}
			//5 meilleurs scores max
			if(size>5)
			{
				meilleuresParties.pop_back();
			}
		}
	}
}

void Jeu::ajoutePartieSauvergardee(Partie const newPartie)
{
	//Ajout à la liste des parties sauvegardées

	//on verifie si il existe deja une sauvegarde pour ce nom de partie -> si oui on l'écrase 
	if(!any_of(partiesSauvegardees.begin(), 
				partiesSauvegardees.end(), 
				[&](const auto & x){return x.getName()==newPartie.getName();}))
	{	
		partiesSauvegardees.push_back(newPartie.getName());//rem: si une partie avec ce nom existe deja on modifie pas le vecteur 
	}
	newPartie.sauvegarder();//si la partie existait elle sera ecraser àn l'appelle de la fonction sauvegarder()

	//on verifie qu'on a pas dépassé le nombre de partie sauvegardées autorisé (5)
	if(partiesSauvegardees.size()>5)
	{	
		partiesSauvegardees.pop_front();//supprime la premiere partie (la plus ancienne)
		supprimer(partiesSauvegardees.front().getName());//on supprime la sauvegarde aussi 
	}
}

//---------------aides aux test----------------- 
void Jeu::displayPartiesSauvegardrees() const
{
	for(int i=0; i<partiesSauvegardees.size(); i++)
	{
		std::cout << partiesSauvegardees[i].getName()<<std::endl;
	}
}

void Jeu::displayMeilleuresParties() const
{
	for(int i=0; i<=meilleuresParties.size(); i++)
	{
		std::cout << meilleuresParties[i].getName() <<" -> "<<meilleuresParties[i].getScore() <<std::endl;
	}
}





