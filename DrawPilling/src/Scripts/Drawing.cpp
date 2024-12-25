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

struct CordData {
    float x;
    float y;
};

static float* xRatio;
static float* yRatio;
float* xOffset;
float* yOffset;
float* scale;

static bool pressed = false;

void Drawing::initDrawData(Ratios& ratios){
    xRatio = ratios.xRatio;
    yRatio = ratios.xRatio;
    xOffset = ratios.xOffset;
    yOffset = ratios.yOffset;
    scale = ratios.scale;
}

std::vector<float> Drawing::drawCircle(float& x, float& y, float& r, int& sides) {
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

void Drawing::handleCanvasMovement(GLFWwindow* window) {

}

CordData GetCordData(double& xpos, double& ypos, int& width, int& height) {
    CordData data;
    data.x = ((((static_cast<float>(xpos) / width) / *xRatio) - (*xOffset / 2) * *scale) * 2.0f - 1.0f) / *scale;
    data.y = ((((-static_cast<float>(ypos) / height + 1) / *yRatio) - (*yOffset / 2) * *scale) * 2.0f - 1.0f) / *scale;
    return data;
}

void Drawing::handleCursorMovement(GLFWwindow* window, double& prevXpos, double& prevYpos, std::vector<std::vector<float>>& circles, GLuint VBO, GLuint VAO, float radius, int sides, bool hover) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    CordData prev = GetCordData(prevXpos, prevYpos, width, height);
    CordData now = GetCordData(xpos, ypos, width, height);

    /*
    float x2 = static_cast<float>(xpos) / width;
    float y2 = -static_cast<float>(ypos) / height + 1;
    x2 /= *xRatio;
    y2 /= *yRatio;
    x2 -= (*xOffset / 2) * *scale;
    y2 -= (*yOffset / 2) * *scale;
    x2 = x2 * 2.0f - 1.0f;
    y2 = y2 * 2.0f - 1.0f;
    x2 /= *scale; 
    y2 /= *scale;
    */
    

    std::vector<float> currentCircle = Drawing::drawCircle(now.x, now.y, radius, sides);
    GLManager::updateVBO(VBO, currentCircle);
    GLManager::drawStuff(VAO, GL_TRIANGLE_FAN, currentCircle);

    if (hover || ImGui::IsAnyItemHovered())
    {
        return;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        if (prev.x == now.x && prev.y == now.y) return;
        //int num_samples = std::max(static_cast<int>(sqrt((now.x - prev.x) * (now.x - prev.x) + (now.y - prev.y) * (prev.y - prev.y)) / radius), 4);
        int num_samples = std::max(static_cast<int>(std::exp(std::sqrt((now.x - prev.x) * (now.x - prev.x) + (now.y - prev.y) * (now.y - prev.y)) / radius)), 4);
        for (int i = 0; i <= num_samples; ++i) {
            float t = static_cast<float>(i) / num_samples;
            float vx = prev.x * (1 - t) + now.x * t;
            float vy = prev.y * (1 - t) + now.y * t;
            std::vector<float> currentCircle = Drawing::drawCircle(vx, vy, radius, sides);
            circles.push_back(currentCircle);
        }
    }

    prevXpos = xpos;
    prevYpos = ypos;
}