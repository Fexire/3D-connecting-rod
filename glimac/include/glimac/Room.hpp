#pragma once

#include <string>
#include <vector>
#include "common.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "glimac/Texture.hpp"

//glfw

namespace glimac{
class Room
{

    public :
        Room() = default;
        ~Room() = default;
        void LoadMesh(const std::string& Filename);


    private :
        void InitFromScene(const aiScene* scene, const std::string& Filename);
        void InitMesh(unsigned int index, const aiMesh* paiMesh);
        void InitMaterials(const aiScene* scene, const std::string& Filename);
        
        struct Mesh {
            Mesh();

            ~Mesh();

            bool Init(const std::vector<ShapeVertex> &vertices,
            const std::vector<uint> &indices);

            GLuint vbo;
            GLuint ibo;
            uint numIndices;
            uint materialIndex;
        };

        std::vector<Mesh> m_Entries;
        std::vector<Texture *> m_Textures;
};
}