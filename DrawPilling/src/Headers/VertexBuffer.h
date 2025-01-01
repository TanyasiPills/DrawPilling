#pragma once


class VertexBuffer
{
private:
	unsigned int VBO;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind();
	void Unbind();

	void UpdateData();
};

