#ifndef TEST_H
#define TEST_H

#include "core/voxelBase.h"
#include <memory>
#include <vector>
#include <string>

using std::vector;
using std::shared_ptr;

class PlaneVoxel : public VoxelBase
{
public:
    PlaneVoxel();
    virtual ~PlaneVoxel();
    virtual bool rayHit(std::shared_ptr<HitRecord> h, std::shared_ptr<Ray> r) override;
    virtual void draw() override;

private:
    void genVertices();
    void genBuffers();
    void pushSubVoxelPositions(float xStart, float yStart, float zStart, float xEnd, float yEnd, float zEnd);

    vector<float> positions;
    vector<int> indices;

    std::string shaderName;
    float deltaX, deltaY, deltaZ;
};
#endif
