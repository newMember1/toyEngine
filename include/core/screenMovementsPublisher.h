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

    void processKeyBoardInput(ACTION a)
    {
        //update speed
        notifyAllUpdateSpeed(a);
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
    void notifyAllUpdateSpeed(ACTION a)
    {
        //only update objects that can move
        //if hit static objects, we should move it back a little
        for(auto obser : moveableObservers)
        {
            obser->setSpeed(a);
        }
    }

private:
    vector<shared_ptr<VoxelBase>> moveableObservers;
    vector<shared_ptr<VoxelBase>> staticVoxels;
};

#endif
