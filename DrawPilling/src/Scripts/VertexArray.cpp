#include "VertexArray.h"

VertexArray::VertexArray() 
{
	glGenVertexArrays(1, &VAO);
}
VertexArray::~VertexArray() 
{
	glDeleteVertexArrays(1, &VAO);
}

void VertexArray::SetBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout) 
{
	Bind();
	vertexBuffer.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) 
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}

void VertexArray::Bind() const
{
	glBindVertexArray(VAO);
}
void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}