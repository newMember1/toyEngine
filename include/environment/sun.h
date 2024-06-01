#ifndef SUN_H
#define SUN_H
#include "core/baseStructures.h"
#include "utils/ballMesh.h"
#include "utils/circleMesh.h"
#include <memory>
#include <string>

using std::shared_ptr;

class Sun
{
public:
    void init(glm::vec3 direc);
    void draw(float time);
    glm::vec3 getSunDirec();

private:
    void update(float time);

    glm::mat4 model{1.0f};
    glm::mat4 view{1.0f};
    glm::mat4 projection{1.0f};

    glm::vec3 sunDirec;

    unsigned int sunVAO;
    unsigned int sunEBO;
    unsigned int sunVBO;

    std::string shaderName;
    shared_ptr<BallMesh> sunMesh = nullptr;
};

#endif // SUN_H
