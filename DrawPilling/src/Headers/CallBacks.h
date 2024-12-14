#pragma once

class CallBackManager {
public:
	 static void SetCallBacks(GLFWwindow* window, unsigned int* VBO, unsigned int* VAO, float* size, bool* hover);
	 static void ProcessInput(GLFWwindow* window);
};