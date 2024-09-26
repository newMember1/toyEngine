#ifndef TEST_H
#define TEST_H

#include "core/voxelBase.h"
#include "voxels/chunkVoxel.h"
#include <memory>
#include <vector>
#include <string>

using std::vector;
using std::shared_ptr;

class PlaneVoxel : public VoxelBase
{
public:
    PlaneVoxel() = delete;
    PlaneVoxel(int xc, int yc, int zc);
    virtual ~PlaneVoxel();
    virtual bool rayHit(std::shared_ptr<HitRecord> h, std::shared_ptr<Ray> r) override;
    virtual void draw() override;

private:
    void generateHeightMap();
    void genVertices();
    void genBuffers();

    vector<float> heightMaps;
    vector<float> planeVertices;

    std::string shaderName;
    float deltaX, deltaY, deltaZ;
};
#endif
