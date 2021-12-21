#pragma once

#include "glm.hpp"

class FreeflyCamera
{
public:

    FreeflyCamera()
    {
        computeDirectionVectors();
    }

    void moveLeft(float t)
    {
        m_Position += t * m_LeftVector;
    } 
    
    void moveFront(float t)
    {
        m_Position += t * m_FrontVector;
    } 

    void rotateLeft(float degrees)
    {
        m_fPhi += degrees*M_PI/180;
        computeDirectionVectors();
    }
    
    void rotateUp(float degrees)
    {
        m_fTheta += degrees*M_PI/180;
        computeDirectionVectors();
    }

    void computeDirectionVectors()
    {
        m_FrontVector = glm::vec3{cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * cos(m_fPhi)};
        m_LeftVector = glm::vec3{sin(m_fPhi + M_PI_2), 0, cos(m_fPhi + M_PI_2)};
        m_UpVector = glm::cross(m_FrontVector,m_LeftVector);
    }

    glm::mat4 getViewMatrix() const
    {   
        return glm::lookAt(m_Position, m_Position + m_FrontVector,m_UpVector);
    }

    glm::vec3& getPosition()
    {
        return m_Position;
    }

    glm::vec3& getFrontVector()
    {
        return m_FrontVector;
    }

private:
    glm::vec3 m_Position{0,0,10};
    float m_fPhi = M_PI;
    float m_fTheta = 0;
    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;
};