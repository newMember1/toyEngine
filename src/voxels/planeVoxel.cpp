#include "voxels/planeVoxel.h"
#include "core/baseStructures.h"
#include <glad/glad.h>

#include <iostream>
using std::cout;
using std::endl;

PlaneVoxel::PlaneVoxel()
{
    this->startPos = glm::vec3(-1.5, -1, -1.5);

    this->xLen = 3;
    this->yLen = 0.2;
    this->zLen = 3;

    this->xCount = 5;
    this->yCount = 1;
    this->zCount = 5;

    this->deltaX = (1.0f) * xLen / xCount;
    this->deltaY = (1.0f) * yLen / yCount;
    this->deltaZ = (1.0f) * zLen / zCount;

    this->model = glm::mat4(1.0F);
    this->view = globalCamera.GetViewMatrix();
    this->projection = glm::perspective(glm::radians(45.0f), (float)(800)/(float)(600), 0.1f, 100.0f);
    this->boundingBox = std::make_shared<AABB>(startPos, startPos + glm::vec3(xLen, yLen, zLen));

    genVertices();
    genBuffers();
    genShaders();
}

PlaneVoxel::~PlaneVoxel()
{
    
}

bool PlaneVoxel::rayHit(std::shared_ptr<HitRecord> h, std::shared_ptr<Ray> r)
{
    return false;
}

void PlaneVoxel::pushSubVoxelPositions(float xStart, float yStart, float zStart, float xEnd, float yEnd, float zEnd)
{
    int size = positions.size() / 3;

    //1.push positions
    positions.push_back(xStart); positions.push_back(yStart); positions.push_back(zStart);
    positions.push_back(xStart); positions.push_back(yEnd); positions.push_back(zStart);
    positions.push_back(xEnd); positions.push_back(yEnd); positions.push_back(zStart);
    positions.push_back(xEnd); positions.push_back(yStart); positions.push_back(zStart);

    positions.push_back(xStart); positions.push_back(yStart); positions.push_back(zEnd);
    positions.push_back(xStart); positions.push_back(yEnd); positions.push_back(zEnd);
    positions.push_back(xEnd); positions.push_back(yEnd); positions.push_back(zEnd);
    positions.push_back(xEnd); positions.push_back(yStart); positions.push_back(zEnd);

    //push indexes
    //back
    indices.push_back(size + 0); indices.push_back(size + 1); indices.push_back(size + 2);
    indices.push_back(size + 2); indices.push_back(size + 3); indices.push_back(size + 0);

    //front
    indices.push_back(size + 6); indices.push_back(size + 5); indices.push_back(size + 4);
    indices.push_back(size + 4); indices.push_back(size + 7); indices.push_back(size + 6);

    //left
    indices.push_back(size + 4); indices.push_back(size + 5); indices.push_back(size + 1);
    indices.push_back(size + 1); indices.push_back(size + 0); indices.push_back(size + 4);

    //right
    indices.push_back(size + 7); indices.push_back(size + 6); indices.push_back(size + 2);
    indices.push_back(size + 2); indices.push_back(size + 3); indices.push_back(size + 7);

    //top
    indices.push_back(size + 5); indices.push_back(size + 6); indices.push_back(size + 2);
    indices.push_back(size + 2); indices.push_back(size + 1); indices.push_back(size + 5);

    //bottom
    indices.push_back(size + 4); indices.push_back(size + 0); indices.push_back(size + 3);
    indices.push_back(size + 3); indices.push_back(size + 7); indices.push_back(size + 4);
}

void PlaneVoxel::genVertices()
{
    types = vector<int>(xCount * yCount * zCount, 0);

    for(int i = 0; i < xCount; ++i)
        for(int j = 0; j < yCount; ++j)
            for(int k = 0; k < zCount; ++k)
                {
                    types[getIndex(i, j, k)] = 1;
                    float xStart = startPos.x + i * deltaX;
                    float yStart = startPos.y + j * deltaX;
                    float zStart = startPos.z + k * deltaX;

                    float xEnd = xStart + deltaX;
                    float yEnd = yStart + deltaY;
                    float zEnd = zStart + deltaZ;

                    pushSubVoxelPositions(xStart, yStart, zStart, xEnd, yEnd, zEnd);
                }
}

void PlaneVoxel::genBuffers()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), &positions[0], GL_STATIC_DRAW);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
}

void PlaneVoxel::genShaders()
{
    shaderProgram = std::make_shared<Shader>("../shaders/test.vert", "../shaders/test.frag");
    shaderProgram->use();
    shaderProgram->setMat4("model", model);
    shaderProgram->setMat4("view", view);
    shaderProgram->setMat4("projection", projection);
}

void PlaneVoxel::updateModel(float deltaTime, Direction d)
{   
}

void PlaneVoxel::updateModel(glm::mat4 m)
{
    model = m;
    glm::vec3 newStartPos = glm::vec3(model * glm::vec4(startPos, 1.0));
    boundingBox = std::make_shared<AABB>(newStartPos, newStartPos + glm::vec3(xLen, yLen, zLen));
    shaderProgram->use();
    shaderProgram->setMat4("model", model);
}

void PlaneVoxel::updateView(glm::vec2 deltaDirec)
{
}

void PlaneVoxel::move(glm::vec3 deltaMovement, std::vector<std::shared_ptr<VoxelBase> > moveables)
{
    //do nothind here
}

void PlaneVoxel::draw()
{
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    shaderProgram->use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}