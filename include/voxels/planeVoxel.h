#ifndef TEST_H
#define TEST_H

#include "core/shader.h"
#include "core/voxelBase.h"
#include <memory>
#include <vector>

using std::vector;
using std::shared_ptr;

class PlaneVoxel : public VoxelBase
{
public:
    PlaneVoxel();
    virtual ~PlaneVoxel();
    virtual void updateModel(glm::mat4 m) override;
    virtual void updateView(glm::vec2 deltaDirec) override;
    virtual bool rayHit(std::shared_ptr<HitRecord> h, std::shared_ptr<Ray> r) override;
    virtual void move(float deltaTime, std::vector<std::shared_ptr<VoxelBase> > staticVoxels) override;
    virtual void draw() override;

private:
    void genVertices();
    void genBuffers();
    void genShaders();
    void pushSubVoxelPositions(float xStart, float yStart, float zStart, float xEnd, float yEnd, float zEnd);

    vector<float> positions;
    vector<int> indices;

    shared_ptr<Shader> shaderProgram = nullptr;

    float deltaX, deltaY, deltaZ;
};
#endif
