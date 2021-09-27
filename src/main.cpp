#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/baseStructures.h"
#include "scene.h"

#include <iostream>
#include <vector>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window, std::shared_ptr<ScreenMovementsPublisher> publisher);

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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    // glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    auto publisher = std::make_shared<ScreenMovementsPublisher>();
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
Direction d;
void processInput(GLFWwindow *window, std::shared_ptr<ScreenMovementsPublisher> publisher)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        d = Direction::FORWARD;
        publisher->processKeyBoardInput(deltaTime, d);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        d = Direction::BACKWARD;
        publisher->processKeyBoardInput(deltaTime, d);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        d = Direction::LEFT;
        publisher->processKeyBoardInput(deltaTime, d);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        d = Direction::RIGHT;
        publisher->processKeyBoardInput(deltaTime, d);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        d = Direction::UP;
        publisher->processKeyBoardInput(deltaTime, d);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        d = Direction::DOWN;
        publisher->processKeyBoardInput(deltaTime, d);
    }
}

//reseize window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

//handle view's change when left button is pressed
float xPosPressed, yPosPressed;
float deltaX, deltaY;
bool pressed = false;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    //if cursor pos change then this function will be called
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if(state == GLFW_PRESS && pressed == false)//only store the position when we press left button
    {
        pressed = true;
        xPosPressed = xpos;
        yPosPressed = ypos;
    }
    if(state == GLFW_RELEASE)
    {
        pressed = false;
    }

    if(pressed)
    {
        deltaX = xpos - xPosPressed;
        deltaY = ypos - yPosPressed;
    }
}

// // glfw: whenever the mouse scroll wheel scrolls, this callback is called
// // ----------------------------------------------------------------------
// void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
// {
//     camera.ProcessMouseScroll(yoffset);
// }

