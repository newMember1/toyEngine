#ifndef BALLMESH_H
#define BALLMESH_H

#include <vector>
#include "core/baseStructures.h"

using std::vector;

class BallMesh
{
public:
    BallMesh(int angle);

    vector<float> getPoints();
    vector<int> getIndices();
    int getTriangleCount();
private:
    int topTriangles;
    int midTriangles;
    int phiCount;
    int thetaCount;

    vector<float> points;
    vector<int> indices;
    void generateIndices(int angle);
};

#endif // BALLMESH_H
