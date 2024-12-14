#define GLEW_STATIC
#include "GLEW/glew.h"
#include "ImGui/imgui.h"
#include "ImGui/Backends/imgui_impl_glfw.h"
#include "ImGui/Backends/imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h>
#include <sstream>

#include "CallBacks.h"
#include "Renderer.h"

unsigned int* VBOH;
unsigned int* VAOH;
float* sizeH;
bool* hoverH;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    //int xDif = width - screenwidth;
    //int yDif = height - screenheight;
    glViewport(0, 0, width, height);
    Renderer::RenderScreen(window, *VBOH, *VAOH, sizeH, hoverH);
}

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void CallBackManager::SetCallBacks(GLFWwindow* window, unsigned int* VBO, unsigned int* VAO, float* size, bool* hover) {
    VBOH = VBO;
    VAOH = VAO;
    sizeH = size;
    hoverH = hover;
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
}