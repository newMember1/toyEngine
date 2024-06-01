#include "core/voxelBase.h"
#include <iostream>

int VoxelBase::getIndex(int x, int y, int z)
{
    return xCount * yCount * z + xCount * y + x;
}

void VoxelBase::updateModel(glm::mat4 m)
{
    if(modelLock.try_lock())
    {
        model = m;
        glm::vec3 newStartPos = glm::vec3(model * glm::vec4(startPos, 1.0));
        boundingBox = std::make_shared<AABB>(newStartPos, newStartPos + glm::vec3(xLen, yLen, zLen));

        modelLock.unlock();
    }
}

void VoxelBase::updateView(glm::vec2 deltaDirec)
{
    if(viewLock.try_lock())
    {
        viewLock.unlock();
    }
}

void VoxelBase::processKeyboardInput(ACTION a)
{
    //simple version of move
    glm::vec3 deltaMovement = glm::vec3(0.0f);

    switch (a)
    {
        case ACTION::FRONT: {deltaMovement = glm::vec3(0.0f, 0.0f, -0.03f); break;}
        case ACTION::BACKWARD: {deltaMovement = glm::vec3(0.0f, 0.0f, 0.03f); break;}

        case ACTION::LEFT: {deltaMovement = glm::vec3(-0.03f, 0.0f, 0.0f); break;}
        case ACTION::RIGHT: {deltaMovement = glm::vec3(0.03f, 0.0f, 0.0f);  break;}

        case ACTION::JUMP: {deltaMovement = glm::vec3(0.0f, 0.03f, 0.0f); break;}
        case ACTION::DOWN: {deltaMovement = glm::vec3(0.0f, -0.03f, 0.0f); break;}

        default: break;
    }

    glm::mat4 tmpModel = glm::translate(model, deltaMovement);
    updateModel(tmpModel);
}

// void VoxelBase::updateSpeed(float deltaTime)
// {
//     glm::vec3 attenuation = glm::vec3(3.0f) * deltaTime;

//     //update speed in x direction
//     if(glm::abs(speed.x) > SPEED_EPSLION)
//     {
//         float newXSpeed = speed.x;
//         if(speed.x > 0)
//         {
//             newXSpeed = glm::max(speed.x - attenuation.x, 0.0f);
//         }
//         else
//         {
//             newXSpeed = glm::min(speed.x + attenuation.x, 0.0f);
//         }
//         speed.x = newXSpeed;
//     }

//     //update speed in z direction
//     if(glm::abs(speed.z) > SPEED_EPSLION)
//     {
//         float newZSpeed = speed.z;
//         if(speed.z > 0)
//         {
//             newZSpeed = glm::max(speed.z - attenuation.z, 0.0f);
//         }
//         else
//         {
//             newZSpeed = glm::min(speed.z + attenuation.z, 0.0f);
//         }
//         speed.z = newZSpeed;
//     }

//     //update speed in y direction
//     speed.y = speed.y - G * attenuation.y;
// }