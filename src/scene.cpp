#include "scene.h"

scene::scene(int w, int h, std::shared_ptr<ScreenMovementsPublisher> p)
{
    sceneTexWidth = w;
    sceneTexHeight = h;
    publisher = p;
    init();
}

void scene::draw()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    t->draw();
    s->draw();
}

void scene::init()
{
    t = std::make_shared<PlaneVoxel>();
    s = std::make_shared<SimpleBallVoxel>();

    publisher->attach(s);
}
