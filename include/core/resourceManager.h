#ifndef GLOBALVARMANAGER_H
#define GLOBALVARMANAGER_H
#include <memory>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/camera.h"
#include "core/shader.h"

using std::shared_ptr;
using std::unordered_map;

class ResourceManager
{
public:
    shared_ptr<Camera> getCamera()
    {
        return camera;
    };

    shared_ptr<glm::mat4> getPerspective()
    {
        return perspective;
    };

    shared_ptr<glm::mat4> getOrtho()
    {
        return ortho;
    }

    shared_ptr<Shader> getShader(std::string name)
    {
        if(shaderManager.find(name) != shaderManager.end())
            return shaderManager[name];

        std::cout<<"SHADER: "<<name<<"not found!"<<std::endl;
    }

    void setCamera(Camera cam)
    {
        camera = std::make_shared<Camera>(cam);
    };

    void setOrtho(glm::mat4 m)
    {
        ortho = std::make_shared<glm::mat4>(m);
    };

    void setPerspective(glm::mat4 m)
    {
        perspective = std::make_shared<glm::mat4>(m);
    };

    void addShader(std::string name, std::string vert, std::string frag)
    {
        shaderManager[name] = std::make_shared<Shader>(vert.c_str(), frag.c_str());
    };

    static ResourceManager& getInstance()
    {
        static ResourceManager instance;
        return instance;
    }

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    ResourceManager(){};

    unordered_map<std::string, shared_ptr<Shader>> shaderManager;
    shared_ptr<Camera> camera;
    shared_ptr<glm::mat4> ortho;
    shared_ptr<glm::mat4> perspective;
};

#endif // GLOBALVARMANAGER_H
