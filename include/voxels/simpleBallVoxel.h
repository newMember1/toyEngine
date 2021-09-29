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
    virtual bool rayHit(shared_ptr<HitRecord> h, shared_ptr<Ray> r) override;
    virtual void updateModel(glm::mat4 m) override;
    virtual void updateView(glm::vec2 deltaDirec) override;
    virtual void move(float deltaTime, std::vector<std::shared_ptr<VoxelBase> > staticVoxls) override;
    virtual void setSpeed(ACTION a) override;
    virtual void draw() override;

private:
    void genVertices();
    void genBuffers();
    void genShaders();
    void pushSubVoxelPositions(float xStart, float yStart, float zStart, float xEnd, float yEnd, float zEnd);
    float getPenetration(int i, int j, int k, shared_ptr<VoxelBase> voxel, glm::vec3 startPos, glm::vec3 endPos);
    bool voxelOverlap(shared_ptr<VoxelBase> voxel, AABB tmpBoundingBox);

    vector<float> positions;
    vector<int> indices;

    shared_ptr<Shader> shaderProgram = nullptr;
    glm::vec3 center;
    float radius;
    float dampingCoefficient = 0.9;
    float deltaX, deltaY, deltaZ;
};

#endif // SIMPLEBALLVOXEL_H
