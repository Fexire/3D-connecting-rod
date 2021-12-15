#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/Cube.hpp"
#include "glimac/Mesh.hpp"

namespace glimac
{

    Mesh Cube::build()
    {
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

        for (GLuint i = 0; i < vertices.size(); i+=4)
        {
            indices.emplace_back(i);
            indices.emplace_back(i+1);
            indices.emplace_back(i+2);
            indices.emplace_back(i);
            indices.emplace_back(i+2);
            indices.emplace_back(i+3);
        }

        return Mesh(vertices,indices,textures);
    }

}