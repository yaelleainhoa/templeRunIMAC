#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

#include "../include/moteurJeu.hpp"

void testMvtssCase(ssCase &courante, Joueur joueur, Partie &partie )
{
    std::vector<Objet> objets = courante.getObjet();
    if(!objets.empty())
    {
        for(size_t i=0; i<objets.size(); i++)
        {
            //cas 1: l'objet est une piece et le joueur l'attrappe -> on incremente le score
            if(objets[i].passe(joueur)&&objets[i].estPiece())
            {   //on crée une piece temporaire pour appliquer les méthodes dessus
                Piece temp(objets[i].getIdObjet(),objets[i].getMvt());
                partie.incrementeScore(temp.getValeur());
                courante.attrapeObjetAt(i); //ici on veut changer l'original donc on ne passe pas par la copie objets!
            }
            //cas 2: l'objet est un obstacle et le joueur ne passe pas -> il meurt
            if((!objets[i].passe(joueur)) && objets[i].estObstacle())
            {   //on crée un objet temporaire pour pouvoir utiliser les méthodes
                Obstacle temp(objets[i].getIdObjet());
                if(temp.getGravite()==1)
                {
                    partie.setEtat(MORT);//MORT est une variable globaale ( c'est un int)
                }
                else //si l'objet est de gravité 0
                {
                    joueur.singes().deplacement(-1);//le singe se "rapproche" du joueur
                    courante.attrapeObjetAt(i);
                    if(!poursuite1)
                        {poursuite1 = true; 
                        etatSinges = 1;}
                    else if(poursuite1 && !poursuite2)
                        { poursuite2 = true; 
                        etatSinges = 2;}
                    else if(poursuite1 && poursuite2) 
                        {etatSinges = 2;}
                    if(joueur.singes().getDistancePerso()==0)
                        {partie.setEtat(MORT);}
                    else
                        {joueur.singes().initialiseDistanceSinges();}
                            {NB_TOURS_SINGES=5;};
                }
            }
        }
    }
}
void testMvt(Case &courante, Joueur joueur, Partie &partie )
{   //cas où l'on est sur la case de gauche
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

std::deque<Case> creerCasesAvecDanger()//création de Cases avec obstacles 
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
        int mvt=1;//si c'est un trou on ne change pas cette valeur 
        switch (id_objets)
        {
            case 0://trou à gauche
                id_Text=1;
                position=-1;
                break;
            case 1://trou au milieu
                id_Text=2;
                position=0;
                break;
            case 2://trou à droite
                id_Text=3;
                position=1;
                break;
            default://autres types d'obstacles
                id_Text=0;
                break;
        }
        Case temp(id_Text);//on crée une case avec la bonne texture avant de lui rajouter les objets
        
        //si c'est un trou l'objet est directement crée à la construction de la case grace à l'id_text
        if(id_Text==0)
        {   
           Obstacle obstacle(id_objets-2);
            mvt=obstacle.getMvt();
            std::uniform_int_distribution<int> distribPos{-1,1};//position latérale
            position=distribPos(re);

            temp.ajouterObjetCase(obstacle, position);//on ajoute enfin l'obstacle à la case en position aléatoire
        }

        //on ajoute ensuite une pièce à l'endroit où l'on doit se placer pour survivre à l'obstacle
        std::uniform_int_distribution<int> distribIdPiece{0,2};//l'id de la piece donne la valeur 
        int id_Piece=distribIdPiece(re);
        Piece piece(id_Piece,mvt);
        temp.ajouterObjetCase(piece,position);

        //on ajoute finalement la piece créée à l'ensemble des cases
        cases.push_back(temp);
    }
    return cases;
}

std::deque<Case> creerCasesSansDanger()//creation de Cases sans obstacle
{
    int nbCases=10;//on crée 10 cases possibles
    std::deque<Case> cases;
    std::default_random_engine re(time(0));
    std::uniform_int_distribution<int> distribId{0,2};//indices piece (donne la valeur)
    std::uniform_int_distribution<int> distribPos{-1,1};//position latérale de la pièce
    std::uniform_int_distribution<int> distribMvt{-1,1};//mvt associé à la pièce
    
    for(int i=0; i<nbCases; i++)
    {
        int id_Text=0;//que des sols unis puisque pas d'obstacle

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

std::deque<Case> initialiseParcoursDepart(std::vector<std::deque<Case>> &parcoursPossibles){
    std::deque<Case> parcoursDepart;
    for(int i=0; i<30; i++){
        if(i%5==0) parcoursDepart.push_back(parcoursPossibles[1][rand()%(parcoursPossibles[1].size())]);
        else parcoursDepart.push_back(parcoursPossibles[0][rand()%(parcoursPossibles[0].size())]);
    }
    return parcoursDepart;
}