#pragma once 

#include "glm.hpp"

class TrackballCamera
{

    public:

    TrackballCamera() = default;

    void moveFront(float delta) 
    {
        m_fDistance += delta;
    }

    void rotateLeft(float degrees) 
    {
        m_fAngleY += degrees;
    }

    void rotateup(float degrees) 
    {
        m_fAngleX += degrees;
    }

    glm::mat4 getViewMatrix() const
    {
        glm::mat4 viewMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -m_fDistance));
        viewMatrix = glm::rotate(viewMatrix,float(m_fAngleX*M_PI/180),glm::vec3(1,0,0));
        viewMatrix = glm::rotate(viewMatrix,float(m_fAngleY*M_PI/180),glm::vec3(0,1,0));
        return viewMatrix;
    }

    private:
    float m_fDistance = 5.f;
    float m_fAngleX = 0.f;
    float m_fAngleY = 0.f;
};