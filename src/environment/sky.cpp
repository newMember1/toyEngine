#include "environment/sky.h"

Sky::Sky()
{
    skyCamera = std::make_shared<Camera>(glm::vec3(0.0f, 0.99, 0.0f));
    ballMesh = std::make_shared<BallMesh>(10);
    initSky();
    initSun();
}

void Sky::initSky()
{
    auto points = ballMesh->getPoints();
    auto indices = ballMesh->getIndices();

    //atmosphere
    atmosphereShader = std::make_shared<Shader>("../shaders/atmosphere.vert", "../shaders/atmosphere.frag");
    atmosphereShader->use();
    skyBallModel = glm::mat4(1.0f);
    skyBallView = skyCamera->GetViewMatrix();
    skyBallProjection = glm::perspective(glm::radians(60.0f), (float)(800)/(float)(600), 0.0f, 10.0f);
    sunDirec = glm::vec3(1, -1, 1);

    atmosphereShader->setMat4("model", skyBallModel);
    atmosphereShader->setMat4("view", skyBallView);
    atmosphereShader->setMat4("projection", skyBallProjection);
    atmosphereShader->setVec3("sunDirec", sunDirec);

    glGenVertexArrays(1, &skyVAO);
    glGenBuffers(1, &skyVBO);
    glGenBuffers(1, &skyEBO);
    glBindVertexArray(skyVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Sky::initSun()
{
    auto points = ballMesh->getPoints();
    auto indices = ballMesh->getIndices();

    sunShader = std::make_shared<Shader>("../shaders/constColor.vert", "../shaders/constColor.frag");
    sunShader->use();
    sunModel = glm::mat4(1.0f);
    sunView = skyCamera->GetViewMatrix();
    sunProjection = glm::perspective(glm::radians(60.0f), (float)(800)/(float)(600), 0.0f, 10.0f);

    sunShader->setMat4("model", sunModel);
    sunShader->setMat4("view", sunModel);
    sunShader->setMat4("projection", sunModel);

    glGenVertexArrays(1, &sunVAO);
    glGenBuffers(1, &sunVBO);
    glGenBuffers(1, &sunEBO);
    glBindVertexArray(sunVAO);
    glBindBuffer(GL_ARRAY_BUFFER, sunVBO);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sunEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Sky::update(float time)
{
    sunModel = glm::rotate(sunModel, glm::radians(time / 10), glm::vec3(-1, 0, 1));
    sunDirec = glm::vec3(sunModel * glm::vec4(sunDirec, 1.0f));
    sunDirec.x += glm::sin(10 * time);
    atmosphereShader->use();
    atmosphereShader->setVec3("sunDirec", sunDirec);
    atmosphereShader->release();
}

void Sky::draw(float time)
{
    update(time);

    atmosphereShader->use();
    glBindVertexArray(skyVAO);
    glDrawElements(GL_TRIANGLES, ballMesh->getIndices().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    atmosphereShader->release();

    sunShader->use();
    glBindVertexArray(sunVAO);
    glDrawElements(GL_TRIANGLES, circleMesh->getIndices().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    sunShader->release();
}
