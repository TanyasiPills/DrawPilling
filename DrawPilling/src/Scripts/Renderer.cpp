#include "GLEW/glew.h"
#include "ImGui/imgui.h"
#include "ImGui/Backends/imgui_impl_glfw.h"
#include "ImGui/Backends/imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> 
#include "Renderer.h"
#include "Drawing.h"
#include "GLManager.h"
#include <vector>

std::vector<std::vector<float>> circles;

ImVec4 clear_color = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

void Renderer::RenderScreen(GLFWwindow* window, unsigned int& VBO, unsigned int& VAO, float* size, bool* hover) {
    ImGui::Render();
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    static double prevXpos, prevYpos;
    Drawing::handleCursorMovement(window, prevXpos, prevYpos, circles, VBO, VAO, *size, 24, *hover);

    for (const auto& circle : circles) {
        GLManager::updateVBO(VAO, circle);
        GLManager::drawStuff(VAO, GL_TRIANGLE_FAN, circle);
    }

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}