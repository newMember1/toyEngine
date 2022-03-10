#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H

#include "core/baseStructures.h"
#include "utils/ballMesh.h"
#include "utils/circleMesh.h"
#include <memory>

using std::shared_ptr;

class Atmosphere
{
public:
    void init(shared_ptr<Camera> cam);
    void setSunDirec(glm::vec3 direc);
    void draw(float time);

private:
    void update(float time);
    glm::mat4 model{1.0f};
    glm::mat4 view{1.0f};
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)(800)/(float)(600), 0.0f, 100.0f);;
    glm::vec3 sunDirec;

    unsigned int vao;
    unsigned int ebo;
    unsigned int vbo;

    std::string shaderName;
    shared_ptr<BallMesh> atmoMesh = nullptr;
    shared_ptr<Camera> camera = nullptr;
};

#endif // ATMOSPHERE_H
