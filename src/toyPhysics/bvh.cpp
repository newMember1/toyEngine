#include "toyPhysics/bvh.h"
Bvh::Node::Node()
{

}

Bvh::Node::Node(shared_ptr<VoxelBase> v)
{
    leaf = v;
    boundingBox = v->boundingBox;
}

bool Bvh::Node::rayHit(shared_ptr<Ray> r, shared_ptr<HitRecord> h)
{
    if(!boundingBox->rayHit(r, h->minT, h->maxT))
        return false;

    if(leaf == nullptr)
    {
        bool lHit = left->rayHit(r, h);
        bool rHit = right->rayHit(r, h);
        return lHit || rHit;
    }

    if(leaf != nullptr)
    {
        return leaf->rayHit(h, r);
    }
}

Bvh::Bvh(vector<shared_ptr<VoxelBase>> & voxels)
{
    generateBVH(rootNode, voxels, 0, voxels.size() - 1);
}

void Bvh::generateBVH(shared_ptr<Node> root, vector<shared_ptr<VoxelBase>> & voxels, int start, int end)
{
    root.reset(new Node());
    int axis = rand() % 3;
    if(axis == 0)
        sort(voxels.begin() + start, voxels.begin() + end, xCmp);
    if(axis == 1)
        sort(voxels.begin() + start, voxels.begin() + end, yCmp);
    if(axis == 2)
        sort(voxels.begin() + start, voxels.begin() + end, zCmp);

    if(start == end || start + 1 == end)
    {
        root->left.reset(new Node(voxels[start]));
        root->right.reset(new Node(voxels[end]));
    }
    else
    {
        int mid = (start + end) / 2;
        generateBVH(root->left, voxels, start, mid);
        generateBVH(root->right, voxels, mid + 1, end);
    }
}

bool Bvh::rayHit(shared_ptr<Ray> r, shared_ptr<HitRecord> h)
{
    return rootNode->rayHit(r, h);
}

bool Bvh::xCmp(shared_ptr<VoxelBase> a, shared_ptr<VoxelBase> b)
{
    return a->boundingBox->getBoxMin().x > b->boundingBox->getBoxMin().x;
}

bool Bvh::yCmp(shared_ptr<VoxelBase> a, shared_ptr<VoxelBase> b)
{
    return a->boundingBox->getBoxMin().y > b->boundingBox->getBoxMin().y;
}

bool Bvh::zCmp(shared_ptr<VoxelBase> a, shared_ptr<VoxelBase> b)
{
    return a->boundingBox->getBoxMin().z > b->boundingBox->getBoxMin().z;
}
