#include "scene.h"
#include "core/resourceManager.h"

#include "voxels/planeVoxel.h"
#include "voxels/simpleBallVoxel.h"
#include "voxels/chunkVoxel.h"
#include "environment/sky.h"

scene::scene(int w, int h, std::shared_ptr<MovePublisher> p)
{
    sceneTexWidth = w;
    sceneTexHeight = h;
    publisher = p;
    init();
}

void scene::draw(float time)
{

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    //draw sky
    glDisable(GL_DEPTH_TEST);
    sky->draw(time);
    glEnable(GL_DEPTH_TEST);

    //draw voxels
    for(auto s : staticVoxels)
        s->draw();
    for(auto m : moveableVoxels)
        m->draw();
}

void scene::init()
{
    //init global vars
    //add shaders
    ResourceManager::getInstance().addShader("constColor", "../shaders/constColor.vert", "../shaders/constColor.frag");
    ResourceManager::getInstance().addShader("atmosphere", "../shaders/atmosphere.vert", "../shaders/atmosphere.frag");
    ResourceManager::getInstance().addShader("sun", "../shaders/sun.vert", "../shaders/sun.frag");
    ResourceManager::getInstance().addShader("texture", "../shaders/texture.vert", "../shaders/texture.frag");

    //add textures;
    ResourceManager::getInstance().addTexture("rock", "../assets/wall.jpg", TextureTypes::TWOD, nullptr);

    //init sky
    sky = std::make_shared<Sky>();
    sky->init(glm::vec3(1, 1, -1));

    //init objects
    auto s = std::make_shared<PlaneVoxel>();
    auto m = std::make_shared<SimpleBallVoxel>();
    auto m1 = std::make_shared<ChunkVoxel>(ChunkTypes::ROCK);

    staticVoxels.push_back(s);
    moveableVoxels.push_back(m);
    moveableVoxels.push_back(m1);

    publisher->attach(m);
    publisher->setStaticVoxels(staticVoxels);
}
