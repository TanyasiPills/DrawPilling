#pragma once

#include <GLFW/glfw3.h>
#include "GLEW/glew.h"
#include <vector>

class GLManager {
public:
	void initBuffers(unsigned int& VBO, unsigned int& VAO);

	void updateVBO(const std::vector<float>& vertices);

	void drawStuff(unsigned int& VAO, GLenum mode, const std::vector<float>& vertices);
};