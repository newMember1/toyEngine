#ifndef SKY_H
#define SKY_H

#include "core/baseStructures.h"
#include "core/shader.h"
#include "utils/ballMesh.h"
#include "utils/circleMesh.h"
#include <memory>

class Sky
{
public:
    Sky();
    void draw(float time);

private:
    std::shared_ptr<Camera> skyCamera = nullptr;
    glm::vec3 sunDirec;

    //for atmosphere's rendering
    unsigned int skyVAO, skyVBO, skyEBO;
    glm::mat4 skyBallModel, skyBallView, skyBallProjection;
    std::shared_ptr<BallMesh> ballMesh = nullptr;
    std::shared_ptr<Shader> atmosphereShader = nullptr;

    //for sun's rendering
    unsigned int sunVAO, sunVBO, sunEBO;
    glm::mat4 sunModel, sunView, sunProjection;
    std::shared_ptr<CircleMesh> circleMesh = nullptr;
    std::shared_ptr<Shader> sunShader = nullptr;

    void update(float time);
    void initSky();
    void initSun();
};


#endif // SKY_H
