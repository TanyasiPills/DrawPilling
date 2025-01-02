#include "VertexBuffer.h"
#include "GLEW/glew.h"
#include <GLFW/glfw3.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &VBO);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}
void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}