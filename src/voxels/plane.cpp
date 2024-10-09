#include "voxels/plane.h"
#include "core/baseStructures.h"
#include "core/resourceManager.h"
#include <glad/glad.h>

#include <stdlib.h>

void PlaneVoxel::generateHeightMap()
{
    for(int i = 0; i < this->xCount; ++i)
    {
        for(int j = 0; j < this->zCount; ++j)
        {
            heightMaps.push_back(rand() % (this->yCount - 1) + 1);
        }
    }
}

PlaneVoxel::PlaneVoxel(int xc, int yc, int zc)
{
    //TODO remove hardcode start pos
    this->xCount = xc;
    this->yCount = yc;
    this->zCount = zc;

    glm::mat4 m(1.0f);

    this->model = m;
    this->view = globalCamera->GetViewMatrix();
    this->projection = globalProjection;

    shaderName = "texture";
    generateHeightMap();
    genVertices();
    genBuffers();
}

PlaneVoxel::~PlaneVoxel()
{
}

bool PlaneVoxel::rayHit(std::shared_ptr<HitRecord> h, std::shared_ptr<Ray> r)
{
    return false;
}

void PlaneVoxel::genVertices()
{
    /*
    * 1 0.666413 0.250594
    * 2 0.333587 0.250594
    * 3 0.333587 0.000975
    * 4 0.666413 0.000975
    * 5 0.666413 0.500213
    * 6 0.666413 0.749833
    * 7 0.333587 0.749833
    * 8 0.333587 0.500214
    * 9 0.000761 0.500214
    * 10 0.000761 0.749833
    * 11 0.333587 0.999452
    * 12 0.666413 0.999452
    * 13 0.999239 0.500213
    * 14 0.999239 0.749833
    */

    //(0, 0, 0) --> (1, 1, 1)
    float vertices[] = {
        //position            //texcoord
        //back face
        0.0f, 0.0f, 0.0f,  0.333587, 0.999452,  //11
        1.0f, 0.0f, 0.0f,  0.666413, 0.999452,  //12
        1.0f, 1.0f, 0.0f,  0.666413, 0.749833,  //6
        1.0f, 1.0f, 0.0f,  0.666413, 0.749833,  //6
        0.0f, 1.0f, 0.0f,  0.333587, 0.749833,  //7
        0.0f, 0.0f, 0.0f,  0.333587, 0.999452,  //11

        //front face
        0.0f, 0.0f, 1.0f,  0.333587, 0.250594,  //2
        1.0f, 0.0f, 1.0f,  0.666413, 0.250594,  //1
        1.0f, 1.0f, 1.0f,  0.666413, 0.500213,  //5
        1.0f, 1.0f, 1.0f,  0.666413, 0.500213,  //5
        0.0f, 1.0f, 1.0f,  0.333587, 0.500214,  //8
        0.0f, 0.0f, 1.0f,  0.333587, 0.250594,  //2

        //left face
        0.0f, 1.0f, 1.0f,  0.333587, 0.500214,  //8
        0.0f, 1.0f, 0.0f,  0.333587, 0.749833,  //7
        0.0f, 0.0f, 0.0f,  0.000761, 0.749833,  //10
        0.0f, 0.0f, 0.0f,  0.000761, 0.749833,  //10
        0.0f, 0.0f, 1.0f,  0.000761, 0.500214,  //9
        0.0f, 1.0f, 1.0f,  0.333587, 0.500214,  //8

        //right face
        1.0f, 1.0f, 1.0f,  0.666413, 0.500213,  //5
        1.0f, 1.0f, 0.0f,  0.666413, 0.749833,  //6
        1.0f, 0.0f, 0.0f,  0.999239, 0.749833,  //14
        1.0f, 0.0f, 0.0f,  0.999239, 0.749833,  //14
        1.0f, 0.0f, 1.0f,  0.999239, 0.500213,  //134
        1.0f, 1.0f, 1.0f,  0.666413, 0.500213,  //5

        //bottom face
        0.0f, 0.0f, 0.0f,  0.333587, 0.000975,  //3
        1.0f, 0.0f, 0.0f,  0.666413, 0.000975,  //4
        1.0f, 0.0f, 1.0f,  0.666413, 0.250594,  //1
        1.0f, 0.0f, 1.0f,  0.666413, 0.250594,  //1
        0.0f, 0.0f, 1.0f,  0.333587, 0.250594,  //2
        0.0f, 0.0f, 0.0f,  0.333587, 0.000975,  //3

        //up face
        0.0f, 1.0f, 0.0f,  0.333587 ,0.749833,  //7
        1.0f, 1.0f, 0.0f,  0.666413, 0.749833,  //6
        1.0f, 1.0f, 1.0f,  0.666413, 0.500213,  //5
        1.0f, 1.0f, 1.0f,  0.666413, 0.500213,  //5
        0.0f, 1.0f, 1.0f,  0.333587, 0.500214,  //8
        0.0f, 1.0f, 0.0f,  0.333587, 0.749833,  //7
    };

    //generate vertices based on the heightmaps, here all chunks are GRASS!!!
    types = vector<int>(xCount * yCount * zCount, 0);

    for(int i = 0; i < xCount; ++i)
    {
        for(int k = 0; k < zCount; ++k)
        {
            int h = heightMaps[i * zCount + k];
            for(int j = 0; j < h; ++j)
            {
                for(int n = 0; n < 36; ++n)
                {
                    planeVertices.push_back(vertices[5 * n + 0] + i - (xCount / 2.0f));
                    planeVertices.push_back(vertices[5 * n + 1] + j);
                    planeVertices.push_back(vertices[5 * n + 2] + k - (zCount / 2.0f));
                    planeVertices.push_back(vertices[5 * n + 3]);
                    planeVertices.push_back(vertices[5 * n + 4]);
                }
            }
        }
    }
}

void PlaneVoxel::genBuffers()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, planeVertices.size() * sizeof(float), &planeVertices[0], GL_STATIC_DRAW);

    // position attritube
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void PlaneVoxel::draw()
{
    view = globalCamera->GetViewMatrix();

    //draw grass
    auto grassShader = ResourceManager::getInstance().getShader(shaderName);
    auto grassTex = ResourceManager::getInstance().getTexture("grass");
    grassTex->use();
    grassShader->use();
    grassShader->setMat4("model", model);
    grassShader->setMat4("view", view);
    grassShader->setMat4("projection", projection);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, planeVertices.size() / 5);
    glBindVertexArray(0);
    grassShader->release();
    grassTex->release();
}
