#ifndef SKY_H
#define SKY_H

#include "core/baseStructures.h"
#include "core/shader.h"
#include "utils/ballMesh.h"
#include <memory>

class Sky
{
public:
    Sky();
    void draw();

private:
    std::shared_ptr<BallMesh> ballMesh = nullptr;
    std::shared_ptr<Shader> skyMeshShader = nullptr;
    unsigned int skyVAO, skyVBO, skyEBO;

    void initSkyMesh();
};


#endif // SKY_H
