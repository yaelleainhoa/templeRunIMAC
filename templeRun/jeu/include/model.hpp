#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glimac/Image.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../include/mesh.hpp"
#include <glimac/Shader.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace glimac;

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model 
{
public:
    // model data 
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh>    meshes;
    std::string directory;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model.
    Model(std::string const &path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }

    // draws the model, and thus all its meshes
    void Draw(Program &program)
    {
        for(unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(program);
    }

    void destroy(){
         for(unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].destroy();
    }
    
private:
    void loadModel(std::string const &path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif

