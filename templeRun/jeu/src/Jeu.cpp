#include"../include/Jeu.hpp"
Jeu* Jeu::instance = 0;

//------------méthodes partie-------------------
void Partie::sauvegarderSsCase(const ssCase &ssCase, std::ofstream &myfile) const
{

	//écriture des paramètres des objets pour chaque sous case ( 2 lignes par ssCase)

		std::vector<Objet> objets = ssCase.getObjet();
		for(int j=0; j<objets.size(); j++)
		{//Type_Objet (0 ou 1) ; idObjet (id de la texture dans le tableau correspondant au type d'objet) 
			myfile << objets[j].getTypeObjet() <<" "<< objets[j].getIdObjet() <<" "<<  objets[j].getMvt()<< std::endl;
		}
		if(objets.size()<2)//si on a pas 2 objets on complète avec des lignes de -1 ( à la lecture on "ignorera ces lignes")
		{
			for(int k=0; k<2-objets.size(); k++){myfile << -1 << -1 << -1 << std::endl;}
		}
}

int Partie::sauvegarder() const
{
	//chargement du chemin relatif du dossier 
	std::filesystem::path p = std::filesystem::current_path();
    std::string cheminRelatif=p.relative_path();
	//création (ou ouverture) du fichier .txt
	std::string filename= "/" + cheminRelatif + "/../templeRun/jeu/saves/"+nomPartie+".txt";
	//vide le fichier au cas ou il y a déjà une sauvegarde à ce nom de partie
	std::remove(filename.c_str());	
	//ouvre le fichier:
	std::ofstream myfile;
	myfile.open(filename.c_str());
	
    if(!myfile.is_open()){
        std::cerr << "error: can not create file: " << filename << std::endl;
        return EXIT_FAILURE;
    }

	//écrit les paramètres principaux de la partie
    myfile << score<<std::endl;
	myfile<< distance<<std::endl;
	myfile << etat<<std::endl;
	//on écrit le nombre de cases pour pouvoir recharger plus tard 
	myfile << cheminVisible.size()<<std::endl;
	//on ecrit les information sur la prochaine case de rotation (on en a toujours exactement 1 sur le chemin visible)
	myfile << sensRotation << std::endl;
	myfile << numCaseRot << std::endl;
	myfile << casTerrain << std::endl;
	//on écrit les informations sur les casesdu chemin 
	for(size_t i =0; i<cheminVisible.size(); i++)
	{
		//1) texture de la case
		myfile<< cheminVisible[i].getText()<<std::endl;
		//----------objets ssCase gauche
		sauvegarderSsCase(cheminVisible[i].ssCaseGauche, myfile);
		//----------objets ssCase milieu
		sauvegarderSsCase(cheminVisible[i].ssCaseGauche, myfile);
		//----------objets ssCase droite
		sauvegarderSsCase(cheminVisible[i].ssCaseGauche, myfile);
	} 
	myfile.close();
	return EXIT_SUCCESS;
}

//------------méthodes Jeu----------------------

void Jeu::ajouteMeilleurePartie(Partie const &newPartie)
{
	int size =meilleursScores.size();
	//on crée le couple (nom,score) correspondant à la nouvelle partie
	std::pair<std::string, int> couplePartie (newPartie.getName(), newPartie.getScore());
	if(size==0)//si la liste est vide on ajoute direct le score de la nouvelle partie
	{
		meilleursScores.push_back(couplePartie);
	}
	else{
		//on vérifie si on n'a pas déjà enregistré un meilleur score pour cette partie
		if(!any_of(meilleursScores.begin(), meilleursScores.end(), 
			[&](const auto & x){return (x.first==newPartie.getName() || x.second==newPartie.getScore());}))
		{
				//Ajout ou non aux meilleures parties 
				for(size_t i=0; i<size; i++)
				{
					if(newPartie.getScore() > meilleursScores[i].second)
					//on insert la nouvelle partie
					{
						std::vector<std::pair<std::string, int>>::iterator pos = meilleursScores.begin();
						meilleursScores.insert(pos+i, couplePartie);

						i=size;//pour sortir de la boucle
					}
				}
			//5 meilleurs scores max
			if(size>5)//si on dépasse le nombre de place dans le vecteur on enleve la pire partie ( la derniere vu que c'est trié)
			{
				meilleursScores.pop_back();
			}
		}
	}
}

void Jeu::ajoutePartieSauvergardee(Partie const &newPartie)
{
	//Ajout à la liste des parties sauvegardées

	//on vérifie s'il existe deja une sauvegarde pour ce nom de partie -> si oui on l'écrase 
	if(!any_of(partiesSauvegardees.begin(), 
				partiesSauvegardees.end(), 
				[&](const auto & x){return x.getName()==newPartie.getName();}))
	{	
		//si une partie avec ce nom existe déjà, on ne modifie pas le vecteur 
		partiesSauvegardees.push_back(newPartie);
	}
	//si la partie existait elle sera ecrasée à l'appel de la fonction sauvegarder()
	newPartie.sauvegarder();

	//on vérifie qu'on n'a pas dépassé le nombre de partie sauvegardées autorisé (5)
	if(partiesSauvegardees.size()>5)
	{	
		std::string partieASupprimer = partiesSauvegardees.front().getName();
		partiesSauvegardees.pop_front();//supprime la première partie (la plus ancienne)
		supprimer(partieASupprimer);//on supprime la sauvegarde aussi 
	}
}

int Jeu::sauvegarderJeu(std::string partiesASauvegarder){
	std::filesystem::path p = std::filesystem::current_path();
    std::string cheminRelatif=p.relative_path();
	std::string filename= "/"+cheminRelatif + "/../templeRun/jeu/savesJeu/"+partiesASauvegarder+".txt";

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
	std::string filename= "/"+cheminRelatif + "/../templeRun/jeu/savesJeu/"+ meilleuresPartiesASauvegarder +".txt";
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
		myfile << coupleMeilleurScore.first /*nom*/ << " " <<coupleMeilleurScore.second /*score*/<< std::endl;
	}
	
	myfile.close();
	return EXIT_SUCCESS;
}

void Jeu::displayPartiesSauvegardrees() const
{//fonction uniquement là pour aider au debug
	for(int i=0; i<partiesSauvegardees.size()-1; i++)
	{
		std::cout << partiesSauvegardees[i].getName()<<std::endl;
	}
}

void Jeu::displayMeilleuresParties() const
{//pour le debug aussi
	for(int i=0; i<meilleursScores.size(); i++)
	{
		std::cout << meilleursScores[i].first <<" -> "<< meilleursScores[i].second <<std::endl;
	}
}

//-----------fonctions de chargement---------------
int chargerVecteurParties(std::string partiesACharger, std::deque <Partie> &partiesSauvegardees){
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

	// lecture des paramètres de la partie
	int i=0;
	while(!myfile.eof()&& i<5){//lit juste le nombre de ligne (s'arrête qd il y a une ligne vide grâce à eof())
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

int chargerVecteurMeilleuresParties(std::string partiesACharger, std::vector<std::pair<std::string, int>> &meilleursScores){
	std::vector <Partie> parties;
	std::filesystem::path p = std::filesystem::current_path();
    std::string cheminRelatif=p.relative_path();
	std::string filename= "/"+cheminRelatif + "/../templeRun/jeu/savesJeu/"+partiesACharger+".txt";
	//ouverture du fichier 
	std::ifstream myfile;

	myfile.open(filename.c_str());
    if(!myfile.is_open()){
        std::cerr << "error: can not open file: " << filename << std::endl << std::endl;
        EXIT_FAILURE;
    }

	// lecture des paramètres de la partie
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

void supprimer(std::string &nomPartie)
{
	std::filesystem::path p = std::filesystem::current_path();
    std::string cheminRelatif=p.relative_path();
	std::string filename= "/"+cheminRelatif + "/../templeRun/jeu/saves/"+nomPartie+".txt";
	//vide le fichier au cas ou il y a deja une sauvegarde pour ce nom de partie
	std::remove(filename.c_str());
}

void chargerObjetsSousCase(std::vector<Objet> &obj, std::ifstream &myfile)
{		//2 lignes par sous Case 
		for(int l=0; l<2; l++)
		{
			int type, id ,mvt;
			myfile >> type >> id >> mvt;
			if(type==0 && id!=0) //id 0 correspond à un trou, qui est déjà ajouté avec la texture!
			{	Piece objet(id, mvt);
				obj.push_back(objet);
			}
			else if(type==1 && id!=0)
			{	Obstacle objet(id);
				obj.push_back(objet);
			}
		}
}

Partie charger(std::string &nomPartie){
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
		//chargement des objets correspondants aux trois sous Cases: 
		chargerObjetsSousCase(objG, myfile);
		chargerObjetsSousCase(objM, myfile);
		chargerObjetsSousCase(objD, myfile);
		//création de la case contenant les objets chargés 
		Case case_i(indText,objG,objM,objD);
		cheminVisible.push_back(case_i);
	}
	//creation de la partie correspondante
	Partie partieLoad(nomPartie,cheminVisible, score, distance, etat, numCaseRot, sensRotation, casTerrain);
	//fermeture du fichier
	myfile.close();

	return partieLoad;
	EXIT_SUCCESS;
}




