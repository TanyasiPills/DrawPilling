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
#include "Renderer.h"
#include "CallBacks.h"


//definitions
#define PI 3.1415927f


//Variables
int screenwidth, screenheight;

unsigned int VBO, VAO;

static float size = 0.1f;
bool hover = false;


// Main code
int main()
{
    SessionData data = Manager::Assembly();

    ShaderAndLocs shaderAndLocs = Shadering::CreateShader(VBO,VAO);

    CallBackManager::SetCallBacks(data.window, &VBO, &VAO, &size, &hover, shaderAndLocs.xRatio, shaderAndLocs.yRatio);


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

        CallBackManager::ProcessInput(data.window);

        Renderer::RenderUI(shaderAndLocs.colorLoc, &size, &hover);

        Renderer::RenderScreen(data.window,VBO,VAO, &size, &hover);
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    Manager::DisAssembly(data.window, shaderAndLocs.shader);
}