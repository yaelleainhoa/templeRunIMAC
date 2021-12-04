
// #include "../include/tableauDeScore.hpp"
// using namespace glimac;


// void TableauDeScore::apply_surface( int x, int y, SDL_Surface* source) { 
// 	SDL_Rect offset; 

// 	offset.x = x; 
// 	offset.y = y;

//     SDL_BlitSurface( source, NULL, fondTableauDeScore, &offset ); 
// }

// void TableauDeScore::tableauEnTexture(float x, float y){
//     glGenBuffers(1,&VBO);
//     glBindBuffer(GL_ARRAY_BUFFER,VBO);
//     Vertex2DUV vertices[]{
//         Vertex2DUV(glm::vec2(-0.5+x,0.25+y),glm::vec2(0.0,0.25)),
//         Vertex2DUV(glm::vec2(0.5+x,0.25+y),glm::vec2(1,0.25)),
//         Vertex2DUV(glm::vec2(0.5+x,0.5+y),glm::vec2(1.0,0.0)),
//         Vertex2DUV(glm::vec2(-0.5+x,0.5+y),glm::vec2(0.0,0.0))
//     };
//     glBufferData(GL_ARRAY_BUFFER,4*sizeof(Vertex2DUV),vertices,GL_STATIC_DRAW);
//     glBindBuffer(GL_ARRAY_BUFFER,0);

//     glGenBuffers(1,&IBO);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//     uint32_t index[]={0,1,2,
//                     0,2,3};
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(uint32_t), index, GL_STATIC_DRAW);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

//     int INDEX_ATTR_POSITION=0;
//     int INDEX_ATTR_TEXTURE=1;
//     glGenVertexArrays(1,&VAO);
//     glBindVertexArray(VAO);
//     glEnableVertexAttribArray(INDEX_ATTR_POSITION);
//     glEnableVertexAttribArray(INDEX_ATTR_TEXTURE);
//     glBindBuffer(GL_ARRAY_BUFFER,VBO);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IBO);
//     glVertexAttribPointer(INDEX_ATTR_POSITION, 2, GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),0);
//     glVertexAttribPointer(INDEX_ATTR_TEXTURE, 2, GL_FLOAT,GL_FALSE,sizeof(Vertex2DUV),(const GLvoid*) (2*sizeof(GLfloat)));
//     glBindBuffer(GL_ARRAY_BUFFER,0);
//     glBindVertexArray(0);

//     glEnable(GL_TEXTURE_2D);
//     glEnable(GL_BLEND);
//     glGenTextures(1, &texture);
//     glBindTexture(GL_TEXTURE_2D, texture);
//     glTexImage2D(GL_TEXTURE_2D, 0, 4, fondTableauDeScore->w, fondTableauDeScore->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, fondTableauDeScore->pixels);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//     glBindTexture(GL_TEXTURE_2D, 0);
// }


// void TableauDeScore::creationTableauDeScore(int score, int meilleurScore, int distance){
//     SDL_FreeSurface( fondTableauDeScore ); 
//     SDL_FreeSurface( indicationDistance ); 
//     SDL_FreeSurface( indicationScore ); 
//     SDL_FreeSurface( indicationMeilleurScore ); 
//     //taille de la surface du tableau
//     fondTableauDeScore = SDL_CreateRGBSurface(SDL_SWSURFACE, 300, 300, 32, 0, 0, 0, 0);

//     //si on veut donner une couleur de fond
//     //SDL_FillRect(fondTableauDeScore, NULL, SDL_MapRGB(fondTableauDeScore->format, 0, 255, 255));

//     //les messages à afficher sont des char
//     std::string strScore = "Score : "+std::to_string(score)+" points";
//     std::string strMeilleurScore = "Meilleur score : "+std::to_string(meilleurScore)+" points";
//     std::string strDistance = "Distance : "+std::to_string(distance)+" (?)";

//     //creation des message 
//     indicationDistance = TTF_RenderText_Blended( font, strDistance.c_str(), textColor ); 
//     indicationScore = TTF_RenderText_Blended( font, strScore.c_str(), textColor ); 
//     indicationMeilleurScore = TTF_RenderText_Blended( font, strMeilleurScore.c_str(), textColor ); 

//     //on ajoute les messages au tableau
//     apply_surface( 20, 20, indicationDistance); 
//     apply_surface( 20, 35, indicationScore); 
//     apply_surface( 20, 50, indicationMeilleurScore); 

//     this->tableauEnTexture(-0.5, 0.5);
// }

// void TableauDeScore::Draw(Program &program){
//     glBindTexture(GL_TEXTURE_2D, texture);
//     glBindVertexArray(VAO);
//     glUniform1i(texture,0);
//     glDrawElements(GL_TRIANGLES, 3*2, GL_UNSIGNED_INT,0);
//     glBindTexture(GL_TEXTURE_2D, 0);
//     glBindVertexArray(0);
// }