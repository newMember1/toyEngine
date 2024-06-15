#ifndef BASESTRUCTURES_H
#define BASESTRUCTURES_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"
#include <memory>

const float PI = 3.1415926;
const float FLOAT_EPSLION = 1e-6;
const float DISTANCE_EPSLION = 1e-6;
const float SPEED_EPSLION = 1e-6;
const float G = 9.8;

//used for sky atmosphere, all distance here are in kilometers so absorptions cofficient will be in 1/kilomters.
const float EARTHBOTTOMRADIUS = 6360.f;
const float EARTHTOPRADISU = 6420.f;
const float EARTHRAYLEIGHSCALEHEIGHT = 8.0f;
const float EARTHMIESCALEHEIGHT = 1.2f;

static std::shared_ptr<Camera> globalCamera = std::make_shared<Camera>(glm::vec3(0, 15, 25));
static glm::mat4 globalProjection = glm::perspective(glm::radians(45.0f), (float)(800)/(float)(600), 0.1f, 1000.0f);

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

enum class ACTION
{
    FRONT,
    BACKWARD,
    LEFT,
    RIGHT,
    JUMP,
    DOWN,
    NONE
};

enum class MoveState
{
    UP,
    DOWN,
    JUMP,
    RUN,
    WALK,
    FLY,
    NONE,
};

enum class TextureTypes
{
    TWOD,
    THREED,
    CUBEMAP,
};

enum class ChunkTypes
{
    ROCK,
    GRASS,
    WATER,
    WALL,
    DIAMOD,
    NONE,
};

struct TextureMode
{
    struct WrapMode
    {
        unsigned int WRAPS;
        unsigned int WRAPT;
    } wrapmode;

    struct FilterMode
    {
        unsigned int MINFILTER;
        unsigned int MAXFILTER;
    } filtermode;
};

#endif
