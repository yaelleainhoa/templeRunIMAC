#pragma once

#include <GL/glew.h>
#include "glm.hpp"
#include "Shader.hpp"
#include "Program.hpp"
#include <vector>
#include "glimac/vertex.hpp"
#include "glimac/texture.hpp"

namespace glimac {

class Mesh {
    public:
        // data
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
        //  render data
        unsigned int VAO, VBO, EBO;

        void creerBuffers_mesh();
};  

}
