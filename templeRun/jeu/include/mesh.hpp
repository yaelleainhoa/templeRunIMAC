#pragma once

#include <vector>
#include <iostream>

#include <glimac/Shader.hpp>
#include <glimac/Image.hpp>
#include <glimac/vertex.hpp>

#include "../include/texture.hpp"


using namespace glimac;

class Mesh {
    public:
        // data
        std::vector<ShapeVertex>  vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<ShapeVertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
            :vertices(vertices), indices(indices), textures(textures){creerBuffers_mesh();};
        void Draw(Program &program, glm::mat4 &model, glm::mat4 view, glm::mat4 proj);

        void destroy()
            {
                glDeleteVertexArrays(1, &VAO);
                glDeleteBuffers(1, &VBO);
                glDeleteBuffers(1, &EBO);
            }

        
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void creerBuffers_mesh();
};  

