#pragma once

#include <vector>

#include "Mesh.hpp"

namespace glimac
{
    // canonic cube
    class Cylinder
    {
    public:
        Cylinder() = default;

        Mesh build(int nbTriangles);

    private:

        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;
    };

}