#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
	unsigned int VAO;
public:
	VertexArray();
	~VertexArray();

	void SetBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
	void Bind() const;
	void UnBind() const;
};