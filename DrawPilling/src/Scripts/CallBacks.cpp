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
static float xRatio = 1;
static float yRatio = 1;

GLint xAspectLoc;
GLint yAspectLoc;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

    if (initialWidth == -1) {
        initialHeight = height;
        initialWidth = width;
    }

    int currentX, currentY;
    glfwGetWindowPos(window, &currentX, &currentY);

    if (width != previousWidth) {
        if (currentX != previousX) {
            xRatio = static_cast<float>(width) / initialWidth;
        }
        else {
            xRatio = initialWidth / static_cast<float>(width);
        }
        previousWidth = width;
        previousX = currentX;
        glUniform1f(xAspectLoc, xRatio);
    }
    if (height != prevousHeight) {
        if (currentY != previousY) {
            yRatio = static_cast<float>(height) / initialHeight;
        }
        else {
            yRatio = initialHeight / static_cast<float>(height);
        }
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

void CallBackManager::SetCallBacks(GLFWwindow* window, unsigned int* VBO, unsigned int* VAO, float* size, bool* hover, GLint& xLoc, GLint& yLoc) {
    VBOH = VBO;
    VAOH = VAO;
    sizeH = size;
    hoverH = hover;
    xAspectLoc = xLoc;
    yAspectLoc = yLoc;
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetErrorCallback(glfw_error_callback);
}

void CallBackManager::ProcessInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        if (!spacePressed) {
            spacePressed = true; // Mark as pressed
            // Action for pressing Space
            std::cout << "Space key pressed!" << std::endl;
        }
    }

    // Check if Space is released
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
        if (spacePressed) {
            spacePressed = false; // Mark as released
            // Action for releasing Space
            std::cout << "Space key released!" << std::endl;
        }
    }
}