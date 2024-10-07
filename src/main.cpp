#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/baseStructures.h"
#include "scene.h"
#include "windowProcess.h"

#include <iostream>
#include <vector>
using namespace std;

void processInput(GLFWwindow *window, std::shared_ptr<MovePublisher> publisher);

int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;
float lastFrame = 0;
float deltaTime = 0;

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "toyEngine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, fbSizeCB);
    glfwSetCursorPosCallback(window, mouseCB);
    glfwSetScrollCallback(window, scrollCB);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    auto publisher = std::make_shared<MovePublisher>();
    scene myScene(800, 600, publisher);
    while (!glfwWindowShouldClose(window))
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window, publisher);

        myScene.draw(deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}

//update objects and camera if necessary
ACTION a = ACTION::NONE;
void processInput(GLFWwindow *window, std::shared_ptr<MovePublisher> publisher)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
        a = ACTION::JUMP;
    }
    else if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
        a = ACTION::DOWN;
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        a = ACTION::FRONT;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        a = ACTION::BACKWARD;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        a = ACTION::LEFT;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        a = ACTION::RIGHT;
    }
    else
        return;

    publisher->processKeyBoardInput(a);
}