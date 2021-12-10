#pragma once

#include "glm.hpp"
#include "Mesh.hpp"

class SceneObject
{
public:
    SceneObject(Mesh mesh_, glm::mat4 matrix_) : mesh(mesh_), matrix(matrix_)
    {
    }

    void draw(Program& program)
    {   
        mesh.Draw(program);
    }

    ~SceneObject() = default;

private:
    Mesh mesh;
    glm::mat4 matrix;
};