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

    void notifyAllUpdateModel(float deltaTime, Direction d)
    {
        //only update objects that can move
        //if hit static objects, we should move it back a little
        for(auto obser : moveableObservers)
        {
//            obser->updateModel(deltaTime, d);
//            if(obser->voxelOverlap(staticVoxels[0]))
//                std::cout<<"hit"<<std::endl;
//            else
//                std::cout<<"not hit"<<std::endl;
            if(obser->moveAble == false)
                continue;
            glm::vec3 deltaMovement;
            float distance = obser->speed * deltaTime;
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
            obser->move(deltaMovement, staticVoxels);
        }
    }

    vector<shared_ptr<VoxelBase>> moveableObservers;
    vector<shared_ptr<VoxelBase>> staticVoxels;
};

#endif
