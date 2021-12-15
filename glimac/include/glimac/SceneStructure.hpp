#pragma once

#include "SceneObject.hpp"
#include "Cube.hpp"
#include "Cylinder.hpp"
#include <vector>

class SceneStructure
{
public:
    SceneStructure() = default;

    ~SceneStructure() = default;

    static SceneStructure generateTree(float l, float e, glm::mat4 structureMatrix)
    {
        SceneStructure structure;
        Cube cube;
        glm::mat4 matrix(1);
        matrix = glm::scale(matrix, glm::vec3(e, e, e));
        matrix = glm::translate(matrix, glm::vec3(-l / 2, 0, 0));
        structure.objects.emplace_back(cube.build(), matrix);
        matrix = glm::translate(matrix, glm::vec3(l, 0, 0));
        structure.objects.emplace_back(cube.build(), matrix);
        Cylinder cylinder;
        matrix = glm::mat4(1);
        matrix = glm::scale(matrix, glm::vec3(l, 1, 1));
        matrix = glm::rotate(matrix, float(M_PI_2), glm::vec3(0, 1, 0));
        structure.objects.emplace_back(cylinder.build(100), matrix);
        structure.matrix = structureMatrix;
        return structure;
    }

    static SceneStructure generateArm(float d, float e, glm::mat4 structureMatrix)
    {
        SceneStructure structure;
        Cube cube;
        glm::mat4 matrix(1);
        matrix = glm::scale(matrix, glm::vec3(d / 2, d / 2, 2 * e));
        
        matrix = glm::translate(matrix, glm::vec3((-3 * (d / 4)) / (d / 2), 0, 0));
        structure.objects.emplace_back(cube.build(), matrix);
        matrix = glm::mat4(1);
        matrix = glm::scale(matrix, glm::vec3(d + d / 2, 2 * e, e));
        matrix = glm::translate(matrix, glm::vec3((d / 4) / (3 * (d / 2)), 0, e / 2 / e));
        structure.objects.emplace_back(cube.build(), matrix);
        Cylinder cylinder;
        matrix = glm::mat4(1);
        matrix = glm::scale(matrix, glm::vec3(e, e, e));
        matrix = glm::translate(matrix, glm::vec3(0, 0, -e / 2 / e));
        structure.objects.emplace_back(cylinder.build(6), matrix);
        matrix = glm::mat4(1);
        matrix = glm::scale(matrix, glm::vec3(e, e, e));
        matrix = glm::translate(matrix, glm::vec3(d / e, 0, -e / 2 / e));
        structure.objects.emplace_back(cylinder.build(6), matrix);
        structure.matrix = structureMatrix;
        return structure;
    }

    static SceneStructure generatePiston(float e, glm::mat4 structureMatrix)
    {
        SceneStructure structure;
        Cube cube;
        glm::mat4 matrix(1);
        matrix = glm::scale(matrix, glm::vec3(2 * e, e / 4, 3 * e));
        matrix = glm::translate(matrix, glm::vec3(0, e / (e / 4), 0));
        structure.objects.emplace_back(cube.build(), matrix);
        matrix = glm::mat4(1);
        matrix = glm::scale(matrix, glm::vec3(2 * e, e / 4, 3 * e));
        matrix = glm::translate(matrix, glm::vec3(0, -e / (e / 4), 0));
        structure.objects.emplace_back(cube.build(), matrix);
        matrix = glm::mat4(1);
        matrix = glm::scale(matrix, glm::vec3(2 * e, 2 * e, e));
        matrix = glm::translate(matrix, glm::vec3(0, 0, 0));
        
        structure.objects.emplace_back(cube.build(), matrix);
        structure.matrix = structureMatrix;
        return structure;
    }

    static SceneStructure generateRail(float l, float d, float e, glm::mat4 structureMatrix)
    {
        SceneStructure structure;
        Cube cube;
        glm::mat4 matrix(1);
        matrix = glm::scale(matrix, glm::vec3(l + d + 2 * e, 2 * e, e));
        structure.objects.emplace_back(cube.build(), matrix);
        structure.matrix = structureMatrix;
        return structure;
    }

    void draw(Program &program, FreeflyCamera &camera)
    {
        for (auto &object : objects)
        {
            object.draw(program,matrix, camera);
        }
    }

private:
    std::vector<SceneObject> objects;
    glm::mat4 matrix;
};