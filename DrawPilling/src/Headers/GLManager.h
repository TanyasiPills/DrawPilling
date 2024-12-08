#pragma once

#include "GLEW/glew.h"
#include <GLFW/glfw3.h>
#include <vector>

class GLManager {
public:
	static void initBuffers(unsigned int& VBO, unsigned int& VAO);

	static void updateVBO(unsigned int& VBO, const std::vector<float>& vertices);

	static void drawStuff(unsigned int& VAO, GLenum mode, const std::vector<float>& vertices);
};