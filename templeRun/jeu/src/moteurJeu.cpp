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
                std::cout << courante.getObjet()[i].getTypeObjet() << ", " << courante.getObjet()[i].getIdObjet() << std::endl;
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
                    {std::cout << "singes "<< std::endl;
                        // std::cout << "obj.mvt : " << objets[i].getMvt() << std::endl;
                        // std::cout<<"position verticale : "<<joueur.getPositionVerticale()<<std::endl;
                        joueur.singes().deplacement(-1);
                        if(!poursuite1){ poursuite1 = true; etatSinges = 1;}
                        else if(poursuite1 && !poursuite2){ poursuite2 = true; etatSinges = 2;}
                        else if(poursuite1 && poursuite2) etatSinges = 2;
                        if(joueur.singes().getDistancePerso()==0)
                            {partie.setEtat(0);}//MORT
                        else
                            {NB_TOURS_SINGES=5;}
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