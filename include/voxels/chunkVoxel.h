#ifndef CHUNK_H
#define CHUNK_H

#include <memory>
#include <string>
#include "core/voxelBase.h"

using std::vector;
using std::shared_ptr;
using std::string;

class ChunkVoxel : public VoxelBase
{
friend class TreeChunk;

public:
    ChunkVoxel(const ChunkVoxel& oldVoxel);
    ChunkVoxel(ChunkTypes type);
    ChunkVoxel(ChunkTypes type, string shaderName, glm::mat4 m, glm::vec3 sPos, int xc, int yc, int zc);
    virtual ~ChunkVoxel();
    virtual bool rayHit(shared_ptr<HitRecord> h, shared_ptr<Ray> r) override;
    virtual void draw() override;

private:
    string getTextureName(ChunkTypes type);
    void genVertices();

    ChunkTypes chunkType;
    string textureName;
    string shaderName;
};

#endif