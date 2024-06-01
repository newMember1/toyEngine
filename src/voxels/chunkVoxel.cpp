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
        default:
            return "none";
    }
}

ChunkVoxel::ChunkVoxel(ChunkTypes type)
{
    this->startPos = glm::vec3(-0.5, -0.7, -1);

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

ChunkVoxel::~ChunkVoxel()
{
}

void ChunkVoxel::genVertices()
{
    float vertices[] = {
        //position            //texcoord
        -0.05f, -0.05f, -0.05f,  0.0f, 0.0f,
         0.05f, -0.05f, -0.05f,  1.0f, 0.0f,
         0.05f,  0.05f, -0.05f,  1.0f, 1.0f,
         0.05f,  0.05f, -0.05f,  1.0f, 1.0f,
        -0.05f,  0.05f, -0.05f,  0.0f, 1.0f,
        -0.05f, -0.05f, -0.05f,  0.0f, 0.0f,

        -0.05f, -0.05f,  0.05f,  0.0f, 0.0f,
         0.05f, -0.05f,  0.05f,  1.0f, 0.0f,
         0.05f,  0.05f,  0.05f,  1.0f, 1.0f,
         0.05f,  0.05f,  0.05f,  1.0f, 1.0f,
        -0.05f,  0.05f,  0.05f,  0.0f, 1.0f,
        -0.05f, -0.05f,  0.05f,  0.0f, 0.0f,

        -0.05f,  0.05f,  0.05f,  1.0f, 0.0f,
        -0.05f,  0.05f, -0.05f,  1.0f, 1.0f,
        -0.05f, -0.05f, -0.05f,  0.0f, 1.0f,
        -0.05f, -0.05f, -0.05f,  0.0f, 1.0f,
        -0.05f, -0.05f,  0.05f,  0.0f, 0.0f,
        -0.05f,  0.05f,  0.05f,  1.0f, 0.0f,

         0.05f,  0.05f,  0.05f,  1.0f, 0.0f,
         0.05f,  0.05f, -0.05f,  1.0f, 1.0f,
         0.05f, -0.05f, -0.05f,  0.0f, 1.0f,
         0.05f, -0.05f, -0.05f,  0.0f, 1.0f,
         0.05f, -0.05f,  0.05f,  0.0f, 0.0f,
         0.05f,  0.05f,  0.05f,  1.0f, 0.0f,

        -0.05f, -0.05f, -0.05f,  0.0f, 1.0f,
         0.05f, -0.05f, -0.05f,  1.0f, 1.0f,
         0.05f, -0.05f,  0.05f,  1.0f, 0.0f,
         0.05f, -0.05f,  0.05f,  1.0f, 0.0f,
        -0.05f, -0.05f,  0.05f,  0.0f, 0.0f,
        -0.05f, -0.05f, -0.05f,  0.0f, 1.0f,

        -0.05f,  0.05f, -0.05f,  0.0f, 1.0f,
         0.05f,  0.05f, -0.05f,  1.0f, 1.0f,
         0.05f,  0.05f,  0.05f,  1.0f, 0.0f,
         0.05f,  0.05f,  0.05f,  1.0f, 0.0f,
        -0.05f,  0.05f,  0.05f,  0.0f, 0.0f,
        -0.05f,  0.05f, -0.05f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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