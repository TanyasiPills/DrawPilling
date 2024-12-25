#pragma once

struct Ratios {
	float* xRatio;
	float* yRatio;
};

class CallBackManager {
public:
	 static Ratios SetCallBacks(GLFWwindow* window, unsigned int* VBO, unsigned int* VAO, float* size, bool* hover, GLint& xLoc, GLint& yLoc);
	 static void ProcessInput(GLFWwindow* window);
};