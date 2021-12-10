#pragma once

#include <vector>

#include "Mesh.hpp"

namespace glimac
{
    // canonic cube
    class Cube
    {
    public:
        Cube() = default;

        Mesh build();

    private:

        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;
    };

}