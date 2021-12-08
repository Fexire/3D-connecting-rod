#include "glimac/Room.hpp"


namespace glimac
{
    void Room::LoadMesh(const std::string &filename)
    {

        Assimp::Importer Importer;

        const aiScene *scene = Importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

        InitFromScene(scene, filename);
    }

    void Room::InitFromScene(const aiScene *scene, const std::string &filename)
    {
        m_Entries.resize(scene->mNumMeshes);
        m_Textures.resize(scene->mNumMaterials);

        // Initialize the meshes in the scene one by one
        for (unsigned int i = 0; i < m_Entries.size(); i++)
        {
            const aiMesh *paiMesh = scene->mMeshes[i];
            InitMesh(i, paiMesh);
        }

        InitMaterials(scene, filename);
    }

    void Room::InitMesh(unsigned int Index, const aiMesh *paiMesh)
    {
        m_Entries[Index].materialIndex = paiMesh->mMaterialIndex;

        std::vector<ShapeVertex> vertices;
        std::vector<uint> indices;
        const aiVector3D zero3D(0.0f, 0.0f, 0.0f);

        for (unsigned int i = 0; i < paiMesh->mNumVertices; i++)
        {
            const aiVector3D *pPos = &(paiMesh->mVertices[i]);
            const aiVector3D *pNormal = paiMesh->HasNormals() ? &(paiMesh->mNormals[i]) : &zero3D;
            const aiVector3D *pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &zero3D;

            ShapeVertex v{glm::vec3(pPos->x, pPos->y, pPos->z),
                          glm::vec3(pNormal->x, pNormal->y, pNormal->z),
                          glm::vec2(pTexCoord->x, pTexCoord->y)};

            vertices.push_back(v);
        }
        for (unsigned int i = 0; i < paiMesh->mNumFaces; i++)
        {
            const aiFace &Face = paiMesh->mFaces[i];
            assert(Face.mNumIndices == 3);
            indices.push_back(Face.mIndices[0]);
            indices.push_back(Face.mIndices[1]);
            indices.push_back(Face.mIndices[2]);
        }
        m_Entries[Index].Init(vertices, indices);
    }

    void Room::InitMaterials(const aiScene *pScene, const std::string &Filename)
    {
        for (unsigned int i = 0; i < pScene->mNumMaterials; i++)
        {
            const aiMaterial *pMaterial = pScene->mMaterials[i];
            m_Textures[i] = nullptr;
            if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
            {
                aiString path;

                if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
                {
                    std::string fullPath{"obj"};
                    fullPath.append(path.data);
                    m_Textures[i] = new Texture(fullPath);
                    m_Textures[i]->load();
                }
            }
        }
    }
}