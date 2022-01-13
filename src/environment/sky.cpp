#include "environment/sky.h"
#include <iostream>
using std::cout;
using std::endl;

void Sky::init(glm::vec3 direc)
{
    //1.init sky camera
    skyCamera = std::make_shared<Camera>(glm::vec3(0, 0.99, 0));

    //2.init sun and atmosphere
    sun = std::make_shared<Sun>();
    sun->init(direc);

    atmosphere = std::make_shared<Atmosphere>();
    atmosphere->init(skyCamera);
}

void Sky::draw(float time)
{
    atmosphere->draw(time);
    sun->draw(time);
    atmosphere->setSunDirec(sun->getSunDirec());
}
