#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include "core/baseStructures.h"
#include "core/screenMovementsPublisher.h"
#include "voxels/planeVoxel.h"
#include "voxels/simpleBallVoxel.h"

class scene
{
public:
    scene(int w, int h, std::shared_ptr<ScreenMovementsPublisher> p);
    void draw();
    void init();

private:
    int sceneTexWidth, sceneTexHeight;
    std::shared_ptr<ScreenMovementsPublisher> publisher;
    std::shared_ptr<PlaneVoxel> t = nullptr;
    std::shared_ptr<SimpleBallVoxel> s = nullptr;
};
#endif
