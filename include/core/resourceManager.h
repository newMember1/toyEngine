#ifndef GLOBALVARMANAGER_H
#define GLOBALVARMANAGER_H
#include <memory>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/camera.h"
#include "core/shader.h"
#include "core/texture.h"

#include "debugPrint.h"

using std::string;
using std::shared_ptr;
using std::make_shared;
using std::unordered_map;

/*
* consider the manager will be used in multi threads, we must be sure that
* each thread can safely access the resoureces.
*/
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

    shared_ptr<Shader> getShader(string name)
    {
        if(shaderManager.find(name) != shaderManager.end())
            return shaderManager[name];
        DBG_ERR("SHADER: %s not found!!!", name.c_str());
    }

    shared_ptr<Texture> getTexture(string name)
    {
        if(textureManager.find(name) != textureManager.end())
            return textureManager[name];

        DBG_ERR("TEXTURE: %s not found!!!", name.c_str());
    }

    void setCamera(Camera cam)
    {
        camera = make_shared<Camera>(cam);
    };

    void setOrtho(glm::mat4 m)
    {
        ortho = make_shared<glm::mat4>(m);
    };

    void setPerspective(glm::mat4 m)
    {
        perspective = make_shared<glm::mat4>(m);
    };

    void addShader(string name, string vert, string frag)
    {
        shaderManager[name] = make_shared<Shader>(vert.c_str(), frag.c_str());
    };

    void addTexture(string name, string path, TextureTypes type, TextureMode *mode)
    {
        textureManager[name] = make_shared<Texture>(path.c_str(), type);
    }

    static ResourceManager& getInstance()
    {
        static ResourceManager instance;
        return instance;
    }

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:
    ResourceManager(){};

    unordered_map<string, shared_ptr<Shader>> shaderManager;
    unordered_map<string, shared_ptr<Texture>> textureManager;
    shared_ptr<Camera> camera;
    shared_ptr<glm::mat4> ortho;
    shared_ptr<glm::mat4> perspective;
};

#endif // GLOBALVARMANAGER_H
