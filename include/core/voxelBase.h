#ifndef VOXELBASE_H
#define VOXELBASE_H

//voxel is a cube which contains many little cube
class VoxelBase
{
public:
    virtual ~VoxelBase() = 0;
    virtual void updateModel(float deltaTime, direction d) = 0;
    virtual void updateView(glm::vec2 deltaDirec) = 0;

    virtual bool getMovementState() { return moveMent; }
    virtual void setMovementState(bool m) { moveMent = m; }

    virtual void draw();
private:
    bool moveMent = false;
    int xLen, yLen, zLen;
    int xCount, yCount, zCount;
    vector<int> indexes;
    glm::vec3 startPos(-1, -1, -1);
}
#endif