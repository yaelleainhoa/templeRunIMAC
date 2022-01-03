#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.hpp"

#include <string>
#include <iostream>
#include <map>
#include <vector>
using namespace glimac;

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model 
{
public:
    std::vector<Texture> textures_loaded;	// stocke les texture enregistrées
    std::vector<Mesh>    meshes; //un modele contient plusieurs mesh
    std::string directory; 
    bool gammaCorrection;

    Model(std::string const &path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }

    // dessine les modèles en dessinant tous les mesh
    void Draw(Program &program)
    {
        for(unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(program);
    }
    
private:
    void loadModel(std::string const &path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif
