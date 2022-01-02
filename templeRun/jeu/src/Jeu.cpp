#include"../include/Jeu.hpp"
Jeu* Jeu::instance = 0;
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <filesystem> 	 	 	
#include <glimac/FilePath.hpp>


//----------methode partie-------------------

int Partie::sauvegarder() const{
	std::filesystem::path p = std::filesystem::current_path();
    std::string cheminRelatif=p.relative_path();
	std::string filename= "/"+cheminRelatif + "/../templeRun/jeu/saves/"+nomPartie+".txt";

	//std::cout<<"save filename: "<< filename<<std::endl;
	//vide le fichier au cas ou il y a deja une sauvegarde pour ce nom de partie
	std::remove(filename.c_str());	
	//open the file
	std::ofstream myfile;
	myfile.open(filename.c_str());
	
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
	myfile << sensRotation << std::endl;
	myfile << numCaseRot << std::endl;
	myfile << casTerrain << std::endl;
	for(size_t i =0; i< cheminVisible.size(); i++)
	{
		//1) texture de la case
		myfile<< cheminVisible[i].getText()<<std::endl;
		//ecriture des paramètres des objets pour chaque sous case ( 2 lignes par ssCase)
		//----------objets ssCase gauche
		std::vector<Objet> objets = cheminVisible[i].ssCaseGauche.getObjet();
		for(int j=0; j<objets.size(); j++)
		{	//2) Type Objet (0 ou 1) ---- 3) idObjet (ie id de la texture dans le tableau correspondant au type d'objet) 
			myfile << objets[j].getTypeObjet() <<" "<< objets[j].getIdObjet() <<" "<<  objets[j].getMvt()<< std::endl;
		}
		if(objets.size()<2)//si on a pas 2 objets on complete avec des lignes de -1 ( à la lecture on "ignorera ces lignes")
		{
			for(int k=0; k<2-objets.size(); k++){myfile << -1 << -1 << -1 << std::endl;}
		}

		//----------objets ssCase milieu
		objets = cheminVisible[i].ssCaseMilieu.getObjet();
		for(int j=0; j<objets.size(); j++)
		{	//2) Type Objet (0 ou 1) ---- 3) idObjet (ie id de la texture dans le tableau correspondant au type d'objet) 
			myfile << objets[j].getTypeObjet() <<" "<< objets[j].getIdObjet()<<" " <<objets[j].getMvt()<< std::endl;
		}
		if(objets.size()<2)//si on a pas 2 objets on complete avec des lignes de -1 ( à la lecture on "ignorera ces lignes")
		{
			for(int k=0; k<2-objets.size(); k++){myfile << -1 << -1 << -1 << std::endl;}
		}

		//----------objets ssCase droite
		objets = cheminVisible[i].ssCaseDroite.getObjet();
		for(int j=0; j<objets.size(); j++)
		{	//2) Type Objet (0 ou 1) ---- 3) idObjet (ie id de la texture dans le tableau correspondant au type d'objet) 
			myfile << objets[j].getTypeObjet() <<" "<< objets[j].getIdObjet()<<" " <<objets[j].getMvt()<< std::endl;
		}
		if(objets.size()<2)//si on a pas 2 objets on complete avec des lignes de -1 ( à la lecture on "ignorera ces lignes")
		{
			for(int k=0; k<2-objets.size(); k++){myfile << -1 << -1 << -1 << std::endl;}
		}
	} 
	myfile.close();
	return EXIT_SUCCESS;
}

void supprimer(std::string nomPartie)
{
	std::filesystem::path p = std::filesystem::current_path();
    std::string cheminRelatif=p.relative_path();
	std::string filename= "/"+cheminRelatif + "/../templeRun/jeu/saves/"+nomPartie+".txt";
	//std::cout <<"suppr file : "<<filename<<std::endl;
	//vide le fichier au cas ou il y a deja une sauvegarde pour ce nom de partie
	std::remove(filename.c_str());
}

Partie charger(std::string nomPartie){
	std::filesystem::path p = std::filesystem::current_path();
    std::string cheminRelatif=p.relative_path();
	std::string filename= "/"+cheminRelatif + "/../templeRun/jeu/saves/"+nomPartie+".txt";
	//open the file
	std::ifstream myfile;

	myfile.open(filename.c_str());
    if(!myfile.is_open()){
        std::cerr << "error: can not open file: " << filename << std::endl << std::endl;
        EXIT_FAILURE;
    }

	// lecture des parametres de la partie
	int score;
	int etat;
	int distance;
	int nbCases;
	int sensRotation;
	int numCaseRot;
	int casTerrain;
	myfile 	>>score;
	myfile >> distance; 
	myfile >> etat ;
	myfile >> nbCases;
	myfile >> sensRotation;
	myfile >> numCaseRot;
	myfile >> casTerrain;
	std::deque<Case> cheminVisible;
	//chargement du chemin visible
	for(int i=0; i<nbCases; i++)
	{
		int indText;
		std::vector<Objet> objG, objM, objD ;
		myfile >> indText; //indice de la texture de la case
		//2 premieres lignes pour la ssCase de gauche
		for(int l=0; l<2; l++)
		{
			int type, id ,mvt;
			myfile >> type >> id >> mvt;
			if(type==0 && id!=0) //id 0 correspond à un trou, qui est déjà ajouté avec la texture!
			{	//myfile >> id >>mvt;
				Piece objet(id, mvt);
				objG.push_back(objet);
			}
			else if(type==1 && id!=0)
			{	//myfile >> id >> mvt;
				Obstacle objet(id);
				objG.push_back(objet);
			}
			// else //type ==-1 i.e il n'y a pas plus d'objet
			// {l=2;}
		}

				//2 lignes pour la ssCase du milieu
		for(int l=0; l<2; l++)
		{
			int type, id , mvt;
			myfile >> type >> id >> mvt;
			if(type==0 && id!=0)
			{	//myfile >> id >> mvt;
				Piece objet(id, mvt);
				objM.push_back(objet);
			}
			else if(type==1 && id!=0)
			{	//myfile >> id >> mvt;
				Obstacle objet(id);
				objM.push_back(objet);
			}
			// else //type ==-1 i.e il n'y a pas plus d'objet
			// {l=2;}
		}

				//2 dernieres lignes pour la ssCase de droite
		for(int l=0; l<2; l++)
		{
			int type, id , mvt;
			myfile >> type >> id >> mvt;
			if(type==0 && id!=0)
			{	//myfile >> id >> mvt;
				Piece objet(id, mvt);
				objD.push_back(objet);
			}
			else if(type==1 && id!=0)
			{	//myfile >> id >> mvt;
				Obstacle objet(id);
				objD.push_back(objet);
			}
			//si type=-1 alors ça veut dire que c'est le dernier objet -> on passe à la ligne d'après
		}
		Case case_i(indText,objG,objM,objD);
		cheminVisible.push_back(case_i);
	}
	
	Partie partieLoad(nomPartie,cheminVisible, score, distance, etat, numCaseRot, sensRotation, casTerrain);
	// close file
	myfile.close();

	return partieLoad;
	EXIT_SUCCESS;
}

//--------methodes Jeu-------------------------

void Jeu::ajouteMeilleurePartie(Partie const &newPartie)
{
	int size =meilleursScores.size();
	std::pair<std::string, int> couplePartie (newPartie.getName(), newPartie.getScore());
	if(size==0)//si la liste est vide on ajoute direct le score de la nouvelle partie
	{
		meilleursScores.push_back(couplePartie);
	}
	else{
		//on vérifie si on a pas deja enregistrer un meilleur score pour cette partie
		if(!any_of(meilleursScores.begin(), meilleursScores.end(), 
			[&](const auto & x){return (x.first==newPartie.getName() || x.second==newPartie.getScore());}))
		{
				//Ajout ou non à aux meilleures parties 
				for(size_t i=0; i<size; i++)
				{
					if(newPartie.getScore() > meilleursScores[i].second)
					//on insert la nouvelle partie
					{
						// std::cout << newPartie.getScore()<< " --" <<  meilleursScores[i].second << std::endl;
						std::vector<std::pair<std::string, int>>::iterator pos = meilleursScores.begin();
						meilleursScores.insert(pos+i, couplePartie);

						i=size;
					}
				}
			//5 meilleurs scores max
			if(size>5)
			{
				meilleursScores.pop_back();
			}
		}
	}
}

void Jeu::ajoutePartieSauvergardee(Partie const &newPartie)
{
	//Ajout à la liste des parties sauvegardées

	//on verifie s'il existe deja une sauvegarde pour ce nom de partie -> si oui on l'écrase 
	if(!any_of(partiesSauvegardees.begin(), 
				partiesSauvegardees.end(), 
				[&](const auto & x){return x.getName()==newPartie.getName();}))
	{	
		//si une partie avec ce nom existe deja, on ne modifie pas le vecteur 
		partiesSauvegardees.push_back(newPartie);
	}
	//si la partie existait elle sera ecrasée à l'appel de la fonction sauvegarder()
	newPartie.sauvegarder();

	//on verifie qu'on n'a pas dépassé le nombre de partie sauvegardées autorisé (5)
	if(partiesSauvegardees.size()>5)
	{	
		std::string partieASupprimer = partiesSauvegardees.front().getName();
		partiesSauvegardees.pop_front();//supprime la premiere partie (la plus ancienne)
		supprimer(partieASupprimer);//on supprime la sauvegarde aussi 
	}
}


int chargerParties(std::string partiesACharger, std::deque <Partie> &partiesSauvegardees){
	std::filesystem::path p = std::filesystem::current_path();
    std::string cheminRelatif=p.relative_path();
	std::string filename= "/"+cheminRelatif + "/../templeRun/jeu/savesJeu/"+partiesACharger+".txt";
	//open the file
	std::ifstream myfile;

	myfile.open(filename.c_str());
    if(!myfile.is_open()){
        std::cerr << "error: can not open file: " << filename << std::endl << std::endl;
        EXIT_FAILURE;
    }

	// lecture des parametres de la partie
	int i=0;
	while(!myfile.eof() && i<5){//for(int i=0;i<5;i++){
		std::string partieACharger;
		myfile >> partieACharger;
		if(partieACharger!=""){
			Partie partie = charger(partieACharger);
			partiesSauvegardees.push_back(partie);
		}
		i++;
	}

	myfile.close();

	return EXIT_SUCCESS;
}
int chargerMeilleuresParties(std::string partiesACharger, std::vector<std::pair<std::string, int>> &meilleursScores){
	std::vector <Partie> parties;
	std::filesystem::path p = std::filesystem::current_path();
    std::string cheminRelatif=p.relative_path();
	std::string filename= "/"+cheminRelatif + "/../templeRun/jeu/savesJeu/"+partiesACharger+".txt";
	//open the file
	std::ifstream myfile;

	myfile.open(filename.c_str());
    if(!myfile.is_open()){
        std::cerr << "error: can not open file: " << filename << std::endl << std::endl;
        EXIT_FAILURE;
    }

	// lecture des parametres de la partie
	int i=0;
	while(!myfile.eof() and i<5){
		std::string nomPartie;
		int score;
		myfile >> nomPartie >> score;
		std::pair<std::string, int> coupleMeilleurScore (nomPartie, score);
		meilleursScores.push_back(coupleMeilleurScore);
		i++;
	}

	myfile.close();

	return EXIT_SUCCESS;
};

int Jeu::sauvegarderJeu(std::string partiesASauvegarder){
	std::filesystem::path p = std::filesystem::current_path();
    std::string cheminRelatif=p.relative_path();
	std::string filename= "/"+cheminRelatif + "/../templeRun/jeu/savesJeu/"+partiesASauvegarder+".txt";

	//std::cout<<"save filename: "<< filename<<std::endl;
	//vide le fichier au cas ou il y a deja une sauvegarde pour ce nom de partie
	std::remove(filename.c_str());	
	//open the file
	std::ofstream myfile;
	myfile.open(filename.c_str());
	
    if(!myfile.is_open()){
        std::cerr << "error: can not create file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

	for(int i=0;i<partiesSauvegardees.size();i++){
		std::string partieASauvegarder = partiesSauvegardees[i].getName();
		myfile << partieASauvegarder<<std::endl;
	}

	myfile.close();
	return EXIT_SUCCESS;
}

int Jeu::sauvegarderMeilleur(std::string meilleuresPartiesASauvegarder){
	std::filesystem::path p = std::filesystem::current_path();
    std::string cheminRelatif=p.relative_path();
	std::string filename= "/"+cheminRelatif + "/../templeRun/jeu/savesJeu/"+meilleuresPartiesASauvegarder+".txt";
	std::remove(filename.c_str());	
	//open the file
	std::ofstream myfile;
	myfile.open(filename.c_str());
	
    if(!myfile.is_open()){
        std::cerr << "error: can not create file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

	for(int i=0;i<5;i++){
		std::pair<std::string, int> coupleMeilleurScore = meilleursScores[i];
		myfile << coupleMeilleurScore.first << " " <<coupleMeilleurScore.second << std::endl;
	}
	
	myfile.close();
	return EXIT_SUCCESS;
}


//---------------aides aux test----------------- 
void Jeu::displayPartiesSauvegardrees() const
{
	for(int i=0; i<partiesSauvegardees.size()-1; i++)
	{
		std::cout << partiesSauvegardees[i].getName()<<std::endl;
	}
}

void Jeu::displayMeilleuresParties() const
{
	for(int i=0; i<meilleursScores.size(); i++)
	{
		std::cout << meilleursScores[i].first <<" -> "<< meilleursScores[i].second <<std::endl;
	}
}





