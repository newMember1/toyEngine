#ifndef SKY_H
#define SKY_H

#include "core/baseStructures.h"
#include "core/shader.h"
#include "utils/ballMesh.h"
#include "utils/circleMesh.h"
#include "environment/sun.h"
#include "environment/atmosphere.h"
#include <memory>

class Sky
{
public:
    void init(glm::vec3 direc);
    void draw(float time);

private:
    std::shared_ptr<Sun> sun = nullptr;
    std::shared_ptr<Atmosphere> atmosphere = nullptr;
    std::shared_ptr<Camera> skyCamera = nullptr;
};


#endif // SKY_H
