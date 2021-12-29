#include "include/Terrain.hpp"
#include "variablesGlobales.hpp"



std::vector<Case*> creerCasesAvecDanger(Partie partie)//creation de Cases avec obstacles 
{
    int nbCases=20;
    std::vector<Case*> cases;
    std::default_random_engine re(time(0));
    std::uniform_int_distribution<int> distrib{0,4};//indices des obstacles
    for(int i=0; i<nbCases; i++)//on crée 20 cases possibles
    {
        int id_Text;
        int id_objets= distrib(re);
        int mvt=1;//si c'est un trou on ne change pas cette valeur 
        switch (id_objets)
        {
        case 0://trou à gauche
            id_Text=1;
        case 1://trou au milieu
            id_Text=2;
        case 2://trou à droite
            id_Text=3;
        default://autres types d'obstacles
            id_Text=0;
        }
        Case temp(id_Text);
        if(id_Text>2)//si c'est un trou l'objet est directement crée à la construction de la case grace à l'id_text
        {
            Obstacle obstacle(id_objets);
            mvt=obstacle.getMvt();
            std::uniform_int_distribution<int> distribpos{-1,1};//position latérale
            int position=distribpos(re);
            temp.ajouterObjetCase(obstacle,position);//onn ajoute l'obstacle à la case
        }
        //on ajoute une piece à l'endroit ou on doit se placer pour survivre à l'obstacle
        std::uniform_int_distribution<int> distribIdPiece{0,2};//id de la piece -> valeur 
        int id_Piece=distribIdPiece(re);
        Piece piece(id_Piece,mvt);
        temp.ajouterObjetCase(piece);


        cases.push_back(&temp);
    }
    return cases;
}



std::deque<Case*> creerCasesSansDanger()//creation de cases sans obstacles (que des pieces)
{
      for(int i=0; i<20; i++)
    {
        //int text= 
        //Case* temp();
    }


}
