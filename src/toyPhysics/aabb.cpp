#include "toyPhysics/aabb.h"

AABB::AABB()
{}

AABB::AABB(glm::vec3 minPoint, glm::vec3 maxPoint)
{
    boxMin = minPoint;
    boxMax = maxPoint;
}

AABB::AABB(std::shared_ptr<AABB> boxA, std::shared_ptr<AABB> boxB)
{
    auto aMin = boxA->getBoxMin();
    auto aMax = boxA->getBoxMax();
    auto bMin = boxB->getBoxMin();
    auto bMax = boxB->getBoxMax();

    boxMin = glm::vec3(glm::min(aMin.x, bMin.x),
                       glm::min(aMin.y, bMin.y),
                       glm::min(aMin.z, bMin.z));

    boxMax = glm::vec3(glm::max(aMax.x, bMax.x),
                       glm::max(aMax.y, bMax.y),
                       glm::max(aMax.z, bMax.z));
}

glm::vec3 AABB::getBoxMin()
{
    return boxMin;
}

glm::vec3 AABB::getBoxMax()
{
    return boxMax;
}

bool AABB::rayHit(std::shared_ptr<Ray> r, float minT, float maxT)
{
    for(int i = 0; i < 3; ++i)
    {
        float t0 = fmin(boxMin[i] - r->getStartPos()[i] / r->getDirection()[i],
                        boxMax[i] - r->getStartPos()[i] / r->getDirection()[i]);

        float t1 = fmax(boxMin[i] - r->getStartPos()[i] / r->getDirection()[i],
                        boxMax[i] - r->getStartPos()[i] / r->getDirection()[i]);
    }
}

#include <iostream>
bool AABB::intersects(std::shared_ptr<AABB> box)
{
    auto aMin = getBoxMin();
    auto aMax = getBoxMax();
    auto bMin = box->getBoxMin();
    auto bMax = box->getBoxMax();
    return (((aMin.x >= bMin.x && aMin.x <= bMax.x) || (bMin.x >= aMin.x && bMin.x <= aMax.x)) &&
            ((aMin.y >= bMin.y && aMin.y <= bMax.y) || (bMin.y >= aMin.y && bMin.y <= aMax.y)) &&
            ((aMin.z >= bMin.z && aMin.z <= bMax.z) || (bMin.z >= aMin.z && bMin.z <= aMax.z)));
}
