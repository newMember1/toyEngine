#include "environment/sky.h"

Sky::Sky()
{
    ballMesh = std::make_shared<BallMesh>(9);
    initSkyMesh();
}

void Sky::initSkyMesh()
{
    auto points = ballMesh->getPoints();
    auto indices = ballMesh->getIndices();

    skyMeshShader = std::make_shared<Shader>("../shaders/skyMesh.vert", "../shaders/skyMesh.frag");
    skyMeshShader->use();
    skyMeshShader->setMat4("model", glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

    glGenVertexArrays(1, &skyVAO);
    glGenBuffers(1, &skyVBO);
    glGenBuffers(1, &skyEBO);
    glBindVertexArray(skyVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() *sizeof(float), &points[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Sky::draw()
{
    skyMeshShader->use();
    glBindVertexArray(skyVAO);
    glDrawElements(GL_TRIANGLES, ballMesh->getIndices().size(), GL_UNSIGNED_INT, 0);
}
