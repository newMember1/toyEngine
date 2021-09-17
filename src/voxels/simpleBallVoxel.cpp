#include "voxels/simpleBallVoxel.h"

SimpleBallVoxel::SimpleBallVoxel()
{
    radius = 0.3;
    this->startPos = glm::vec3(-0.5, -0.7, -1);
    float len = radius * 2 * sqrt(3);
    this->center = this->startPos + glm::vec3(len / 2);
    this->xLen = len;
    this->yLen = len;
    this->zLen = len;

    this->xCount = 50;
    this->yCount = 50;
    this->zCount = 50;

    this->deltaX = xLen / xCount;
    this->deltaY = yLen / yCount;
    this->deltaZ = zLen / zCount;

    this->model = glm::mat4(1.0F);
    this->view = globalCamera.GetViewMatrix();
    this->projection = glm::perspective(glm::radians(45.0f), (float)(800)/(float)(600), 0.1f, 100.0f);

    genVertices();
    genBuffers();
    genShaders();
}

SimpleBallVoxel::~SimpleBallVoxel()
{}

void SimpleBallVoxel::updateView(glm::vec2 deltaDirec)
{}

void SimpleBallVoxel::updateModel(float deltaTime, direction d)
{
    std::cout<<"delta time: "<<deltaTime<<std::endl;
    if(d == direction::BACKWARD)
        faceDirection = glm::vec3(0, 0, -1);
    if(d == direction::FORWARD)
        faceDirection = glm::vec3(0, 0, 1);
    if(d == direction::LEFT)
        faceDirection = glm::vec3(-1, 0, 0);
    if(d == direction::RIGHT)
        faceDirection = glm::vec3(1, 0, 0);
    model = glm::translate(model, speed * deltaTime * glm::vec3(faceDirection));
    shaderProgram->use();
    shaderProgram->setMat4("model", model);
}

void SimpleBallVoxel::draw()
{
    shaderProgram->use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void SimpleBallVoxel::pushSubVoxelPositions(float xStart, float yStart, float zStart, float xEnd, float yEnd, float zEnd)
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

void SimpleBallVoxel::genVertices()
{
    types = vector<int>(xCount * yCount * zCount, 0);
    for(int i = 0; i < xCount; ++i)
        for(int j = 0; j < yCount; ++j)
            for(int k = 0; k < zCount; ++k)
            {
                float xStart = startPos.x + i * deltaX;
                float yStart = startPos.y + j * deltaX;
                float zStart = startPos.z + k * deltaX;

                float xEnd = xStart + deltaX;
                float yEnd = yStart + deltaY;
                float zEnd = zStart + deltaZ;

                float xMid = (xStart + xEnd) / 2;
                float yMid = (yStart + yEnd) / 2;
                float zMid = (zStart + zEnd) / 2;

                if(glm::dot(glm::vec3(xMid, yMid, zMid) - center, glm::vec3(xMid, yMid, zMid) - center) <= radius * radius)
                {
                    types[getIndex(i, j, k)] = 1;
                    pushSubVoxelPositions(xStart, yStart, zStart, xEnd, yEnd, zEnd);
                }
            }
}

void SimpleBallVoxel::genBuffers()
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

void SimpleBallVoxel::genShaders()
{
    shaderProgram = std::make_shared<Shader>("../shaders/test.vert", "../shaders/test.frag");
    shaderProgram->use();
    shaderProgram->setMat4("model", model);
    shaderProgram->setMat4("view", view);
    shaderProgram->setMat4("projection", projection);
}
