#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include "core/baseStructures.h"
#include "core/screenMovementsPublisher.h"
#include "voxels/planeVoxel.h"
#include "voxels/simpleBallVoxel.h"
#include "environment/sky.h"

using std::shared_ptr;
using std::vector;
class scene
{
public:
    scene(int w, int h, std::shared_ptr<ScreenMovementsPublisher> p);
    void draw(float time);
    void init();

private:
    void moveVoxels(float time);

    int sceneTexWidth, sceneTexHeight;
    shared_ptr<ScreenMovementsPublisher> publisher = nullptr;
    shared_ptr<Sky> sky = nullptr;
    vector<shared_ptr<VoxelBase>> staticVoxels;
    vector<shared_ptr<VoxelBase>> moveableVoxels;
};
#endif
