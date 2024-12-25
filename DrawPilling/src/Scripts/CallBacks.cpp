#define GLEW_STATIC
#include "GLEW/glew.h"
#include "ImGui/imgui.h"
#include "ImGui/Backends/imgui_impl_glfw.h"
#include "ImGui/Backends/imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <sstream>
#include <iostream>

#include "CallBacks.h"
#include "Renderer.h"
#include "Shader.h"

unsigned int* VBOH;
unsigned int* VAOH;
float* sizeH;
bool* hoverH;

static bool spacePressed = false;

static int initialWidth = -1;
static int initialHeight = -1;
static int previousWidth = 800;
static int prevousHeight = 800;
static int previousX = 0;
static int previousY = 0;

static float xRatio = 1.0f;
static float yRatio = 1.0f;
static float xOffset = 0.0f;
static float yOffset = 0.0f;
static float scale = 1.0f;

GLint xAspectLoc;
GLint yAspectLoc;
GLint xOffsetLoc;
GLint yOffsetLoc;
GLint scaleLoc;

static double previousMousePosX = -1;
static double previousMousePosY = -1;
static double initx = -1;
static double inity = -1;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

    if (initialWidth == -1) {
        initialHeight = height;
        initialWidth = width;
    }

    int currentX, currentY;
    glfwGetWindowPos(window, &currentX, &currentY);

    if (width != previousWidth) {
        xRatio = initialWidth / static_cast<float>(width);
        previousWidth = width;
        previousX = currentX;
        glUniform1f(xAspectLoc, xRatio);
    }
    if (height != prevousHeight) {
        yRatio = initialHeight / static_cast<float>(height);
        prevousHeight = height;
        previousY = currentY;
        glUniform1f(yAspectLoc, yRatio);
    }

    std::cout << "xRatio: " << xRatio << ", yRatio: " << yRatio << std::endl;

    glViewport(0, 0, width, height);
    Renderer::RenderScreen(window, *VBOH, *VAOH, sizeH, hoverH);
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

Ratios CallBackManager::SetCallBacks(GLFWwindow* window, unsigned int* VBO, unsigned int* VAO, float* size, bool* hover, ShaderAndLocs& shaderAndLocs) {
    VBOH = VBO;
    VAOH = VAO;
    sizeH = size;
    hoverH = hover;

    xAspectLoc = shaderAndLocs.xRatio;
    yAspectLoc = shaderAndLocs.yRatio;
    xOffsetLoc = shaderAndLocs.xOffset;
    yOffsetLoc = shaderAndLocs.yOffset;
    scaleLoc = shaderAndLocs.scale;

    Ratios mapData;
    mapData.xRatio = &xRatio;
    mapData.yRatio = &yRatio;
    mapData.xOffset = &xOffset;
    mapData.yOffset = &yOffset;
    mapData.scale = &scale;

    glUniform1f(xAspectLoc, xRatio);
    glUniform1f(yAspectLoc, yRatio);
    glUniform1f(xOffsetLoc, xOffset);
    glUniform1f(yOffsetLoc, yOffset);
    glUniform1f(scaleLoc, scale);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetErrorCallback(glfw_error_callback);

    return mapData;
}

void CallBackManager::ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!spacePressed) {
            glfwGetCursorPos(window, &initx, &inity);
            glfwGetCursorPos(window, &previousMousePosX, &previousMousePosY);
            spacePressed = true;
            return;
        }

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        if (xpos != previousMousePosX) {
            float xdiff = (xpos - previousMousePosX) / width;
            std::cout << (xpos - initx) / width << std::endl;
            xOffset += xdiff*2;
            glUniform1f(xOffsetLoc, xOffset);
        }
        if (ypos != previousMousePosY) {
            float ydiff = (ypos - previousMousePosY) / height;
            std::cout << (ypos - inity) / height << std::endl;
            yOffset -= ydiff*2;
            glUniform1f(yOffsetLoc, yOffset);
        }

        previousMousePosX = xpos;
        previousMousePosY = ypos;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        if (spacePressed) {
            spacePressed = false;
        }
    }
}