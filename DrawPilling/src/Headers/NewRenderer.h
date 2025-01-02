#pragma once

#include "VertexArray.h"
#include "NewShader.h"
#include "IndexBuffer.h"

class NewRenderer {
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const NewShader& shader) const;
};