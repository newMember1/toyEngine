#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include "environment/sky.h"
#include "core/baseStructures.h"
#include "core/screenMovementsPublisher.h"

using std::shared_ptr;
using std::vector;
class scene
{
public:
    scene(int w, int h, std::shared_ptr<MovePublisher> p);
    void draw(float time);
    void init();

private:
    int sceneTexWidth, sceneTexHeight;
    shared_ptr<MovePublisher> publisher = nullptr;
    shared_ptr<Sky> sky = nullptr;
    vector<shared_ptr<VoxelBase>> staticVoxels;
    vector<shared_ptr<VoxelBase>> moveableVoxels;
};
#endif
