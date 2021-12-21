#pragma once

#include "glm.hpp"

class SpotLight
{

public:
    SpotLight() = default;

    ~SpotLight() = default;

    glm::vec4 position;
    glm::vec4 direction;
};