#include "scene.h"
#include "core/resourceManager.h"

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

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //draw sky
    glDisable(GL_DEPTH_TEST);
    sky->draw(time);
    glEnable(GL_DEPTH_TEST);

    //draw voxels
    moveVoxels(time);
    for(auto s : staticVoxels)
        s->draw();
    for(auto m : moveableVoxels)
        m->draw();
}

void scene::init()
{
    //init global vars
    ResourceManager::getInstance().addShader("constColor", "../shaders/constColor.vert", "../shaders/constColor.frag");
    ResourceManager::getInstance().addShader("atmosphere", "../shaders/atmosphere.vert", "../shaders/atmosphere.frag");
    ResourceManager::getInstance().addShader("sun", "../shaders/sun.vert", "../shaders/sun.frag");

    //init sky
    sky = std::make_shared<Sky>();
    sky->init(glm::vec3(1, 1, -1));

    //init objects
    auto s = std::make_shared<PlaneVoxel>();
    auto m = std::make_shared<SimpleBallVoxel>();
    staticVoxels.push_back(s);
    moveableVoxels.push_back(m);
    publisher->attach(m);
    publisher->setStaticVoxels(staticVoxels);
}
