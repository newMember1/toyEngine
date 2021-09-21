#ifndef BVH_H
#define BVH_H

#include "core/voxelBase.h"
#include <algorithm>

using std::shared_ptr;
using std::vector;
using std::sort;

//sepcific used for store "VoxelBase"
class Bvh
{
public:
    class Node
    {
    public:
        std::shared_ptr<Node> left = nullptr;
        std::shared_ptr<Node> right = nullptr;
        std::shared_ptr<AABB> boundingBox;
        std::shared_ptr<VoxelBase> leaf = nullptr;

        Node();
        Node(std::shared_ptr<VoxelBase> v);
        bool rayHit(shared_ptr<Ray> r, shared_ptr<HitRecord> h);
    };

    Bvh(std::vector<std::shared_ptr<VoxelBase>> & voxels);
    bool rayHit(shared_ptr<Ray> r, shared_ptr<HitRecord> h);
private:
    std::shared_ptr<Node> rootNode = nullptr;
    void generateBVH(shared_ptr<Node> root, vector<shared_ptr<VoxelBase>> & voxels, int start, int end);

    static bool xCmp(shared_ptr<VoxelBase> a, shared_ptr<VoxelBase> b);
    static bool yCmp(shared_ptr<VoxelBase> a, shared_ptr<VoxelBase> b);
    static bool zCmp(shared_ptr<VoxelBase> a, shared_ptr<VoxelBase> b);
};

#endif // BVH_H
