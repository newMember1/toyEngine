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
    for(auto s : staticVoxels)
        s->draw();
    for(auto m : moveableVoxels)
        m->draw();
}

void scene::init()
{
    auto s = std::make_shared<PlaneVoxel>();
    auto m = std::make_shared<SimpleBallVoxel>();
    staticVoxels.push_back(s);
    moveableVoxels.push_back(m);
    publisher->attach(m);
    publisher->setStaticVoxels(staticVoxels);
}
