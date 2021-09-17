#ifndef SIMPLEBALLVOXEL_H
#define SIMPLEBALLVOXEL_H

#include <vector>
#include <memory>
#include "core/shader.h"
#include "core/voxelBase.h"

using std::vector;
using std::shared_ptr;

class SimpleBallVoxel : public VoxelBase
{
public:
    SimpleBallVoxel();
    virtual ~SimpleBallVoxel();
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
    glm::vec3 center;
    float radius;
    float deltaX, deltaY, deltaZ;
    float speed = 1.0;
};

#endif // SIMPLEBALLVOXEL_H
