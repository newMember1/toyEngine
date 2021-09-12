#ifndef BASEOBJECTS_H
#define BASEOBJECTS_H
#include <glm/glm.hpp>

class BaseObject
{
public:
    virtual bool hit() = 0;
    virtual void updateModel() = 0;
    virtual void updateView() = 0;
    virtual ~BaseObject() = 0;
private:
    glm::vec3 moveDirection(0);
}
#endif