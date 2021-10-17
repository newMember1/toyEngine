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
    void draw(float time);

private:
    std::shared_ptr<BallMesh> ballMesh = nullptr;
    std::shared_ptr<Shader> atmosphereShader = nullptr;

    //for atmosphere's rendering
    unsigned int skyVAO, skyVBO, skyEBO;
    glm::mat4 skyBallModel, skyBallView, skyBallProjection;
    glm::mat4 sunModel, sunView, sunProjection;
    std::shared_ptr<Camera> skyCamera = nullptr;
    glm::vec3 sunDirec;

    void update(float time);
    void initSkyMesh();
};


#endif // SKY_H
