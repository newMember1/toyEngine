#ifndef VOXELBASE_H
#define VOXELBASE_H

#include <vector>
#include "baseStructures.h"

//voxel is a cube which contains many little cube
class VoxelBase
{
public:
    virtual ~VoxelBase(){};
    virtual void updateModel(float deltaTime, direction d) = 0;
    virtual void updateView(glm::vec2 deltaDirec) = 0;
    virtual void draw() = 0;

    virtual bool getMovementState() { return moveMent; }
    virtual void setMovementState(bool m) { moveMent = m; }

    int getIndex(int x, int y, int z) { return xCount * yCount * z + xCount * y + x;}

    bool moveMent = false;
    float xLen, yLen, zLen;
    int xCount, yCount, zCount;
    std::vector<int> types;
    glm::vec3 startPos{-1, -1, -1};
    glm::vec3 faceDirection{1, 0, 1};

    glm::mat4 model, view, projection;
    unsigned int vao, vbo, ebo;
};

#endif
