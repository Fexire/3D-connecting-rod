#pragma once

#include <vector>
#include "SceneStructure.hpp"
#include "Program.hpp"
#include "FreeflyCamera.hpp"

class Rod
{
public:
    Rod(float l,float d,float e)
    {
        glm::mat4 matrix;
        tree =  SceneStructure::generateTree(l,e,glm::rotate(matrix,float(M_PI_2),glm::vec3(0,1,0)) );
        arm = SceneStructure::generateArm(d,e,matrix);
        piston = SceneStructure::generatePiston(e,matrix);
        rail = SceneStructure::generateRail(l,d,e,matrix);
    }

    void draw(Program& program,FreeflyCamera& camera)
    {
        tree.draw(program,camera);
        /*arm.draw(program,camera);
        piston.draw(program,camera);
        rail.draw(program,camera);*/
    }

private:
    SceneStructure tree;

    SceneStructure arm;

    SceneStructure piston;

    SceneStructure rail;
};