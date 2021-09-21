#ifndef VOXELBASE_H
#define VOXELBASE_H

#include <vector>
#include <memory>
#include "baseStructures.h"
#include "toyPhysics/aabb.h"
#include "toyPhysics/voxelHitResult.h"

//voxel is a cube which contains many little cube
class VoxelBase
{
public:
    virtual ~VoxelBase(){};
    virtual void updateModel(float deltaTime, Direction d) = 0;
    virtual void updateModel(glm::mat4 m) = 0;
    virtual void updateView(glm::vec2 deltaDirec) = 0;
    virtual bool rayHit(std::shared_ptr<HitRecord> h, std::shared_ptr<Ray> r) = 0;
    virtual void move(glm::vec3 deltaMovement, std::vector<std::shared_ptr<VoxelBase>> moveables) = 0;
    virtual void draw() = 0;

    virtual int getIndex(int x, int y, int z) { return xCount * yCount * z + xCount * y + x; }

    bool moveAble = false;
    float xLen, yLen, zLen;
    int xCount, yCount, zCount;
    std::vector<int> types;
    std::shared_ptr<AABB> boundingBox = nullptr;
    std::shared_ptr<VoxelHitResult> voxelHitResult = nullptr;

    glm::vec3 startPos{-1, -1, -1};
    glm::vec3 frontDirection{0, 0, -1};
    glm::vec3 leftDirection{-1, 0, 0};
    glm::vec3 upDirection{0, 1, 0};
    float speed = 1.0f;

    glm::mat4 model, view, projection;
    unsigned int vao, vbo, ebo;
};

#endif
