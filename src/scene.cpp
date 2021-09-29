#include "scene.h"

scene::scene(int w, int h, std::shared_ptr<ScreenMovementsPublisher> p)
{
    sceneTexWidth = w;
    sceneTexHeight = h;
    publisher = p;
    init();
}

void scene::moveVoxels(float time)
{
    for(auto m : moveableVoxels)
        m->move(time, staticVoxels);
}

void scene::draw(float time)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    moveVoxels(time);
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
