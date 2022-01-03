#include "../include/fenetresTextuelles.hpp"
using namespace glimac;

Jeu *jeu = Jeu::getInstance();

void FenetreTextuelle::apply_surface( int x, int y, SDL_Surface* source) { 
	SDL_Rect offset; 

	offset.x = x; 
	offset.y = y;

    SDL_BlitSurface( source, NULL, fondFenetreTextuelle, &offset ); 
}

void FenetreTextuelle::fenetreEnTexture(float x, float y, float longueur, float largeur){

    //on crée un rectangle, celui sur lequel on appliquera la texture de la fenetre textuelle
    glGenBuffers(1,&VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    Vertex2DUV vertices[]{
        Vertex2DUV(glm::vec2(-longueur/2+x,largeur/2+y),glm::vec2(0.0,0.0)),
        Vertex2DUV(glm::vec2(longueur/2+x,largeur/2+y),glm::vec2(1,0.0)),
        Vertex2DUV(glm::vec2(longueur/2+x, -largeur/2+y),glm::vec2(1.0,1.0)),
        Vertex2DUV(glm::vec2(-longueur/2+x,-largeur/2+y),glm::vec2(0.0,1.0))
    };
    glBufferData(GL_ARRAY_BUFFER,4*sizeof(Vertex2DUV),vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glGenBuffers(1,&IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    uint32_t index[]={0,1,2,
                    0,2,3};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(uint32_t), index, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

    int INDEX_ATTR_POSITION=0;
    int INDEX_ATTR_TEXTURE=1;
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(INDEX_ATTR_POSITION);
    glEnableVertexAttribArray(INDEX_ATTR_TEXTURE);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
    glVertexAttribPointer(INDEX_ATTR_POSITION, 2, GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),0);
    glVertexAttribPointer(INDEX_ATTR_TEXTURE, 2, GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(const GLvoid*) (2*sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, fondFenetreTextuelle->w, fondFenetreTextuelle->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, fondFenetreTextuelle->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void FenetreTextuelle::Draw(Program &program){
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glUniform1i(texture,0);
    glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT,0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

void TableauDeScore::setTableauDeScore(const Partie &partie){
    score=partie.getScore();
    meilleurScore=jeu->getListeMeilleuresParties()[0].second;
    distance=partie.getDistance();
}


void TableauDeScore::creation(){
    SDL_FreeSurface( fondFenetreTextuelle ); 
    SDL_Surface *indicationDistance = NULL;
    SDL_Surface *indicationScore = NULL;
    SDL_Surface *indicationMeilleurScore = NULL;
    //taille de la surface du tableau
    fondFenetreTextuelle = SDL_CreateRGBSurface(SDL_SWSURFACE, 300, 80, 32, 0, 0, 0, 0);

    //on met du noir en fond de la fenetre textuelle
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format, 0,0,0));

    //les messages à afficher sont des char
    std::string strScore = "Score : "+std::to_string(score)+" points";
    std::string strMeilleurScore = "Meilleur score : "+std::to_string(meilleurScore)+" points";
    std::string strDistance = "Distance : "+std::to_string(distance);

    //creation des message s
    indicationDistance = TTF_RenderText_Blended( font, strDistance.c_str(), textColor ); 
    indicationScore = TTF_RenderText_Blended( font, strScore.c_str(), textColor ); 
    indicationMeilleurScore = TTF_RenderText_Blended( font, strMeilleurScore.c_str(), textColor ); 

    //on ajoute les messages au tableau
    apply_surface( 20, 20, indicationDistance); 
    apply_surface( 20, 35, indicationScore); 
    apply_surface( 20, 50, indicationMeilleurScore); 

    //avant de transformer en texture, on choisit la taille de notre fenetre textuelle
    float longueur=1;
    float largeur=0.3;
    this->fenetreEnTexture(-(1-longueur/2), 1-largeur/2, longueur,largeur);
}


void MenuPause::creation(){
    SDL_Surface *Pause = NULL;
    SDL_Surface *Recommencer = NULL;
    SDL_Surface *Sauvegarder = NULL;
    SDL_Surface *Reprendre = NULL;

    //taille de la surface du tableau
    fondFenetreTextuelle = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 800, 32, 0, 0, 0, 0);

    //si on veut donner une couleur de fond
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  0,0,0));

    //les messages à afficher sont des char
    std::string pause = "PAUSE";
    std::string recommencer = "Recommencer (R)";
    std::string sauvegarder = "Sauvegarder la partie (S)";
    std::string reprendre = "Reprendre la partie (ESC)";

    //creation des messages
    Pause = TTF_RenderText_Blended( font, pause.c_str(), textColor ); 
    Recommencer = TTF_RenderText_Blended( font, recommencer.c_str(), textColor ); 
    Sauvegarder = TTF_RenderText_Blended( font,sauvegarder.c_str(), textColor ); 
    Reprendre = TTF_RenderText_Blended( font, reprendre.c_str(), textColor ); 

    //on ajoute les messages au tableau
    apply_surface( 350, 50, Pause); 
    apply_surface( 210, 272, Recommencer); 
    apply_surface( 80, 342, Sauvegarder); 
    apply_surface( 80, 412, Reprendre); 

    float longueur=1.5;
    float largeur=1.5;
    this->fenetreEnTexture(0, 0,longueur,largeur);
}


void MenuDebutDePartie::creation(){
    SDL_Surface *Jeu = NULL;
    SDL_Surface *AnciennePartie = NULL;
    SDL_Surface *VoirMeilleursScores = NULL;
    SDL_Surface *Jouer = NULL;
    SDL_Surface *Reprendre = NULL;

    //taille de la surface du tableau
    fondFenetreTextuelle = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 800, 32, 0, 0, 0, 0);

    //si on veut donner une couleur de fond
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  0,0,0));

    //les messages à afficher sont des char
    std::string jeu = "RUN BABIMAC!";
    std::string anciennePartie = "Recharger ancienne partie (R)";
    std::string voirMeilleursScores = "Voir meilleurs scores (M)";
    std::string jouer = "JOUER (J)";

    //creation des messages
    Jeu = TTF_RenderText_Blended( font, jeu.c_str(), textColor ); 
    AnciennePartie = TTF_RenderText_Blended( font, anciennePartie.c_str(), textColor ); 
    VoirMeilleursScores = TTF_RenderText_Blended( font, voirMeilleursScores.c_str(), textColor ); 
    Jouer = TTF_RenderText_Blended( font,jouer.c_str(), textColor ); 

    //on ajoute les messages au tableau
    apply_surface( 220, 50, Jeu); 
    apply_surface( 20, 272, AnciennePartie); 
    apply_surface( 80, 342, VoirMeilleursScores); 
    apply_surface( 300, 512, Jouer); 

    float longueur=1.5;
    float largeur=1.5;
    this->fenetreEnTexture(0, 0,longueur,largeur);
}


void EntrerNomDeLaPartie::creation(){
    SDL_FreeSurface( fondFenetreTextuelle ); 
    SDL_Surface *Entrez = NULL;
    SDL_Surface *NomPartie = NULL;
    SDL_Surface *ChampTexte=NULL;


    //taille de la surface du tableau
    fondFenetreTextuelle = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 800, 32, 0, 0, 0, 0);
    ChampTexte = SDL_CreateRGBSurface(SDL_SWSURFACE, 500, 80, 32, 0, 0, 0, 0);

    //si on veut donner une couleur de fond
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  0,0,0));
    SDL_FillRect(ChampTexte, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  255, 255, 255));

    //les messages à afficher sont des char
    std::string entrez = "ENTREZ LE NOM DE VOTRE PARTIE : ";


    //creation des messages
    Entrez = TTF_RenderText_Blended( font, entrez.c_str(), textColor ); 
    NomPartie = TTF_RenderText_Blended( font, nomPartie.c_str(), { 0,0,0 } ); 

    //on ajoute les messages au tableau
    apply_surface( 20, 300, Entrez); 

    SDL_Rect offset; 
	offset.x = 20; 
	offset.y = 10;
    SDL_BlitSurface( NomPartie, NULL, ChampTexte, &offset ); 
    apply_surface( 100, 500, ChampTexte); 

    float longueur=1.5;
    float largeur=1.5;
    this->fenetreEnTexture(0, 0,longueur,largeur);
}


//peut être donner une capacité au vecteur puisqu'on veut sauvegarder un nombre fini de parties
void AffichageAnciennesPartiesSauvegardees::creation(){
    SDL_FreeSurface( fondFenetreTextuelle ); 
    SDL_Surface *PartieACharger = NULL;
    SDL_Surface *ESC = NULL;


    //taille de la surface du tableau
    fondFenetreTextuelle = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 800, 32, 0, 0, 0, 0);

    //si on veut donner une couleur de fond
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  0,0,0));

    //les messages à afficher sont des char
    std::string partieACharger = "CHOISISSEZ LA PARTIE";
    std::string escape = "(<-- ESC)";

    //creation des messages 
    PartieACharger = TTF_RenderText_Blended( font, partieACharger.c_str(), textColor ); 
    ESC = TTF_RenderText_Blended(font, escape.c_str(), textColor);

    //on ajoute les messages au tableau
    apply_surface( 20, 50, PartieACharger); 

    for (int i=0; i<anciennesParties.size(); i++){
        SDL_Surface *Partie=NULL;
        char toucheDeClavier = char(i+97);
        std::string str_toucheDeClavier(1, toucheDeClavier);
        std::string partie = "Partie ("+str_toucheDeClavier+") : "+anciennesParties[i].getName();
        Partie=TTF_RenderText_Blended(font, partie.c_str(), textColor);
        apply_surface(50,200+100*i, Partie);
    }

    apply_surface( 5, 100, ESC); 

    float longueur=1.5;
    float largeur=1.5;
    this->fenetreEnTexture(0, 0,longueur,largeur);
}

void AffichageMeilleursScores::creation(){
    SDL_FreeSurface( fondFenetreTextuelle ); 
    SDL_Surface *MeilleursScores = NULL;
    SDL_Surface *ESC = NULL;

    //taille de la surface du tableau
    fondFenetreTextuelle = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 800, 32, 0, 0, 0, 0);

    //si on veut donner une couleur de fond
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  0,0,0));

    //les messages à afficher sont des char
    std::string meilleursScores = "MEILLEURS SCORES";
    std::string escape = "(<-- ESC)";


    //creation des messages 
    MeilleursScores = TTF_RenderText_Blended( font, meilleursScores.c_str(), textColor ); 
    ESC = TTF_RenderText_Blended(font, escape.c_str(), textColor);

    //on ajoute les messages au tableau
    apply_surface( 20, 50, MeilleursScores); 
    apply_surface( 5, 100, ESC); 

    for (int i=0; i<meilleursScoresJeu.size(); i++){
        SDL_Surface *Partie=NULL;
        std::string partie = meilleursScoresJeu[i].first+" SCORE : "+std::to_string(meilleursScoresJeu[i].second);
        Partie=TTF_RenderText_Blended(font, partie.c_str(), textColor);
        apply_surface(50,220+100*i, Partie);
    }


    float longueur=1.5;
    float largeur=1.5;
    this->fenetreEnTexture(0, 0,longueur,largeur);
}

void Mort::creation(){
    SDL_FreeSurface( fondFenetreTextuelle ); 
    SDL_Surface *Mort = NULL;


    //taille de la surface du tableau
    fondFenetreTextuelle = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 800, 32, 0, 0, 0, 0);

    //si on veut donner une couleur de fond
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  227, 41, 27));

    std::string mort = "PERDU !";

    //creation des messages 
    Mort = TTF_RenderText_Blended( font, mort.c_str(), textColor ); 

    //on ajoute les messages au tableau
    apply_surface( 20, 100, Mort); 

    float longueur=1.5;
    float largeur=1.5;
    this->fenetreEnTexture(0, 0,longueur,largeur);
}
