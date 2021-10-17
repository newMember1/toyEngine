#include "utils/ballMesh.h"
#include <iostream>

BallMesh::BallMesh(int angle)
{
    phiCount = 180 / angle;
    thetaCount = 360 / angle;

    points.resize(((phiCount - 1) * thetaCount + 2) * 3);
    int index = 3;
    int minPhi = angle;
    int maxPhi = 180 - angle;

    for(int p = minPhi; p <= maxPhi; p += angle)
        for(int t = 0; t < 360; t += angle)
        {
            float phi = 1.0 * p / 180 * PI;
            float theta = 1.0 * t / 180 * PI;
            points[index++] = sin(phi) * cos(theta);
            points[index++] = cos(phi);
            points[index++] = sin(phi) * sin(theta);
        }

    points[0] = 0;
    points[1] = 1;
    points[2] = 0;
    points[index++] = 0;
    points[index++] = -1;
    points[index++] = 0;

    generateIndices(angle);
}

void BallMesh::generateIndices(int angle)
{
    topTriangles = 360 / angle;
    midTriangles = ((180 / angle) - 2)*(360 / angle) * 2;
    indices.resize((topTriangles * 2 + midTriangles) * 3);

    int count = 0;
    //top triangles
    for(int i = 0; i < topTriangles; ++i)
    {
        indices[i * 3] = 0;
        indices[i * 3 + 1] = i + 1;
        indices[i * 3 + 2] = (i + 1 == topTriangles) ? 1 : i + 2;
        ++count;
    }

    int rows = 180 / angle - 2;
    int columns = 360 / angle;
    for (int row = 0; row < rows; row++)
        for (int col = 0; col < columns; col++)
        {
            int topLeft = row * columns + col + 1;
            int topRight = (topLeft % columns) ? topLeft + 1 : row * columns + 1;

            int bottomLeft = topLeft + columns;
            int bottomRight = topRight + columns;

            indices[count * 3 + 0] = topLeft;
            indices[count * 3 + 1] = bottomLeft;
            indices[count * 3 + 2] = bottomRight;
            count++;

            indices[count * 3 + 0] = bottomRight;
            indices[count * 3 + 1] = topRight;
            indices[count * 3 + 2] = topLeft;
            count++;
        }

    int bottomStart = rows * columns + 1;
    for (int i = 0; i < topTriangles; i++)
    {
        indices[count * 3 + 0] = bottomStart + i;
        indices[count * 3 + 1] = (i == topTriangles - 1) ? bottomStart : indices[count * 3] + 1;
        indices[count * 3 + 2] = points.size() / 3 - 1;

        count++;
    }
}

vector<float> BallMesh::getPoints()
{
    return points;
}

vector<int> BallMesh::getIndices()
{
    return indices;
}

int BallMesh::getTriangleCount()
{
    return topTriangles * 2 + midTriangles;
}
