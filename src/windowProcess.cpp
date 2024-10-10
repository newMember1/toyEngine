#include "windowProcess.h"
using namespace std;

bool gPressed = false;
double gXPressed = false;
double gYPressed = false;

class GLFWwindow;

void fbSizeCB(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouseCB(GLFWwindow* window, double xpos, double ypos)
{
    //if cursor pos change then this function will be called
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    float deltaX = 0.0f;
    float deltaY = 0.0f;

    if(state == GLFW_PRESS)//only store the position when we press left button
    {
        if(gPressed)
        {
            deltaX = xpos - gXPressed;
            deltaY = ypos - gYPressed;
            gXPressed = xpos;
            gYPressed = ypos;
        }
        else
        {
            gPressed = true;
            gXPressed = xpos;
            gYPressed = ypos;
        }
    }
    else
    {
        gPressed = false;
    }

    globalCamera->ProcessMouseMovement(-deltaX, deltaY);
}

void scrollCB(GLFWwindow* window, double xoffset, double yoffset)
{
    globalCamera->ProcessMouseScroll(yoffset);
}