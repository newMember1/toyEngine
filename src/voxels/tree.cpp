#include "voxels/tree.h"
#include "core/resourceManager.h"

TreeChunk::TreeChunk()
{
    //generate vertices and VAOs
    genVertices();
    this->model = glm::translate(glm::mat4(1.0F), glm::vec3(0, 3, 0));
    this->view = globalCamera->GetViewMatrix();
    this->projection = globalProjection;
}

bool TreeChunk::rayHit(shared_ptr<HitRecord> h, shared_ptr<Ray> r)
{
    return false;
}

void TreeChunk::genVertices()
{
    //(0, 0, 0) --> (1, 1, 1)
    float vertices[] = {
        //position            //texcoord
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

        0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.0f, 1.0f, 1.0f,  1.0f, 0.0f,

        1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 0.0f,

        0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

        0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        1.0f, 1.0f, 1.0f,  1.0f, 0.0f,
        0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,  0.0f, 1.0f
    };

    //generate trunk vertices
    vector<float> trunkVertices;
    for(int i = 0; i < 3; ++i)
    {
        for(int n = 0; n < 36; ++n)
        {
            trunkVertices.push_back(vertices[5 * n + 0]);
            trunkVertices.push_back(vertices[5 * n + 1] + i);
            trunkVertices.push_back(vertices[5 * n + 2]);
            trunkVertices.push_back(vertices[5 * n + 3]);
            trunkVertices.push_back(vertices[5 * n + 4]);
        }
    }
    glGenVertexArrays(1, &trunkVao);
    glBindVertexArray(trunkVao);
    glGenBuffers(1, &trunkVbo);
    glBindBuffer(GL_ARRAY_BUFFER, trunkVbo);
    glBufferData(GL_ARRAY_BUFFER, trunkVertices.size() * sizeof(float), &trunkVertices[0], GL_STATIC_DRAW);
    // position attritube
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //generate leaves
    vector<float> leavesVertices;
    for(int i = 0; i < 18; ++i)
    {
        for(int n = 0; n < 36; ++n)
        {
            leavesVertices.push_back(vertices[5 * n + 0] + i % 3 - 1);
            leavesVertices.push_back(vertices[5 * n + 1] + (i < 9 ? 3 : 4));
            leavesVertices.push_back(vertices[5 * n + 2] + i % 9 / 3 - 1);
            leavesVertices.push_back(vertices[5 * n + 3]);
            leavesVertices.push_back(vertices[5 * n + 4]);
        }
    }
    glGenVertexArrays(1, &leafVao);
    glBindVertexArray(leafVao);
    glGenBuffers(1, &leafVbo);
    glBindBuffer(GL_ARRAY_BUFFER, leafVbo);
    glBufferData(GL_ARRAY_BUFFER, leavesVertices.size() * sizeof(float), &leavesVertices[0], GL_STATIC_DRAW);
    // position attritube
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

#include <iostream>
using namespace std;
void TreeChunk::draw()
{
    view = globalCamera->GetViewMatrix();
    //draw tree trunk
    //77 49 31
    auto treeTrunkShader = ResourceManager::getInstance().getShader(trunkShader);
    treeTrunkShader->use();
    treeTrunkShader->setVec4("color", glm::vec4(77.0 / 255, 49.0 / 255, 31.0 / 255, 1.0));
    treeTrunkShader->setMat4("model", this->model);
    treeTrunkShader->setMat4("view", this->view);
    treeTrunkShader->setMat4("projection", this->projection);
    glBindVertexArray(trunkVao);
    glDrawArrays(GL_TRIANGLES, 0, 36 * 3);
    glBindVertexArray(0);
    treeTrunkShader->release();

    //draw leaves
    //126 176 58
    auto treeLeavesShader = ResourceManager::getInstance().getShader(leafShader);
    treeLeavesShader->use();
    treeLeavesShader->setVec4("color", glm::vec4(126.0 / 255, 176.0 / 255, 58.0 / 255, 1.0));
    treeLeavesShader->setMat4("model", this->model);
    treeLeavesShader->setMat4("view", this->view);
    treeLeavesShader->setMat4("projection", this->projection);
    glBindVertexArray(leafVao);
    glDrawArrays(GL_TRIANGLES, 0, 36 * 18);
    glBindVertexArray(0);
    treeLeavesShader->release();
}