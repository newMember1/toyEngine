#include "core/voxelBase.h"
#include <iostream>

int VoxelBase::getIndex(int x, int y, int z)
{
    return xCount * yCount * z + xCount * y + x;
}

void VoxelBase::setSpeed(ACTION a)
{
    if(a == ACTION::FRONT)
        speed.z = -1;
    else if(a == ACTION::BACKWARD)
        speed.z = 1;
    else if(a == ACTION::LEFT)
        speed.x = -1;
    else if(a == ACTION::RIGHT)
        speed.x = 1;
    else if(a == ACTION::JUMP)
        speed.y = 1;
}

void VoxelBase::updateSpeed(float deltaTime)
{
    glm::vec3 attenuation = glm::vec3(3.0f) * deltaTime;

    //update speed in x direction
    if(glm::abs(speed.x) > SPEED_EPSLION)
    {
        float newXSpeed = speed.x;
        if(speed.x > 0)
        {
            newXSpeed = glm::max(speed.x - attenuation.x, 0.0f);
        }
        else
        {
            newXSpeed = glm::min(speed.x + attenuation.x, 0.0f);
        }
        speed.x = newXSpeed;
    }

    //update speed in z direction
    if(glm::abs(speed.z) > SPEED_EPSLION)
    {
        float newZSpeed = speed.z;
        if(speed.z > 0)
        {
            newZSpeed = glm::max(speed.z - attenuation.z, 0.0f);
        }
        else
        {
            newZSpeed = glm::min(speed.z + attenuation.z, 0.0f);
        }
        speed.z = newZSpeed;
    }

    //update speed in y direction
    speed.y = speed.y - G * attenuation.y;
}
