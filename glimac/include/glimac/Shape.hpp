#pragma once

#include "Mesh.hpp"

class Shape
{
    public :
    static Mesh buildCube()
    {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;
        Vertex vertex;
        vertex.Normal.x = 0.;
        vertex.Normal.y = 0.;
        vertex.Normal.z = -1.;
        vertex.Position.x = -0.5;
        vertex.Position.y = -0.5;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = -0.5;
        vertex.Position.y = 0.5;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = 0.5;
        vertex.Position.y = 0.5;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = 0.5;
        vertex.Position.y = -0.5;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);

        vertex.Normal.x = 0.;
        vertex.Normal.y = 0.;
        vertex.Normal.z = 1.;
        vertex.Position.x = -0.5;
        vertex.Position.y = -0.5;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = -0.5;
        vertex.Position.y = 0.5;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = 0.5;
        vertex.Position.y = 0.5;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = 0.5;
        vertex.Position.y = -0.5;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);

        vertex.Normal.x = -1.;
        vertex.Normal.y = 0.;
        vertex.Normal.z = 0.;
        vertex.Position.x = -0.5;
        vertex.Position.y = -0.5;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = -0.5;
        vertex.Position.y = 0.5;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = -0.5;
        vertex.Position.y = 0.5;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = -0.5;
        vertex.Position.y = -0.5;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);

        vertex.Normal.x = 1.;
        vertex.Normal.y = 0.;
        vertex.Normal.z = 0.;
        vertex.Position.x = 0.5;
        vertex.Position.y = -0.5;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = 0.5;
        vertex.Position.y = 0.5;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = 0.5;
        vertex.Position.y = 0.5;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = 0.5;
        vertex.Position.y = -0.5;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);

        vertex.Normal.x = 0;
        vertex.Normal.y = -1;
        vertex.Normal.z = 0.;
        vertex.Position.x = -0.5;
        vertex.Position.y = -0.5;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = -0.5;
        vertex.Position.y = -0.5;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = 0.5;
        vertex.Position.y = -0.5;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = 0.5;
        vertex.Position.y = -0.5;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);

        vertex.Normal.x = 0;
        vertex.Normal.y = 1;
        vertex.Normal.z = 0.;
        vertex.Position.x = -0.5;
        vertex.Position.y = 0.5;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = -0.5;
        vertex.Position.y = 0.5;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = 0.5;
        vertex.Position.y = 0.5;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);
        vertex.Position.x = 0.5;
        vertex.Position.y = 0.5;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);

        for (GLuint i = 0; i < vertices.size(); i += 4)
        {
            indices.emplace_back(i);
            indices.emplace_back(i + 1);
            indices.emplace_back(i + 2);
            indices.emplace_back(i);
            indices.emplace_back(i + 2);
            indices.emplace_back(i + 3);
        }

        return Mesh(vertices, indices, textures);
    }

    static Mesh buildCylinder(int nbTriangles, bool semi)
    {
        std::vector<Vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Texture> textures;

        float angle = M_2_PI * 10 / nbTriangles;
        if (semi)
        {
            angle = M_PI / nbTriangles;
            nbTriangles = nbTriangles + 1;
        }

        Vertex vertex;
        vertex.Normal.x = 0.;
        vertex.Normal.y = 0.;
        vertex.Normal.z = 1.;
        vertex.Position.x = 0;
        vertex.Position.y = 0;
        vertex.Position.z = 0.5;
        vertices.emplace_back(vertex);

        for (uint i = 0; i < nbTriangles; i++)
        {
            vertex.Position.x = cos(i * angle) / 2.;
            vertex.Position.y = sin(i * angle) / 2.;
            vertices.emplace_back(vertex);
        }

        vertex.Normal.x = 0.;
        vertex.Normal.y = 0.;
        vertex.Normal.z = -1.;
        vertex.Position.x = 0;
        vertex.Position.y = 0;
        vertex.Position.z = -0.5;
        vertices.emplace_back(vertex);

        for (uint i = 0; i < nbTriangles; i++)
        {
            vertex.Position.x = cos(i * angle) / 2.;
            vertex.Position.y = sin(i * angle) / 2.;
            vertices.emplace_back(vertex);
        }

        vertex.Position.z = -0.5;
        vertex.Normal.z = 0.;
        for (uint i = 0; i < nbTriangles; i++)
        {
            vertex.Position.x = cos(i * angle) / 2.;
            vertex.Position.y = sin(i * angle) / 2.;
            vertex.Normal.x = cos(i * angle);
            vertex.Normal.y = sin(i * angle);
            vertices.emplace_back(vertex);
        }

        vertex.Position.z = 0.5;
        vertex.Normal.z = 0.;
        for (uint i = 0; i < nbTriangles; i++)
        {
            vertex.Position.x = cos(i * angle) / 2.;
            vertex.Position.y = sin(i * angle) / 2.;
            vertex.Normal.x = cos(i * angle);
            vertex.Normal.y = sin(i * angle);
            vertices.emplace_back(vertex);
        }

        if (semi)
        {
            vertex.Normal.x = 0;
            vertex.Normal.y = -1;
            vertex.Normal.z = 0.;
            vertex.Position.z = -0.5;
            vertex.Position.x = cos((nbTriangles - 1) * angle) / 2.;
            vertex.Position.y = sin((nbTriangles - 1) * angle) / 2.;
            vertices.emplace_back(vertex);
            vertex.Position.z = 0.5;
            vertices.emplace_back(vertex);
            vertex.Position.z = -0.5;
            vertex.Position.x = cos(0 * angle) / 2.;
            vertex.Position.y = sin(0 * angle) / 2.;
            vertices.emplace_back(vertex);
            vertex.Position.z = 0.5;
            vertices.emplace_back(vertex);
        }

        if (!semi)
        {
            indices.emplace_back(0);
            indices.emplace_back(1);
            indices.emplace_back(nbTriangles);
        }

        for (uint i = 1; i < nbTriangles; i++)
        {
            indices.emplace_back(0);
            indices.emplace_back(i);
            indices.emplace_back(i + 1);
        }
        if (!semi)
        {
            indices.emplace_back(nbTriangles + 1);
            indices.emplace_back(nbTriangles + 2);
            indices.emplace_back(nbTriangles + 1 + nbTriangles);
        }
        for (uint i = nbTriangles + 2; i < nbTriangles + 1 + nbTriangles; i++)
        {
            indices.emplace_back(nbTriangles + 1);
            indices.emplace_back(i);
            indices.emplace_back(i + 1);
        }

        if (semi)
        {
            indices.emplace_back(vertices.size() - 1);
            indices.emplace_back(vertices.size() - 2);
            indices.emplace_back(vertices.size() - 3);
            indices.emplace_back(vertices.size() - 3);
            indices.emplace_back(vertices.size() - 2);
            indices.emplace_back(vertices.size() - 4);
        }
        else
        {
            uint a = nbTriangles + 2 + nbTriangles;
            indices.emplace_back(a + nbTriangles - 1);
            indices.emplace_back(a);
            indices.emplace_back(a + nbTriangles + nbTriangles - 1);
            indices.emplace_back(a);
            indices.emplace_back(a + nbTriangles + nbTriangles - 1);
            indices.emplace_back(a + nbTriangles);
        }
        for (uint i = nbTriangles + 2 + nbTriangles; i < nbTriangles + 2 + nbTriangles + nbTriangles - 1; i++)
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
};
