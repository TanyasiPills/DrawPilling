#define GLEW_STATIC
#include "GLEW/glew.h"
#include "ImGui/imgui.h"
#include "ImGui/Backends/imgui_impl_glfw.h"
#include "ImGui/Backends/imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> 

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif
#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

////////////////
//actual stuff//
////////////////

//includes
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>

#include "Drawing.h"
#include "GLManager.h"
#include "Shader.h"
#include "SessionManager.h"


//definitions
#define PI 3.1415927f


//Variables
int screenwidth;
int screenheight;

unsigned int VBO;
unsigned int VAO;

std::vector<std::vector<float>> circles;

ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

static float size = 0.1f;
bool hover = false;


//functions
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    }
}

void RenderScreen(GLFWwindow* window) {
    ImGui::Render();
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    static double prevXpos, prevYpos;
    Drawing::handleCursorMovement(window, prevXpos, prevYpos, circles, VBO, VAO, size, 24, hover);

    for (const auto& circle : circles) {
        GLManager::updateVBO(VAO, circle);
        GLManager::drawStuff(VAO, GL_TRIANGLE_FAN, circle);
    }

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    //int xDif = width - screenwidth;
    //int yDif = height - screenheight;
    glViewport(0, 0, width, height);
    RenderScreen(window);
}

// Main code
int main(int, char**)
{
    
    SessionData data = Manager::Assembly(glfw_error_callback);

    GLManager::initBuffers(VBO, VAO);


    unsigned int shader = Shadering::CreateShader();

    GLint colorLocation = glGetUniformLocation(shader, "circleColor");
    GLint aspectRatioLoc = glGetUniformLocation(shader, "aspectRatio");
    glUseProgram(shader);

    int width, height;
    glfwGetFramebufferSize(data.window, &width, &height);
    float aspect = (float)width / (float)height;

    glUniform1f(aspectRatioLoc, aspect);

    glfwSetFramebufferSizeCallback(data.window, framebuffer_size_callback);

    //ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground;

    // Main loop
#ifdef __EMSCRIPTEN__
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(data.window))
#endif
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(data.window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        //ImGui::ShowDemoWindow(&show_demo_window);

        processInput(data.window);

        {
            ImGui::Begin("Controls", 0);

            float label_width = 200.0f + ImGui::GetStyle().ItemSpacing.x;
            ImGui::PushItemWidth(label_width);
            ImVec2 content_size = ImGui::GetWindowSize();
            ImGui::SetWindowSize(ImVec2(0, 0), ImGuiCond_Always);

            ImGui::DragFloat("##x", &size, 0.01f, 0.0f, 0.0f, "%.04f");
            ImGui::SeparatorText("Color");
            static float color[3] = { 0.0f, 0.0f, 1.0f };
            ImGui::ColorEdit3("##c", color);
            glUniform3f(colorLocation, color[0], color[1], color[2]);
            glfwGetFramebufferSize(data.window, &width, &height);
            float aspect = (float)width / (float)height;
            glUniform1f(aspectRatioLoc, aspect);

            hover = ImGui::IsWindowHovered();

            ImGui::PopItemWidth();

            ImGui::End();
        }

        // Rendering
        RenderScreen(data.window);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    Manager::DisAssembly(data.window, shader);
}