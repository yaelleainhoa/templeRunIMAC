#include "../include/fenetresTextuelles.hpp"
#include "../include/variablesGlobales.hpp"
using namespace glimac;

int DEBUT=0;
int PAUSE=1;
int JEU=2;
int MEILLEURSSCORES=3;
int RECHARGER=4;
int RECOMMENCER=5;
int NOMPARTIE=6;
int ANCIENNESPARTIES=7;
int SAUVEGARDER=8;
int WARNING=9;

void FenetreTextuelle::apply_surface( int x, int y, SDL_Surface* source) { 
	SDL_Rect offset; 

	offset.x = x; 
	offset.y = y;

    SDL_BlitSurface( source, NULL, fondFenetreTextuelle, &offset ); 
}

void FenetreTextuelle::fenetreEnTexture(float x, float y, float longueur, float largeur){
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


void TableauDeScore::creation(){
    SDL_FreeSurface( fondFenetreTextuelle ); 
    SDL_Surface *indicationDistance = NULL;
    SDL_Surface *indicationScore = NULL;
    SDL_Surface *indicationMeilleurScore = NULL;
    //taille de la surface du tableau
    fondFenetreTextuelle = SDL_CreateRGBSurface(SDL_SWSURFACE, 300, 80, 32, 0, 0, 0, 0);

    //si on veut donner une couleur de fond
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format, 71, 17, 166));

    //les messages à afficher sont des char
    std::string strScore = "Score : "+std::to_string(score)+" points";
    std::string strMeilleurScore = "Meilleur score : "+std::to_string(meilleurScore)+" points";
    std::string strDistance = "Distance : "+std::to_string(distance)+" (?)";

    //creation des message 
    indicationDistance = TTF_RenderText_Blended( font, strDistance.c_str(), textColor ); 
    indicationScore = TTF_RenderText_Blended( font, strScore.c_str(), textColor ); 
    indicationMeilleurScore = TTF_RenderText_Blended( font, strMeilleurScore.c_str(), textColor ); 

    //on ajoute les messages au tableau
    apply_surface( 20, 20, indicationDistance); 
    apply_surface( 20, 35, indicationScore); 
    apply_surface( 20, 50, indicationMeilleurScore); 

    float longueur=1;
    float largeur=0.3;
    this->fenetreEnTexture(-(1-longueur/2), 1-largeur/2, longueur,largeur);
}



void MenuPause::creation(){
    SDL_Surface *Pause = NULL;
    SDL_Surface *Recommencer = NULL;
    // SDL_Surface *VoirMeilleursScores = NULL;
    SDL_Surface *Sauvegarder = NULL;
    SDL_Surface *Reprendre = NULL;

    //taille de la surface du tableau
    fondFenetreTextuelle = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 800, 32, 0, 0, 0, 0);

    //si on veut donner une couleur de fond
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  71, 17, 166));

    //les messages à afficher sont des char
    std::string pause = "PAUSE";
    std::string recommencer = "Recommencer (R)";
    std::string sauvegarder = "Sauvegarder la partie (S)";
    std::string reprendre = "Reprendre la partie (ESC)";

    //creation des message 
    Pause = TTF_RenderText_Blended( font, pause.c_str(), textColor ); 
    Recommencer = TTF_RenderText_Blended( font, recommencer.c_str(), textColor ); 
    // VoirMeilleursScores = TTF_RenderText_Blended( font, voirMeilleursScores.c_str(), textColor ); 
    Sauvegarder = TTF_RenderText_Blended( font,sauvegarder.c_str(), textColor ); 
    Reprendre = TTF_RenderText_Blended( font, reprendre.c_str(), textColor ); 

    //on ajoute les messages au tableau
    apply_surface( 350, 50, Pause); 
    apply_surface( 210, 272, Recommencer); 
    apply_surface( 80, 342, Sauvegarder); 
    apply_surface( 80, 412, Reprendre); 
    // apply_surface( 80, 482, VoirMeilleursScores); 

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
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  71, 17, 166));

    //les messages à afficher sont des char
    std::string jeu = "templeRUNIMAC";
    std::string anciennePartie = "Recharger ancienne partie (R)";
    std::string voirMeilleursScores = "Voir meilleurs scores (M)";
    std::string jouer = "JOUER (J)";

    //creation des message 
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
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  71, 17, 166));
    SDL_FillRect(ChampTexte, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  255, 255, 255));

    //les messages à afficher sont des char
    std::string entrez = "ENTREZ LE NOM DE VOTRE PARTIE : ";


    //creation des message 
    Entrez = TTF_RenderText_Blended( font, entrez.c_str(), textColor ); 
    NomPartie = TTF_RenderText_Blended( font, nomPartie.c_str(), { 71, 17, 166 } ); 

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

    //taille de la surface du tableau
    fondFenetreTextuelle = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 800, 32, 0, 0, 0, 0);

    //si on veut donner une couleur de fond
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  71, 17, 166));

    //les messages à afficher sont des char
    std::string partieACharger = "CHOISISSEZ LA PARTIE";


    //creation des message 
    PartieACharger = TTF_RenderText_Blended( font, partieACharger.c_str(), textColor ); 

    //on ajoute les messages au tableau
    apply_surface( 20, 50, PartieACharger); 

    for (int i=0; i<anciennesParties.size(); i++){
        SDL_Surface *Partie=NULL;
        //std::string partie = anciennesParties[i].getName();
        std::string partie = "Partie ("+std::to_string(i)+")";
        Partie=TTF_RenderText_Blended(font, partie.c_str(), textColor);
        apply_surface(200,200+100*i, Partie);
    }


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
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  71, 17, 166));

    //les messages à afficher sont des char
    std::string meilleursScores = "MEILLEURS SCORES";
    std::string escape = "(<-- ESC)";


    //creation des message 
    MeilleursScores = TTF_RenderText_Blended( font, meilleursScores.c_str(), textColor ); 
    ESC = TTF_RenderText_Blended(font, escape.c_str(), textColor);

    //on ajoute les messages au tableau
    apply_surface( 20, 50, MeilleursScores); 
    apply_surface( 5, 100, ESC); 

    for (int i=0; i<meilleuresParties.size(); i++){
        SDL_Surface *Partie=NULL;
        //std::string partie = anciennesParties[i].getName() + "SCORE : "+std::to_string(meilleuresParties[i].getScore());
        std::string partie = "Partie ("+std::to_string(i)+") SCORE : "+std::to_string(i*100);
        Partie=TTF_RenderText_Blended(font, partie.c_str(), textColor);
        apply_surface(100,220+100*i, Partie);
    }


    float longueur=1.5;
    float largeur=1.5;
    this->fenetreEnTexture(0, 0,longueur,largeur);
}


void Warning::creation(){
    SDL_FreeSurface( fondFenetreTextuelle ); 
    SDL_Surface *Warning = NULL;
    SDL_Surface *Warning2 = NULL;
    SDL_Surface *Warning3 = NULL;


    //taille de la surface du tableau
    fondFenetreTextuelle = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 800, 32, 0, 0, 0, 0);

    //si on veut donner une couleur de fond
    SDL_FillRect(fondFenetreTextuelle, NULL, SDL_MapRGB(fondFenetreTextuelle->format,  71, 17, 166));

    std::string warning = "CE NOM EXISTE DEJA";
    std::string warning2 = "Ecraser l'ancienne partie ?";
    std::string warning3 = "(O/N)";

    //creation des message 
    Warning = TTF_RenderText_Blended( font, warning.c_str(), textColor ); 
    Warning2 = TTF_RenderText_Blended( font, warning2.c_str(), textColor ); 
    Warning3 = TTF_RenderText_Blended( font, warning3.c_str(), textColor ); 

    //on ajoute les messages au tableau
    apply_surface( 20, 100, Warning); 
    apply_surface( 20, 200, Warning2); 
    apply_surface( 20, 300, Warning3); 

    float longueur=1.5;
    float largeur=1.5;
    this->fenetreEnTexture(0, 0,longueur,largeur);
}

void debut(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            switch(e.type){
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_j){
                        etat=JEU;
                    }
                    if(e.key.keysym.sym == SDLK_r){
                        etat=ANCIENNESPARTIES;
                    }
                    if(e.key.keysym.sym == SDLK_m){
                        etat=MEILLEURSSCORES;
                    }
                    break;
            }
        }

        program.use();
        menu.Draw(program);

        windowManager.swapBuffers();
}

void pause(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_Event e;
    while(windowManager.pollEvent(e)) {
        switch(e.type){
            case SDL_QUIT:
                done = true; // Leave the loop after this iteration
                break;
            case SDL_KEYDOWN:
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    etat=JEU;
                }
                if(e.key.keysym.sym == SDLK_s){
                    //inserer fonction pour sauvegarder
                    etat=SAUVEGARDER;
                }
                if(e.key.keysym.sym == SDLK_r){
                    etat=RECOMMENCER;
                }
                break;
        }
    }

    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/

    program.use();
    menu.Draw(program);

    // Update the display
    windowManager.swapBuffers();
}

void nom(int &etat, Program &program, SDLWindowManager &windowManager, EntrerNomDeLaPartie &menu, bool &done, std::string &nomDePartie){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_Event e;
    program.use();
    SDL_EnableUNICODE(1);
    while(windowManager.pollEvent(e)) {
        switch(e.type){
            case SDL_QUIT:
                done = true; // Leave the loop after this iteration
                break;
            case SDL_KEYDOWN:
                if(e.key.keysym.sym == SDLK_RETURN){
                    std::cout<<nomDePartie<<std::endl;
                    //DONNER LE NOM DE PARTIE A PARTIE
                    // if(){ //si le nom de partie existe déjà
                    //     etat=WARNING;
                    // }
                    etat=DEBUT;
                }
                else{
                    if((e.key.keysym.unicode >= 'a' && e.key.keysym.unicode <= 'z') or  (e.key.keysym.unicode >= 'A' && e.key.keysym.unicode <= 'Z')) {
                        nomDePartie +=char(e.key.keysym.unicode);
                        menu.setNomPartie(nomDePartie);
                        menu.creation();
                        menu.Draw(program);
                        windowManager.swapBuffers();
                    }
                }
                SDL_EnableUNICODE(0);
                break;
        }
    }
        /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/
    // menu.creationEntrerNomDeLaPartie(nomDePartie);
    menu.Draw(program);
    // Update the display
    windowManager.swapBuffers();
}

void warning(int &etat, Program &program, SDLWindowManager &windowManager, Warning &menu, bool &done, std::string &nomDePartie){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SDL_Event e;
    program.use();
    SDL_EnableUNICODE(1);
    while(windowManager.pollEvent(e)) {
        switch(e.type){
            case SDL_QUIT:
                done = true; // Leave the loop after this iteration
                break;
            case SDL_KEYDOWN:
                if(e.key.keysym.sym == SDLK_o){
                    //rechager partie
                    etat=DEBUT;
                }
                if(e.key.keysym.sym == SDLK_n){
                    nomDePartie="";
                    etat=SAUVEGARDER;
                }
                SDL_EnableUNICODE(0);
                break;
        }
    }




    /*********************************
     * HERE SHOULD COME THE RENDERING CODE
     *********************************/
    // menu.creationEntrerNomDeLaPartie(nomDePartie);
    menu.Draw(program);
    // Update the display
    windowManager.swapBuffers();
}

void recharger(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            switch(e.type){
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_a){
                        //on charge la partie 1
                        etat=RECHARGER;
                    }
                    if(e.key.keysym.sym == SDLK_b){
                        //on charge la partie 2
                        etat=RECHARGER;
                    }
                    if(e.key.keysym.sym == SDLK_c){
                        //on charge la partie 3
                        etat=RECHARGER;
                    }
                    break;
            }
        }

        program.use();
        menu.Draw(program);

        windowManager.swapBuffers();
}

void meilleursScores(int &etat, Program &program, SDLWindowManager &windowManager, FenetreTextuelle &menu, bool &done){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            switch(e.type){
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE){
                        //on charge la partie 1
                        etat=DEBUT;
                    }
                    break;
            }
        }

        program.use();
        menu.Draw(program);

        windowManager.swapBuffers();
}