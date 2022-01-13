#include "environment/atmosphere.h"

void Atmosphere::init(shared_ptr<Camera> cam)
{
    camera = cam;
    sunDirec = glm::vec3(1, -1, 1);

    //1.matrix config
    view = camera->GetViewMatrix();

    //2.atmosphere mesh
    atmoMesh = std::make_shared<BallMesh>(10);
    auto points = atmoMesh->getPoints();
    auto indices = atmoMesh->getIndices();

    //3.VAO
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glBindVertexArray(0);

    //4.shader
    atmoShader = std::make_shared<Shader>("../shaders/atmosphere.vert", "../shaders/atmosphere.frag");
    atmoShader->use();
    atmoShader->setMat4("model", model);
    atmoShader->setMat4("view", view);
    atmoShader->setMat4("projection", projection);
    atmoShader->setVec3("sunDirec", sunDirec);
    atmoShader->release();
}

void Atmosphere::setSunDirec(glm::vec3 direc)
{
    sunDirec = direc;
    atmoShader->use();
    atmoShader->setVec3("sunDirec", sunDirec);
}

void Atmosphere::draw(float time)
{
    atmoShader->use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, atmoMesh->getIndices().size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    atmoShader->release();

    update(time);
}

void Atmosphere::update(float time)
{

}
