#ifndef BASESTRUCTURES_H
#define BASESTRUCTURES_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"

const float PI = 3.1415926;
static Camera globalCamera{glm::vec3(0, 0, 3)}; 

class Ray
{
public:
    Ray(glm::vec3 s, glm::vec3 d) { startPos = s; direction = glm::normalize(d); }
    glm::vec3 getStartPos() { return startPos; }
    glm::vec3 getDirection() {return direction; }
    void setStartPos(glm::vec3 s) { startPos = s; }
    void setDirection(glm::vec3 d) { direction = glm::normalize(d); }
private:
    glm::vec3 startPos;
    glm::vec3 direction;
};

class HitRecord
{
public:
    float t = 1e6;
    float minT = 1e-6;
    float maxT = 1e6;
    float u, v;
    float hitPdf = 1;
    float hitRoughnessX;
    float hitRoughnessY;
    glm::vec3 hitPos;
    glm::vec3 hitNormal;
    glm::vec3 hitInDirec;
    glm::vec3 hitOutDirec;
    glm::vec3 hitReflectDirec;
    glm::vec3 hitRefractDirec;

    //for anisotropy
    glm::vec3 xAxis;
    glm::vec3 yAxis;
};

enum class Direction
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

enum class Type{
    AIR,
    STONE
};

#endif
