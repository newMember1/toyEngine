#ifndef TREE_VOXEL_H
#define TREE_VOXEL_H

#include <memory>
#include <string>
#include "chunkVoxel.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::string;

class TreeChunk : public VoxelBase
{
public:
    TreeChunk();
    virtual ~TreeChunk() {};

    virtual bool rayHit(shared_ptr<HitRecord> h, shared_ptr<Ray> r) override;
    virtual void draw() override;

private:
    void genVertices();

    unsigned int trunkVao, trunkVbo;
    unsigned int leafVao, leafVbo;

    string trunkShader = "constColor";
    string leafShader = "constColor";
};

#endif