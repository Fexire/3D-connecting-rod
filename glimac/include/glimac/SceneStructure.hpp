#pragma once

#include "SceneObject.hpp"
#include "Shape.hpp"
#include <vector>

class SceneStructure
{
public:
    SceneStructure() = default;

    ~SceneStructure() = default;

    static SceneStructure generateTree(float l, float e, glm::mat4 structureMatrix)
    {
        SceneStructure structure;
        glm::mat4 matrix(1);
        matrix = glm::scale(matrix, glm::vec3(e, e, e));
        structure.objects.emplace_back(Shape::buildCube(), matrix);
        matrix = glm::mat4(1);
        matrix = glm::translate(matrix, glm::vec3(l, 0, 0));
        matrix = glm::scale(matrix, glm::vec3(e, e, e));
        structure.objects.emplace_back(Shape::buildCube(), matrix);
        matrix = glm::mat4(1);
        matrix = glm::translate(matrix, glm::vec3(l / 2, 0, 0));
        matrix = glm::scale(matrix, glm::vec3(l, e / 2, e / 2));
        matrix = glm::rotate(matrix, float(M_PI_2), glm::vec3(0, 1, 0));
        structure.objects.emplace_back(Shape::buildCylinder(100, false), matrix);
        structure.matrix = structureMatrix;
        return structure;
    }

    static SceneStructure generateArm(float d, float e, glm::mat4 structureMatrix)
    {
        SceneStructure structure;
        glm::mat4 matrix(1);
        matrix = glm::translate(matrix, glm::vec3((-3 * (d / 4)), 0, 0));
        matrix = glm::scale(matrix, glm::vec3(d / 2, d / 2, 2 * e));
        structure.objects.emplace_back(Shape::buildCube(), matrix);
        matrix = glm::mat4(1);
        matrix = glm::translate(matrix, glm::vec3(d / 4, 0, -e / 2));
        matrix = glm::scale(matrix, glm::vec3(d + d / 2, 2 * e, e));
        structure.objects.emplace_back(Shape::buildCube(), matrix);
        matrix = glm::mat4(1);
        matrix = glm::translate(matrix, glm::vec3(0, 0, e / 2));
        matrix = glm::scale(matrix, glm::vec3(e, e, e));
        structure.objects.emplace_back(Shape::buildCylinder(6, false), matrix);
        matrix = glm::mat4(1);
        matrix = glm::translate(matrix, glm::vec3(d, 0, e / 2));
        matrix = glm::scale(matrix, glm::vec3(e, e, e));
        structure.objects.emplace_back(Shape::buildCylinder(6, false), matrix);
        matrix = glm::mat4(1);
        matrix = glm::translate(matrix, glm::vec3(d, 0, -e / 2));
        matrix = glm::scale(matrix, glm::vec3(2 * e, 2 * e, e));
        matrix = glm::rotate(matrix, float(-M_PI_2), glm::vec3(0, 0, 1));
        structure.objects.emplace_back(Shape::buildCylinder(50, true), matrix);

        structure.matrix = structureMatrix;
        return structure;
    }

    static SceneStructure generatePiston(float e, glm::mat4 structureMatrix)
    {
        SceneStructure structure;
        glm::mat4 matrix(1);
        matrix = glm::translate(matrix, glm::vec3(0, e + e / 4 / 2, 0));
        matrix = glm::scale(matrix, glm::vec3(2 * e, e / 4, 3 * e));
        structure.objects.emplace_back(Shape::buildCube(), matrix);
        matrix = glm::mat4(1);
        matrix = glm::translate(matrix, glm::vec3(0, -e - e / 4 / 2, 0));
        matrix = glm::scale(matrix, glm::vec3(2 * e, e / 4, 3 * e));
        structure.objects.emplace_back(Shape::buildCube(), matrix);
        matrix = glm::mat4(1);
        matrix = glm::scale(matrix, glm::vec3(2 * e, 2 * e, e));
        structure.objects.emplace_back(Shape::buildCube(), matrix);
        structure.matrix = structureMatrix;
        return structure;
    }

    static SceneStructure generateRail(float l, float d, float e, glm::mat4 structureMatrix)
    {
        SceneStructure structure;
        glm::mat4 matrix(1);
        matrix = glm::scale(matrix, glm::vec3(l + d + 2 * e, 2 * e, e));
        structure.objects.emplace_back(Shape::buildCube(), matrix);
        matrix = glm::mat4(1);
        matrix = glm::translate(matrix, glm::vec3((l + d + 2 * e) / 2, 0, 0));
        matrix = glm::scale(matrix, glm::vec3(2 * e, 2 * e, e));
        matrix = glm::rotate(matrix, float(-M_PI_2), glm::vec3(0, 0, 1));
        structure.objects.emplace_back(Shape::buildCylinder(50, true), matrix);
        matrix = glm::mat4(1);
        matrix = glm::translate(matrix, glm::vec3(-(l + d + 2 * e) / 2, 0, 0));
        matrix = glm::scale(matrix, glm::vec3(2 * e, 2 * e, e));
        matrix = glm::rotate(matrix, float(M_PI_2), glm::vec3(0, 0, 1));
        structure.objects.emplace_back(Shape::buildCylinder(50, true), matrix);
        structure.matrix = structureMatrix;
        return structure;
    }

    void draw(Program &program, FreeflyCamera &camera)
    {
        for (auto &object : objects)
        {
            object.draw(program, matrix, camera);
        }
    }

    void setMatrix(glm::mat4 newMatrix)
    {
        matrix = newMatrix;
    }

    const glm::mat4 &getMatrix()
    {
        return matrix;
    }

private:
    std::vector<SceneObject> objects;
    glm::mat4 matrix;
};