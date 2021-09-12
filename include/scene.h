#ifndef SCENE_H
#define SCENE_H
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <vector>
#include "shader.h"

class scene
{
public:
    scene(int w, int h, glm::mat4 m);
    void draw();
    void init();

private:
    int scrWidth, scrHeight;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
};
#endif