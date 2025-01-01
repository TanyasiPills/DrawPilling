#include "GLEW/glew.h"
#include "ImGui/imgui.h"
#include "ImGui/Backends/imgui_impl_glfw.h"
#include "ImGui/Backends/imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> 
#include "SessionManager.h"

SessionData Manager::Assembly() {
    SessionData data;

    glfwInit(); //!!!!!!!!

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(720, 720, "I hate Jazz", nullptr, nullptr);
    data.window = window;
    data.screenWidth = 690;
    data.screenHeight = 690;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    glewInit(); //!!!!!!!!

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);

    return data;
}
void Manager::DisAssembly(GLFWwindow* window, unsigned int shader) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glDeleteProgram(shader);
    glfwTerminate();
}