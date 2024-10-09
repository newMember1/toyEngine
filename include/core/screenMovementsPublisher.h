#ifndef SCREENMOVEMENTSPUBLISHER_H
#define SCREENMOVEMENTSPUBLISHER_H

#include "voxelBase.h"
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

class MovePublisher
{
public:
    void setStaticVoxels(vector<shared_ptr<VoxelBase>> & s)
    {
        staticVoxels = s;
    }

    void processKeyBoardInput(ACTION a)
    {
        notifyAllProcessKeyboardInput(a);
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
    void notifyAllProcessKeyboardInput(ACTION a)
    {
        for(auto obser : moveableObservers)
        {
            obser->processKeyboardInput(a);
        }
    }

private:
    vector<shared_ptr<VoxelBase>> moveableObservers;
    vector<shared_ptr<VoxelBase>> staticVoxels;
};

#endif
