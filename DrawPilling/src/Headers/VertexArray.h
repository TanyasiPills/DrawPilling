#pragma once

#include "VertexBuffer.h"

class VertexArray {
private:

public:
	VertexArray();
	~VertexArray();

	void SetBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);
};