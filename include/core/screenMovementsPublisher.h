#ifndef SCREENMOVEMENTSPUBLISHER_H
#define SCREENMOVEMENTSPUBLISHER_H

#include "voxelBase.h"
#include <vector>
#include <memory>
#include <iostream>

using std::vector;
using std::shared_ptr;

class ScreenMovementsPublisher
{
public:
    void setStaticVoxels(vector<shared_ptr<VoxelBase>> & s)
    {
        staticVoxels = s;
    }

    void processKeyBoardInput(float deltaTime, Direction d)
    {
        //handel objects model matrix
        notifyAllUpdateModel(deltaTime, d);
    }

    void processMouseInput(glm::vec2 deltaDirec)
    {
        //process camera's view
        //this will change camera's view
    }

    void attach(std::shared_ptr<VoxelBase> moveableObserver)
    {
        moveableObservers.push_back(moveableObserver);
    }

private:
    void notifyAllUpdateModel(float deltaTime, Direction d)
    {
        //only update objects that can move
        //if hit static objects, we should move it back a little
        for(auto obser : moveableObservers)
        {
            glm::vec3 deltaMovement;
            float distance = obser->moveSpeed * deltaTime;
            if(d == Direction::BACKWARD)
            {
                deltaMovement = -distance * obser->frontDirection;
            }
            if(d == Direction::FORWARD)
            {
                deltaMovement = distance * obser->frontDirection;
            }
            if(d == Direction::LEFT)
            {
                deltaMovement = distance * obser->leftDirection;
            }
            if(d == Direction::RIGHT)
            {
                deltaMovement = -distance * obser->leftDirection;
            }
            if(d == Direction::UP)
            {
                deltaMovement = distance * glm::vec3(0, 1, 0);
            }
            if(d == Direction::DOWN)
            {
                deltaMovement = -distance * glm::vec3(0, 1, 0);
            }
            obser->move(deltaMovement, staticVoxels);
        }
    }

    vector<shared_ptr<VoxelBase>> moveableObservers;
    vector<shared_ptr<VoxelBase>> staticVoxels;
};

#endif
