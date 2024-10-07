#ifndef WINDOWPROCESS_H
#define WINDOWPROCESS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include "core/baseStructures.h"
#include "core/screenMovementsPublisher.h"

void fbSizeCB(GLFWwindow* window, int width, int height);

void mouseCB(GLFWwindow* window, double xpos, double ypos);

void scrollCB(GLFWwindow* window, double xoffset, double yoffset);

#endif
