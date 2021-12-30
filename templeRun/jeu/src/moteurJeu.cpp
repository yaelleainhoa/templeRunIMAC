#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include "../include/moteurJeu.hpp"
void testMvtssCase(ssCase &courante, Joueur joueur, Partie &partie )
{
    //std::cout<<"position horizontale : "<<joueur.getPositionHorizontale()<<std::endl;
    //std::cout<<"position verticale : "<<joueur.getPositionVerticale()<<std::endl;
    std::vector<Objet> objets=courante.getObjet();
        if(!objets.empty())
        {
            //std::cout<<"objet sur cette case!!"<<std::endl;
            for(size_t i=0; i<objets.size(); i++)
            {
                std::cout << courante.getObjet()[i].getTypeObjet() << ", " << courante.getObjet()[i].getIdObjet() << std::endl;
               //cas 1: l'objet est une piece et le joueur l'attrappe -> on incremente le score
                //std::cout<<"position objet : "<<objets[i].getMvt()<<std::endl;
                if(objets[i].passe(joueur)&&objets[i].estPiece())
                {//std::cout<<"piece en position : "<< joueur.getPositionHorizontale()<<std::endl;
                    //on crée une piece temporaire pour appliqué les méthodes dessus
                    Piece temp(objets[i].getIdObjet(),objets[i].getMvt());
                    partie.incrementeScore(temp.getValeur());//trouver comment utiliser une metgode de l'enfant sur le parent
                    courante.attrapeObjetAt(i); //ici on veut changer l'original donc on ne passe pas par la copie objets!
                }
                //cas 2: l'objet est un obstacle et le joueur ne passe pas -> il meurt
                if((!objets[i].passe(joueur)) && objets[i].estObstacle())
                {   //std::cout<<"se prend l'obstacle en position "<<joueur.getPositionHorizontale()<<std::endl;
                      //on crée un objet temporaire pour pouvoir utiliser les méthodes
                    Obstacle temp(objets[i].getIdObjet());
                    std::cout<<temp.getGravite()<<"\n";
                    if(temp.getGravite()==0)
                    {std::cout<<"mort"<<std::endl;
                        //partie.setEtat(MORT);//MORT en variable globale? sinon mettre l'int correspondant
                        partie.setEtat(MORT);//A CHANGER avec la version precedente
                    }
                    else 
                    {std::cout << "singes "<< std::endl;
                        // std::cout << "obj.mvt : " << objets[i].getMvt() << std::endl;
                        // std::cout<<"position verticale : "<<joueur.getPositionVerticale()<<std::endl;
                        joueur.singes().deplacement(-1);
                        courante.attrapeObjetAt(i);
                        if(!poursuite1){ poursuite1 = true; etatSinges = 1;}
                        else if(poursuite1 && !poursuite2){ poursuite2 = true; etatSinges = 2;}
                        else if(poursuite1 && poursuite2) etatSinges = 2;
                        if(joueur.singes().getDistancePerso()==0)
                            {partie.setEtat(0);}//MORT
                            {partie.setEtat(MORT);}//MORT
                        else
                            {NB_TOURS_SINGES=5;}
                    }
                }
        }
    }
}
void testMvt(Case &courante, Joueur joueur, Partie &partie )
{   //cas ou on est sur la case de gauche
    if(joueur.getPositionHorizontale()==-1)
    {
        testMvtssCase(courante.ssCaseGauche,joueur, partie );
    }
    //on fait pareil dans le cas ou il est au milieu
    else if(joueur.getPositionHorizontale()==0)
    {
        testMvtssCase(courante.ssCaseMilieu,joueur, partie );
    }
    //cas on est est sur la case de droite 
    else
    {
        testMvtssCase(courante.ssCaseDroite,joueur, partie );
    }
}

std::deque<Case> creerCasesAvecDanger()//creation de Cases avec obstacles 
{
    int nbCases=20;
    int c = 0;
    std::deque<Case> cases;
    std::default_random_engine re(time(0));
    std::uniform_int_distribution<int> distrib{0,5};//indices des obstacles
    for(int i=0; i<nbCases; i++)//on crée 20 cases possibles
    {
        int id_Text;
        int position=0;
        int id_objets= distrib(re);
        std::cout<< "id_objets="<<id_objets<<std::endl;
        if(id_objets == 0 || id_objets == 3) c++;
        int mvt=1;//si c'est un trou on ne change pas cette valeur 
        switch (id_objets)
        {
            case 0://trou à gauche
            std::cout <<"trou gauche\n";
                id_Text=1;
                position=-1;
                break;
            case 1://trou au milieu
            std::cout <<"trou milieu\n";
                id_Text=2;
                position=0;
                break;
            case 2://trou à droite
            std::cout <<"trou droite\n";
                id_Text=3;
                position=1;
                break;
            default://autres types d'obstacles
            std::cout <<"autre\n";
                id_Text=0;
                break;
        }
        Case temp(id_Text);
        
        if(id_Text>3 || id_Text==0)//si c'est un trou l'objet est directement crée à la construction de la case grace à l'id_text
        {   
            // 2 parce qu'il n'y a que 3 types d'autres obstacles (sans compter les trous) et avec la pomme qui me sert de cobaye donc il n'y en aura que 2 au final, enfin je crois
            //j'ai fait un petit changement au niveau des id des obstacles : 
            //l'id = au rang de l'objet dans le tableau de model obstacle + 1 (sinon il y avait un conflit avec le trou qui avait le meme type et le meme id ==> du coup le trou et le tancarville se dessiner tout le temps ensemble) (je sais pas si c'est très clair)
            Obstacle obstacle(id_objets-2);
            mvt=obstacle.getMvt();
            std::uniform_int_distribution<int> distribPos{-1,1};//position latérale
            position=distribPos(re);
            // pour éviter de creer des tancarvilles qui ne seront pas draw (je sais pas si c'est vraiment utile) car la condition dans drawObjectssCase() c'est if(la taille  == 3  && cas == -1)
            if(obstacle.getTaille() == 3 && position == -1 || obstacle.getTaille() != 3){
                temp.ajouterObjetCase(obstacle,position);//onn ajoute l'obstacle à la case
            }
            //juste des tests, je les laisse au cas où, désolée
            if(obstacle.getTaille() == 3 && position == -1){
                std::cout <<  "un tancarville à la bonne position !" << std::endl;
            }else if(obstacle.getTaille() == 3 && position != -1){
                std::cout << "un tancarville MAIS pas à la bonne position car position = " << position << std::endl;
            }
        }
        else{
            std::cout << "idtexture = " << id_Text << std::endl;
            std::cout << "numéro de la case que l'on contruit sur 20 : " << i << std::endl;
        }
        //on ajoute une piece à l'endroit ou on doit se placer pour survivre à l'obstacle
        std::uniform_int_distribution<int> distribIdPiece{0,2};//id de la piece -> valeur 
        int id_Piece=distribIdPiece(re);
        Piece piece(id_Piece,mvt);
        temp.ajouterObjetCase(piece,position);

        cases.push_back(temp);
        Case simple(0);
        cases.push_back(simple);
        cases.push_back(simple);
    }
    std::cout << "compteur de id_objects == 0 : " << c << std::endl; 
    return cases;
}

std::deque<Case> creerCasesSansDanger()//creation de Cases sans obstacle
{
    int nbCases=10;//on crée 10 cases possibles
    std::deque<Case> cases;
    std::default_random_engine re(time(0));
    std::uniform_int_distribution<int> distribId{0,2};//indices piece->valeur
    std::uniform_int_distribution<int> distribPos{-1,1};//positin laterale de la piece
    std::uniform_int_distribution<int> distribMvt{-1,1};//mvt associé à la piece
    
    for(int i=0; i<nbCases; i++)
    {
        int id_Text=0;//que des sol uni puisque pas d'obstacles
        int position=distribPos(re);
        int id_Piece= distribId(re);
        int mvt =distribMvt(re); 

        Case temp(id_Text);
        Piece piece(id_Piece,mvt);
        temp.ajouterObjetCase(piece,position);

        cases.push_back(temp);
    }
    return cases;
}