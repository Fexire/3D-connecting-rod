#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/Cylinder.hpp"
#include "glimac/Mesh.hpp"

namespace glimac
{

    Mesh Cylinder::build(int nbTriangles)
    {
        Vertex vertex;
        vertex.Normal.x = 0.;
        vertex.Normal.y = 0.;
        vertex.Normal.z = 1.;
        vertex.Position.x = 0;
        vertex.Position.y = 0;
        vertex.Position.z = 1.;
        vertices.emplace_back(vertex);

        float angle = M_2_PI * 10 / nbTriangles;
        for (uint i = 0; i < nbTriangles; i++)
        {
            vertex.Position.x = cos(i * angle);
            vertex.Position.y = sin(i * angle);
            vertices.emplace_back(vertex);
        }

        vertex.Normal.x = 0.;
        vertex.Normal.y = 0.;
        vertex.Normal.z = -1.;
        vertex.Position.x = 0;
        vertex.Position.y = 0;
        vertex.Position.z = -1.;
        vertices.emplace_back(vertex);

        for (uint i = 0; i < nbTriangles; i++)
        {
            vertex.Position.x = cos(i * angle);
            vertex.Position.y = sin(i * angle);
            vertices.emplace_back(vertex);
        }

        vertex.Position.z = -1;
        vertex.Normal.z = 0.;
        for (uint i = 0; i < nbTriangles; i++)
        {
            vertex.Position.x = cos(i * angle);
            vertex.Position.y = sin(i * angle);
            vertex.Normal.x = cos(i * angle);
            vertex.Normal.y = sin(i * angle);
            vertices.emplace_back(vertex);
        }

        vertex.Position.z = 1;
        vertex.Normal.z = 0.;
        for (uint i = 0; i < nbTriangles; i++)
        {
            vertex.Position.x = cos(i * angle);
            vertex.Position.y = sin(i * angle);
            vertex.Normal.x = cos(i * angle);
            vertex.Normal.y = sin(i * angle);
            vertices.emplace_back(vertex);
        }

        indices.emplace_back(0);
        indices.emplace_back(1);
        indices.emplace_back(nbTriangles);
        for (uint i = 1; i < nbTriangles; i++)
        {
            indices.emplace_back(0);
            indices.emplace_back(i);
            indices.emplace_back(i + 1);
        }
    
        indices.emplace_back(nbTriangles + 1);
        indices.emplace_back(nbTriangles + 2);
        indices.emplace_back(nbTriangles + 1 + nbTriangles);
        for (uint i = nbTriangles + 2; i < nbTriangles + 1 + nbTriangles; i++)
        {
            indices.emplace_back(nbTriangles + 1);
            indices.emplace_back(i);
            indices.emplace_back(i + 1);
        }

        uint a = nbTriangles + 2 + nbTriangles;
        indices.emplace_back(a + nbTriangles-1);
        indices.emplace_back(a);
        indices.emplace_back(a + nbTriangles + nbTriangles -1);
        indices.emplace_back(a);
        indices.emplace_back(a + nbTriangles + nbTriangles -1);
        indices.emplace_back(a + nbTriangles);
        for (uint i = nbTriangles + 2 + nbTriangles; i < nbTriangles + 2 + nbTriangles + nbTriangles-1; i++)
        {
            indices.emplace_back(i);
            indices.emplace_back(i + 1);
            indices.emplace_back(i + nbTriangles);
            indices.emplace_back(i + 1);
            indices.emplace_back(i + nbTriangles);
            indices.emplace_back(i + nbTriangles + 1);
        }

        return Mesh(vertices, indices, textures);
    }

}