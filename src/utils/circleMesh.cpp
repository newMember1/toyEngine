#include "utils/circleMesh.h"

CircleMesh::CircleMesh(int angle)
{
    int thetaCount = 360 / angle;
    points.resize((thetaCount + 1) * 3);
    points[0] = 0;
    points[1] = 0;
    points[2] = 0;

    for(int i = 0; i < thetaCount; ++i)
    {
        float theta = i * angle;
        points[(i + 1) * 3] = cos(glm::radians(theta));
        points[(i + 1) * 3 + 1] = sin(glm::radians(theta));
        points[(i + 1) * 3 + 2] = 0;
    }

    indices.resize((thetaCount) * 3);
    for(int i = 0; i < thetaCount; ++i)
    {
        indices[i * 3] = 0;
        indices[i * 3 + 1] = i + 1;
        indices[i * 3 + 2] = i + 2 > (thetaCount) ? 1 : i + 2;
    }
}

vector<float> CircleMesh::getPoints()
{
    return points;
}

vector<int> CircleMesh::getIndices()
{
    return indices;
}
