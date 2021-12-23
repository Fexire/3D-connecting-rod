#pragma once

#include <vector>
#include "SceneStructure.hpp"
#include "Program.hpp"
#include "FreeflyCamera.hpp"

class Rod
{
public:
    Rod(float l_, float d_, float e_) : l(l_), d(d_), e(e_)
    {
        generateRod();
    }

    void generateRod()
    {
        glm::mat4 treeMatrix;
        treeMatrix = glm::rotate(treeMatrix, float(M_PI), glm::vec3(0, 0, 1));
        treeMatrix = glm::translate(treeMatrix, glm::vec3(-(-((l + d + e) / 2) + d + l), -5, 3 * e));
        tree = SceneStructure::generateTree(l, e, treeMatrix);
        glm::mat4 matrix;
        arm = SceneStructure::generateArm(d, e, glm::translate(matrix, glm::vec3(-((l + d + e) / 2), 5, e + e / 2)));
        piston = SceneStructure::generatePiston(e, glm::translate(matrix, glm::vec3(-((l + d + e) / 2) + d + l, 5, e)));
        rail = SceneStructure::generateRail(l, d, e, glm::translate(matrix, glm::vec3(0,5,0)));
        resetToState();
    }

    void draw(Program &program, FreeflyCamera &camera)
    {
        if (run)
        {
            update();
        }
        tree.draw(program, camera);
        arm.draw(program, camera);
        piston.draw(program, camera);
        rail.draw(program, camera);
    }

    void update()
    {
        alpha += rotationStep;
        if (alpha > M_PI * 2)
        {
            alpha = alpha - (M_PI * 2);
        }
        glm::mat4 armMatrix = arm.getMatrix();
        arm.setMatrix(armMatrix * glm::rotate(glm::mat4(1), rotationStep, glm::vec3(0, 0, 1)));
        float newBeta = asin((-sin(alpha) * d) / l);
        float newBx = (cos(alpha) * d + cos(beta) * l) - d - l;
        glm::mat4 treeMatrix = tree.getMatrix();
        treeMatrix = glm::translate(glm::mat4(1), glm::vec3(newBx - Bx, 0, 0)) * treeMatrix;
        treeMatrix = glm::rotate(treeMatrix, newBeta - beta, glm::vec3(0, 0, 1));
        tree.setMatrix(treeMatrix);
        glm::mat4 pistonMatrix = piston.getMatrix();
        pistonMatrix = glm::translate(pistonMatrix, glm::vec3(newBx - Bx, 0, 0));
        piston.setMatrix(pistonMatrix);
        beta = newBeta;
        Bx = newBx;
    }

    void runStopUpdate()
    {
        run = !run;
    }

    void speedUp()
    {
        rotationStep += 0.01;
    }

    void speedDown()
    {
        rotationStep -= 0.01;
        if (rotationStep < 0)
        {
            rotationStep = 0;
        }
    }

    void thicknessUp()
    {
        e += 0.2;
        generateRod();
    }

    void thicknessDown()
    {
        e -= 0.2;
        if (e < 0.1)
        {
            e = 0.2;
        }
        generateRod();
    }

    void armLengthUp()
    {
        d += 0.2;
        generateRod();
    }

    void armLengthDown()
    {
        d -= 0.2;
        if (d < 0.1)
        {
            d = 0.2;
        }
        generateRod();
    }

    void treeLengthUp()
    {
        l += 0.2;
        generateRod();
    }

    void treeLengthDown()
    {
        l -= 0.2;
        if (l < 0.1)
        {
            l = 0.2;
        }
        generateRod();
    }

    const glm::mat4 getTreeMatrix()
    {
        return tree.getMatrix();
    }

    float midAB()
    {
        return l / 2.;
    }

private:
    void resetToState()
    {
        glm::mat4 armMatrix = arm.getMatrix();
        arm.setMatrix(armMatrix * glm::rotate(glm::mat4(1), alpha, glm::vec3(0, 0, 1)));
        float newBeta = asin((-sin(alpha) * d) / l);
        float newBx = (cos(alpha) * d + cos(beta) * l) - d - l;
        glm::mat4 treeMatrix = tree.getMatrix();
        treeMatrix = glm::translate(glm::mat4(1), glm::vec3(newBx, 0, 0)) * treeMatrix;
        treeMatrix = glm::rotate(treeMatrix, newBeta, glm::vec3(0, 0, 1));
        tree.setMatrix(treeMatrix);
        glm::mat4 pistonMatrix = piston.getMatrix();
        pistonMatrix = glm::translate(pistonMatrix, glm::vec3(newBx, 0, 0));
        piston.setMatrix(pistonMatrix);
        beta = newBeta;
        Bx = newBx;
    }

    float alpha = 0;
    float beta = 0;
    float rotationStep = 0.01;
    float Bx = 0;
    float l;
    float d;
    float e;
    bool run = false;
    SceneStructure tree;
    SceneStructure arm;
    SceneStructure piston;
    SceneStructure rail;
};