#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <iostream>

#include <glimac/Shader.hpp>
#include <glimac/Image.hpp>
#include <glimac/vertex.hpp>

#include "texture.hpp"
#include "variablesGlobales.hpp"


using namespace glimac;

//un modele est composé de plusieurs mesh on va dessiner mesh par mesh
class Mesh {
    public:
        std::vector<ShapeVertex>  vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<ShapeVertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
            :vertices(vertices), indices(indices), textures(textures){creerBuffers_mesh();};
        void Draw(Program &program);

        void destroy()
            {
                glDeleteVertexArrays(1, &VAO);
                glDeleteBuffers(1, &VBO);
                glDeleteBuffers(1, &EBO);
            }

        
    private:
        unsigned int VAO, VBO, EBO;

        void creerBuffers_mesh();
};  

#endif