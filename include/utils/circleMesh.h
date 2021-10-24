#ifndef CIRCLEMESH_H
#define CIRCLEMESH_H
#include <vector>
#include "core/baseStructures.h"

using std::vector;

class CircleMesh
{
public:
    CircleMesh(int angle = 10);
    vector<float> getPoints();
    vector<int> getIndices();
private:
    vector<float> points;
    vector<int> indices;
};

#endif // CIRCLEMESH_H
