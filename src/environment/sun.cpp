#include "environment/sun.h"
#include "core/resourceManager.h"

void Sun::init(glm::vec3 direc)
{
    //1.sun direction and position
    sunDirec = glm::normalize(direc);
    model = glm::scale(model, glm::vec3(0.1));
    model = glm::translate(model, -12.0f * sunDirec);
    view = globalCamera->GetViewMatrix();
    projection = globalProjection;

    //2.sun mesh
    sunMesh = std::make_shared<BallMesh>(10);
    auto points = sunMesh->getPoints();
    auto indices = sunMesh->getIndices();

    //3.VAO
    glGenVertexArrays(1, &sunVAO);
    glGenBuffers(1, &sunVBO);
    glGenBuffers(1, &sunEBO);
    glBindVertexArray(sunVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sunEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glBindVertexArray(0);

    //4.sun shader
    shaderName = "sun";
    auto sunShader = ResourceManager::getInstance().getShader(shaderName);
    sunShader->use();
    sunShader->setMat4("model", model);
    sunShader->setMat4("view", view);
    sunShader->setMat4("projection", projection);
    sunShader->release();
}

void Sun::draw(float time)
{
    auto sunShader = ResourceManager::getInstance().getShader(shaderName);
    sunShader->use();
    glBindVertexArray(sunVAO);
    glDrawElements(GL_TRIANGLES, sunMesh->getIndices().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    sunShader->release();

    update(time);
}

void Sun::update(float time)
{
    auto sunShader = ResourceManager::getInstance().getShader(shaderName);
    //need to update model matrix and sunDirec
    glm::mat4 rot = glm::rotate(glm::mat4{1.0f}, time / 2, glm::vec3(0, 0, 1));
    model = rot * model;
    sunDirec = glm::vec3(rot * glm::vec4(sunDirec, 1.0f));
    sunShader->use();
    sunShader->setMat4("model", model);
    sunShader->release();
}

glm::vec3 Sun::getSunDirec()
{
    return sunDirec;
}
