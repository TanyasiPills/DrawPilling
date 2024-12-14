#pragma once

class Renderer {
public:
	static void RenderScreen(GLFWwindow* window, unsigned int& VBO, unsigned int& VAO, float* size, bool* hover);
	static void RenderUI(GLint& colorLoc, float* size, bool* hover);
};