#include "GLManager.h"
#include <GLFW/glfw3.h>
#include "GLEW/glew.h"

void GLManager::initBuffers(unsigned int& VBO, unsigned int& VAO) {
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
}

void GLManager::updateVBO(const std::vector<float>& vertices) {
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
}

void GLManager::drawStuff(unsigned int& VAO,GLenum mode, const std::vector<float>& vertices) {
	glBindVertexArray(VAO);
	glDrawArrays(mode, 0, static_cast<GLsizei>(vertices.size() / 2));
	glBindVertexArray(0);
}
