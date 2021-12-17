#include"../include/Jeu.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <glimac/FilePath.hpp>

//------------méthode jeu--------------------

Jeu::Jeu(std::deque<Partie> parties , int initScore=0 )
{
	std::vector<Partie> meilleuresParties;
	meilleuresParties.clear();
	for(int i=0; i<parties.size(); i++)
	{
		ajoutePartieSauvergardee(parties[i]);
		if(i<5)
		{
			ajouteMeilleurePartie(parties[i]);
		}
	}
}


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
	//on garde le nombre de case (ou on le passe en variable globale vu qu'il changera pas )
	myfile << cheminVisible.size()<<std::endl;
	for(size_t i =0; i< cheminVisible.size(); i++)
	{
		//1) texture de la case
		myfile<< cheminVisible[i].getText()<<std::endl;
		//ecriture des paramètres des objets pour chaque sous case ( 2 lignes par ssCase)
		//----------objets ssCase gauche
		std::vector<Objet> objets = cheminVisible[i].ssCaseGauche.getObjet();
		for(int j=0; j<objets.size(); j++)
		{	//2) Type Objet (0 ou 1) ---- 3) idObjet (ie id de la texture dans le tableau correspondant au type d'objet) 
			myfile << objets[j].getTypeObjet() << " "<< objets[j].getIdObjet() << " " << objets[i].getMvt()<< std::endl;
		}
		if(objets.size()<2)//si on a pas 2 objets on complete avec des lignes de -1 ( à la lecture on "ignorera ces lignes")
		{
			for(int k=0; k<2-objets.size(); k++){myfile << -1 << std::endl;}
		}

		//----------objets ssCase milieu
		std::vector<Objet> objets = cheminVisible[i].ssCaseMilieu.getObjet();
		for(int j=0; j<objets.size(); j++)
		{	//2) Type Objet (0 ou 1) ---- 3) idObjet (ie id de la texture dans le tableau correspondant au type d'objet) 
			myfile << objets[j].getTypeObjet() << " "<< objets[j].getIdObjet()<<" " << objets[i].getMvt()<< std::endl;
		}
		if(objets.size()<2)//si on a pas 2 objets on complete avec des lignes de -1 ( à la lecture on "ignorera ces lignes")
		{
			for(int k=0; k<2-objets.size(); k++){myfile << -1 << std::endl;}
		}

		//----------objets ssCase droite
		std::vector<Objet> objets = cheminVisible[i].ssCaseDroite.getObjet();
		for(int j=0; j<objets.size(); j++)
		{	//2) Type Objet (0 ou 1) ---- 3) idObjet (ie id de la texture dans le tableau correspondant au type d'objet) 
			myfile << objets[j].getTypeObjet() << " "<< objets[j].getIdObjet()<<" " << objets[i].getMvt()<< std::endl;
		}
		if(objets.size()<2)//si on a pas 2 objets on complete avec des lignes de -1 ( à la lecture on "ignorera ces lignes")
		{
			for(int k=0; k<2-objets.size(); k++){myfile << -1 << std::endl;}
		}
	} 
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
	int nbCases;

	myfile 	>>score 
			>> distance 
			>> etat ;

	myfile >> nbCases;
	std::vector<Case> cheminVisible;
	//chargement du chemin visible
	for(int i=0; i<nbCases; i++)
	{
		int indText;
		std::vector<Objet> objG, objM, objD ;
		myfile >> indText; //indice de la texture de la case
		//2 premieres lignes pour la ssCase de gauche
		for(int l=0; l<2; l++)
		{
			int type, id , mvt;
			myfile >> type ;
			if(type==0)
			{	myfile >> id >> mvt;
				Piece objet(id, mvt);
				objG.push_back(objet);
			}
			if(type==1)
			{	myfile >> id >> mvt;
				Obstacle objet(id);
				objG.push_back(objet);
			}
			else //type ==-1 i.e il n'y a pas plus d'objet
			{l=2;}
		}

				//2 lignes pour la ssCase du milieu
		for(int l=0; l<2; l++)
		{
			int type, id , mvt;
			myfile >> type ;
			if(type==0)
			{	myfile >> id >> mvt;
				Piece objet(id, mvt);
				objM.push_back(objet);
			}
			if(type==1)
			{	myfile >> id >> mvt;
				Obstacle objet(id);
				objM.push_back(objet);
			}
			else //type ==-1 i.e il n'y a pas plus d'objet
			{l=2;}
		}

				//2 dernieres lignes pour la ssCase de droite
		for(int l=0; l<2; l++)
		{
			int type, id , mvt;
			myfile >> type ;
			if(type==0)
			{	myfile >> id >> mvt;
				Piece objet(id, mvt);
				objD.push_back(objet);
			}
			if(type==1)
			{	myfile >> id >> mvt;
				Obstacle objet(id);
				objD.push_back(objet);
			}
			//si type=-1 alors ça veut dire que c'est le dernier objet -> on passe à la ligne d'après
		}
		Case case_i(indText,objG,objM,objD);
		cheminVisible.push_back(case_i);
	}
	
	Partie partieLoad(nomPartie,cheminVisible, score, distance, etat);
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
		partiesSauvegardees.push_back(newPartie);//rem: si une partie avec ce nom existe deja on modifie pas le vecteur 
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





