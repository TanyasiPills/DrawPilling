#define GLEW_STATIC
#include "GLEW/glew.h"
#include "ImGui/imgui.h"
#include "ImGui/Backends/imgui_impl_glfw.h"
#include "ImGui/Backends/imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> 

#include "GLManager.h"
#include "Drawing.h"
#include "Renderer.h"



std::vector<std::vector<float>> circles;
std::vector<std::vector<float>> canvas;

ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

void Renderer::RenderScreen(GLFWwindow* window, unsigned int& VBO, unsigned int& VAO, float* size, bool* hover) {
    ImGui::Render();
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    static double prevXpos, prevYpos;
    Drawing::handleCursorMovement(window, prevXpos, prevYpos, circles, VBO, VAO, *size, 12, *hover);

    for (const auto& circle : circles) {
        GLManager::updateVBO(VAO, circle);
        GLManager::drawStuff(VAO, GL_TRIANGLE_FAN, circle);
    }

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

void Renderer::RenderUI(GLint& colorLoc,float* size, bool* hover) {
    ImGui::Begin("Controls", 0);

    float label_width = 200.0f + ImGui::GetStyle().ItemSpacing.x;
    ImGui::PushItemWidth(label_width);
    ImVec2 content_size = ImGui::GetWindowSize();
    ImGui::SetWindowSize(ImVec2(0, 0), ImGuiCond_Always);

    ImGui::DragFloat("##x", size, 0.01f, 0.0f, 0.0f, "%.04f");
    ImGui::SeparatorText("Color");
    static float color[3] = { 0.0f, 0.0f, 1.0f };
    ImGui::ColorEdit3("##c", color);
    glUniform3f(colorLoc, color[0], color[1], color[2]);

    *hover = ImGui::IsWindowHovered();

    ImGui::PopItemWidth();

    ImGui::End();
}