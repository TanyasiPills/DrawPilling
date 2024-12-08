#include "Drawing.h"
#include "GLManager.h"
#include <vector>
#include <math.h>
#include <iostream>
#include "GLEW/glew.h"
#include <GLFW/glfw3.h>
#include "ImGui/imgui.h"
#include "ImGui/Backends/imgui_impl_glfw.h"
#include "ImGui/Backends/imgui_impl_opengl3.h"

#define PI 3.1415927f

std::vector<float> Drawing::drawCircle(float x, float y, float r, int sides) {
    std::vector<float> vertices;
	const float step = 2 * PI / sides;

    for (int i = 0; i < sides; ++i) {
        float theta = step * i;
        float dX = x + r * cosf(theta);
        float dY = y + r * sinf(theta);
        vertices.push_back(dX);
        vertices.push_back(dY);
    }
    return vertices;
}

void Drawing::handleCursorMovement(GLFWwindow* window, double& prevXpos, double& prevYpos, std::vector<std::vector<float>>& circles, GLuint VBO, GLuint VAO, float radius, int sides, bool hover) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float x1 = static_cast<float>(prevXpos) / width * 2.0f - 1.0f;
    float y1 = -static_cast<float>(prevYpos) / height * 2.0f + 1.0f;
    float x2 = static_cast<float>(xpos) / width * 2.0f - 1.0f;
    float y2 = -static_cast<float>(ypos) / height * 2.0f + 1.0f;

    std::vector<float> currentCircle = Drawing::drawCircle(x2, y2, radius, sides);
    GLManager::updateVBO(VBO, currentCircle);
    GLManager::drawStuff(VAO, GL_TRIANGLE_FAN, currentCircle);

    if (hover || ImGui::IsAnyItemHovered())
    {
        std::cout << "hhhaaaaaaa" << std::endl;
        return;
    }

    std::cout << circles.size() << std::endl;

    std::cout << "nyomjuk" << std::endl;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        std::cout << "nagyon" << std::endl;
        int num_samples = std::max(static_cast<int>(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) / radius), 1);
        for (int i = 0; i <= num_samples; ++i) {
            float t = static_cast<float>(i) / num_samples;
            float vx = x1 * (1 - t) + x2 * t;
            float vy = y1 * (1 - t) + y2 * t;
            std::vector<float> currentCircle = Drawing::drawCircle(vx, vy, radius, sides);
            circles.push_back(currentCircle);
        }
    }


    prevXpos = xpos;
    prevYpos = ypos;
}