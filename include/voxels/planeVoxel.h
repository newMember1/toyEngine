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
    virtual void updateModel(float deltaTime, direction d) override;
    virtual void updateView(glm::vec2 deltaDirec) override;
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
