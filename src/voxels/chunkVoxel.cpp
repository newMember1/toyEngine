#include "voxels/chunkVoxel.h"
#include "core/resourceManager.h"

#ifdef DEBUG
#include <iostream>
using std::cout;
using std::endl;
#endif

string ChunkVoxel::getTextureName(ChunkTypes type)
{
    switch(type)
    {
        case ChunkTypes::ROCK:
            return "rock";
        case ChunkTypes::GRASS:
            return "grass";
        case ChunkTypes::WATER:
            return "water";
        case ChunkTypes::DIAMOD:
            return "diamond";
        case ChunkTypes::WALL:
            return "wall";
        default:
            return "none";
    }
}

ChunkVoxel::ChunkVoxel(ChunkTypes type)
{
    this->startPos = glm::vec3(-0.6, -0.7, -1);

    this->xLen = 1;
    this->yLen = 1;
    this->zLen = 1;

    this->xCount = 1;
    this->yCount = 1;
    this->zCount = 1;

    this->model = glm::mat4(1.0F);
    this->view = globalCamera->GetViewMatrix();
    this->projection = globalProjection;

    this->boundingBox = std::make_shared<AABB>(startPos, startPos + glm::vec3(xLen, yLen, zLen));

    this->genVertices();

    this->chunkType = type;
    this->shaderName = "texture";
    this->textureName = getTextureName(chunkType);
}

ChunkVoxel::ChunkVoxel(ChunkTypes type, string sName, glm::mat4 m, glm::vec3 sPos, int xc, int yc, int zc)
{
    this->startPos = sPos;
    this->xCount = xc;
    this->yCount = yc;
    this->zCount = zc;

    this->model = m;
    this->view = globalCamera->GetViewMatrix();
    this->projection = globalProjection;
    this->shaderName = sName;
    this->chunkType = type;
    this->textureName = getTextureName(type);

    this->genVertices();
    this->boundingBox = std::make_shared<AABB>(sPos, sPos + glm::vec3(xc, yc, zc));
}

ChunkVoxel::~ChunkVoxel()
{
}

void ChunkVoxel::genVertices()
{
    //(0, 0, 0) --> (1, 1, 1)
    float vertices[] = {
        //position            //texcoord
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        0.0f,  1.0f, 0.0f,  0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        0.0f, 0.0f,  1.0f,  0.0f, 0.0f,
        1.0f, 0.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 1.0f,
        0.0f,  1.0f,  1.0f,  0.0f, 1.0f,
        0.0f, 0.0f,  1.0f,  0.0f, 0.0f,

        0.0f,  1.0f,  1.0f,  1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.0f, 0.0f,  1.0f,  0.0f, 0.0f,
        0.0f,  1.0f,  1.0f,  1.0f, 0.0f,

        1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 0.0f,  1.0f,  0.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 0.0f,

        0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        1.0f, 0.0f,  1.0f,  1.0f, 0.0f,
        1.0f, 0.0f,  1.0f,  1.0f, 0.0f,
        0.0f, 0.0f,  1.0f,  0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

        0.0f,  1.0f, 0.0f,  0.0f, 1.0f,
        1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,  1.0f, 0.0f,
        0.0f,  1.0f,  1.0f,  0.0f, 0.0f,
        0.0f,  1.0f, 0.0f,  0.0f, 1.0f
    };

    assert(xCount >= 1 & yCount >= 1 && zCount >= 1);

    int cubes = xCount * yCount * zCount;
    int faces = cubes * 6;
    int verts = faces * 6;
    int vsize = verts * 5;
    vector<float> newVertices;
    for(int i = 0; i < xCount; ++i)
    {
        for(int j = 0; j < yCount; ++j)
        {
            for(int k = 0; k < zCount; ++k)
            {
                for (int n = 0; n < 36; ++n)
                {
                    newVertices.push_back(vertices[5 * n + 0] + i);
                    newVertices.push_back(vertices[5 * n + 1] + j);
                    newVertices.push_back(vertices[5 * n + 2] + k);
                    newVertices.push_back(vertices[5 * n + 3]);
                    newVertices.push_back(vertices[5 * n + 4]);
                }
            }
        }
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vsize * sizeof(float), &newVertices[0], GL_STATIC_DRAW);

    // position attritube
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

bool ChunkVoxel::rayHit(std::shared_ptr<HitRecord> h, std::shared_ptr<Ray> r)
{
    return false;
}

void ChunkVoxel::draw()
{
    auto shader = ResourceManager::getInstance().getShader(shaderName);
    shader->use();
    shader->setInt("tex", 0);
    shader->setMat4("model", model);
    shader->setMat4("view", view);
    shader->setMat4("projection", projection);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    shader->release();
}