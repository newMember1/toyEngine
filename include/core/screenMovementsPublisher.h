#ifndef SCREENMOVEMENTSPUBLISHER_H
#define SCREENMOVEMENTSPUBLISHER_H

#include "voxelBase.h"
#include <vector>
#include <memory>

class ScreenMovementsPublisher
{
public:
    void processKeyBoardInput(float deltaTime, direction d)
    {
        //handel objects model matrix
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

    void notifyAllUpdateModel(float deltaTime, direction d)
    {
        //only update objects that can move 
        for(auto obser : moveableObservers)
            obser->updateModel(deltaTime, d); 
    }

    std::vector<std::shared_ptr<VoxelBase>> moveableObservers; //only stores moveable object
};

#endif
