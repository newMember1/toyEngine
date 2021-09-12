#ifndef BASESTRUCTURES_H
#define BASESTRUCTURES_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"

const float PI = 3.1415926;
Camera globalCamera{glm::vec3(0, 0, 3)}; 

enum class direction
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

#endif