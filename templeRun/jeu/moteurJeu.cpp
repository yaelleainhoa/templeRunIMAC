#include "include/Jeu.hpp"
#include "include/Objets.hpp"
#include "include/Personnage.hpp"
#include "include/Cases.hpp"
#include <vector>
#include <deque>
#include <iostream>
#include <fstream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

int NB_TOURS_SINGES=-1;//a passer en variable globale
                    //--> egal à -1 tant que le singe ne s'st pas déplacé
                    //lorsque le joueur se prend un obstacle de gravité 0 les singes avancent pendant5 tours
                    //--> NB_TOURS_SINGES =5
                    //dans la boucle de jeu si la variable est >0 la variable decrémente de 1 à chaque tours
                    // : qd il arrive à 0 on appelle singes.deplacement(1)
                    //et on met NB_TOURS_SINGES =-1 

void testMvt(Case courante, Joueur joueur, Partie partie )
{   //cas ou on est sur la case de gauche
    if(joueur.getPositionHorizontale()==-1)
    {
        std::vector<Objet> objets=courante.ssCaseGauche.getObjet();
        if(!objets.empty())
        {
            for(size_t i=0; i<objets.size(); i++)
            {
                //cas 1: l'objet est une piece et le joueur l'attrappe -> on incremente le score
                if(objets[i].passe(joueur)&&objets[i].estPiece())
                {   //on crée une piece temporaire pour appliqué les méthodes dessus
                    Piece temp(objets[i].getIdObjet(),objets[i].getMvt());
                    partie.incrementeScore(temp.getValeur());//trouver comment utiliser une metgode de l'enfant sur le parent
                }
                //cas 2: l'objet est un obstacle et le joueur ne passe pas -> il meurt
                if((!objets[i].passe(joueur)) && objets[i].estObstacle())
                {   //on crée un objet temporaire pour pouvoir utiliser les méthodes
                    Obstacle temp(objets[i].getIdObjet());
                    if(temp.getGravite()==1)
                    {//partie.setEtat(MORT);//MORT en variable globale? sinon mettre l'int correspondant
                        partie.setEtat(0);//A CHANGER avec la version precedente
                    }
                    else 
                    {
                        joueur.singes.deplacement(-1);
                        if(joueur.singes.getDistancePerso()==0)
                            {partie.setEtat(0);}//MORT
                        else
                            {NB_TOURS_SINGES=5;}
                    }
                }
            }
        }
    }
    //on fait pareil dans le cas ou il est au milieu
    if(joueur.getPositionHorizontale()==0)
    {
        std::vector<Objet> objets=courante.ssCaseMilieu.getObjet();
        if(!objets.empty())
        {
            for(size_t i=0; i<objets.size(); i++)
            {   //cas 1: l'objet est une piece et le joueur l'attrappe -> on incremente le score
                if(objets[i].passe(joueur)&&objets[i].estPiece())
                {
                    //on crée une piece temporaire pour appliqué les méthodes dessus
                    Piece temp(objets[i].getIdObjet(),objets[i].getMvt());
                    partie.incrementeScore(temp.getValeur());//trouver comment utiliser une metgode de l'enfant sur le parent
                }
                //cas 2: l'objet est un obstacle et le joueur ne passe pas -> il meurt
                if((!objets[i].passe(joueur)) && objets[i].estObstacle())
                {   //on crée un objet temporaire pour pouvoir utiliser les méthodes
                    Obstacle temp(objets[i].getIdObjet());
                    if(temp.getGravite()==1)
                    {   //partie.setEtat(MORT);//MORT en variable globale? sinon mettre l'int correspondant
                        partie.setEtat(0);//A CHANGER avec la version precedente
                    }
                    else 
                    {
                        joueur.singes.deplacement(-1);
                        if(joueur.singes.getDistancePerso()==0)
                            {partie.setEtat(0);}//MORT
                        else
                            {NB_TOURS_SINGES=5;}
                    }
                }
            }
        }
    }
    //cas on est est sur la case de droite 
    else
    {
        std::vector<Objet> objets=courante.ssCaseDroite.getObjet();
        if(!objets.empty())
        {
            for(size_t i=0; i<objets.size(); i++)
            {
                 //cas 1: l'objet est une piece et le joueur l'attrappe -> on incremente le score
                if(objets[i].passe(joueur)&&objets[i].estPiece())
                {
                    //on crée une piece temporaire pour appliqué les méthodes dessus
                    Piece temp(objets[i].getIdObjet(),objets[i].getMvt());
                    partie.incrementeScore(temp.getValeur());//trouver comment utiliser une metgode de l'enfant sur le parent
                }
                //cas 2: l'objet est un obstacle et le joueur ne passe pas -> il meurt
                if((!objets[i].passe(joueur)) && objets[i].estObstacle())
                {
                    //on crée un objet temporaire pour pouvoir utiliser les méthodes
                    Obstacle temp(objets[i].getIdObjet());
                    if(temp.getGravite()==1)
                    {   //partie.setEtat(MORT);//MORT en variable globale? sinon mettre l'int correspondant
                        partie.setEtat(0);//A CHANGER avec la version precedente
                    }
                    else 
                    {
                        joueur.singes.deplacement(-1);
                        if(joueur.singes.getDistancePerso()==0)
                            {partie.setEtat(0);}//MORT
                        else
                            {NB_TOURS_SINGES=5;}
                    }
                }
            }
        }
    }
}


int main()
{
    std::cout<< "maaaaaaaaarche stp "<< std::endl;
    return 0;
}
