#pragma once

#include <vector>

struct VertexBufferElement 
{

};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> elements;
public:
	VertexBufferLayout();
	~VertexBufferLayout();
	

};