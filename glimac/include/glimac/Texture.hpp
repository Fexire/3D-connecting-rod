#pragma once

#include <string>
#include <string_view>
#include "glimac/Image.hpp"
#include <iostream>


class Texture
{
    public:
    Texture(std::string& path_):path(path_){};

    ~Texture();

    void load()
    {
        auto cloudTexture = glimac::loadImage(path);
        if (cloudTexture == NULL)
        {
            std::cerr << "failed to load texture" + path << std::endl;
        }
    }

    private :
    std::string path;


};