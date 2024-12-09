#define GLEW_STATIC
#define PI 3.1415927f

#include "GLEW/glew.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include "Drawing.h"
#include "GLManager.h"


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


int screenwidth;
int screenheight;

struct ShaderSource {
    std::string Vertex;
    std::string Fragment;
};


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

static ShaderSource ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if(line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str()};
}

static unsigned int ComplileShader(const std::string& source, unsigned int type) 
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) 
{
    unsigned int program = glCreateProgram();
    unsigned int vertShader = ComplileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fragShader = ComplileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    return program;
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    //int xDif = width - screenwidth;
    //int yDif = height - screenheight;
    glViewport(0, 0, width, height);
}

// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;


    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(690, 690, "I hate Jazz", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    screenwidth = 690;
    screenheight = 690;
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

    bool show_demo_window = true;
    ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);


    unsigned int VBO;
    unsigned int VAO;
    GLManager::initBuffers(VBO, VAO);


    ShaderSource source = ParseShader("Resources/shaders/Style.penis");
    unsigned int shader = CreateShader(source.Vertex, source.Fragment);

    //int maxIterationLoc = glGetUniformLocation(shader, "maxIterations");
    GLint colorLocation = glGetUniformLocation(shader, "circleColor");
    GLint aspectRatioLoc = glGetUniformLocation(shader, "aspectRatio");

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float aspect = (float)width / (float)height;


    glUseProgram(shader);

    glUniform1f(aspectRatioLoc, aspect);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground;

    std::vector<std::vector<float>> circles;

    // Main loop
#ifdef __EMSCRIPTEN__
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        //if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

        processInput(window);

        static float size = 0.1f;
        bool hover = false;

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
            glfwGetFramebufferSize(window, &width, &height);
            float aspect = (float)width / (float)height;
            glUniform1f(aspectRatioLoc, aspect);

            hover = ImGui::IsWindowHovered();

            ImGui::PopItemWidth();

            ImGui::End();
        }

        



        // Rendering
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
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glDeleteProgram(shader);
    glfwTerminate();

    return 0;
}