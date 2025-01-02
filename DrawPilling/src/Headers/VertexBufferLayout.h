#pragma once

#include <vector>
#include "GLEW/glew.h"

struct VertexBufferElement 
{
	unsigned int count;
	unsigned int type;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type) 
	{
		switch (type)
		{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 3;
			case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> elements;
	unsigned int stride;
public:
	VertexBufferLayout() : stride(0) {};
	~VertexBufferLayout();
	
	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	void Push<unsigned int>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	void Push<unsigned char>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return elements; }
	inline unsigned int GetStride() const { return stride; }

};