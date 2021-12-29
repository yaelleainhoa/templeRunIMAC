#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include "../include/moteurJeu.hpp"
void testMvtssCase(ssCase courante, Joueur joueur, Partie &partie )
{
    //std::cout<<"position horizontale : "<<joueur.getPositionHorizontale()<<std::endl;
    //std::cout<<"position verticale : "<<joueur.getPositionVerticale()<<std::endl;
    std::vector<Objet> objets=courante.getObjet();
        if(!objets.empty())
        {
            //std::cout<<"objet sur cette case!!"<<std::endl;
            for(size_t i=0; i<objets.size(); i++)
            {
               //cas 1: l'objet est une piece et le joueur l'attrappe -> on incremente le score
                //std::cout<<"position objet : "<<objets[i].getMvt()<<std::endl;
                if(objets[i].passe(joueur)&&objets[i].estPiece())
                {//std::cout<<"piece en position : "<< joueur.getPositionHorizontale()<<std::endl;
                    //on crée une piece temporaire pour appliqué les méthodes dessus
                    Piece temp(objets[i].getIdObjet(),objets[i].getMvt());
                    partie.incrementeScore(temp.getValeur());//trouver comment utiliser une metgode de l'enfant sur le parent
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
                        partie.setEtat(0);//A CHANGER avec la version precedente
                    }
                    else 
                    {   std::cout << "singes "<< std::endl;
                        joueur.singes().deplacement(-1);//met la variable tours restants à 5;
                        if(joueur.singes().getDistancePerso()==0)
                            {partie.setEtat(0);}//MORT
                    }
                }
        }
    }
}
void testMvt(Case courante, Joueur joueur, Partie &partie )
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
    std::deque<Case> cases;
    std::default_random_engine re(time(0));
    std::uniform_int_distribution<int> distrib{0,4};//indices des obstacles
    for(int i=0; i<nbCases; i++)//on crée 20 cases possibles
    {
        int id_Text;
        int position=0;
        int id_objets= distrib(re);
        std::cout<< "id_objets="<<id_objets<<std::endl;
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
        if(id_Text>2)//si c'est un trou l'objet est directement crée à la construction de la case grace à l'id_text
        {
            Obstacle obstacle(id_objets);
            mvt=obstacle.getMvt();
            std::uniform_int_distribution<int> distribPos{-1,1};//position latérale
            position=distribPos(re);
            temp.ajouterObjetCase(obstacle,position);//onn ajoute l'obstacle à la case
        }
        //on ajoute une piece à l'endroit ou on doit se placer pour survivre à l'obstacle
        std::uniform_int_distribution<int> distribIdPiece{0,2};//id de la piece -> valeur 
        int id_Piece=distribIdPiece(re);
        Piece piece(id_Piece,mvt);
        temp.ajouterObjetCase(piece,position);


        cases.push_back(temp);
    }
    return cases;
}