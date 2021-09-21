#ifndef AABBBOX_H
#define AABBBOX_H

#include <memory>
#include "core/baseStructures.h"

class AABB
{
public:
    AABB();
    AABB(glm::vec3 minPoint, glm::vec3 maxPoint);
    AABB(std::shared_ptr<AABB> boxA, std::shared_ptr<AABB> boxB);

    glm::vec3 getBoxMin();
    glm::vec3 getBoxMax();
    bool rayHit(std::shared_ptr<Ray> r, float minT, float maxT);
    bool intersects(std::shared_ptr<AABB> box);
private:
    glm::vec3 boxMin;
    glm::vec3 boxMax;
};

#endif // AABBBOX_H
