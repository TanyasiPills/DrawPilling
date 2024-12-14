#pragma once
#include <iostream>

struct ShaderSource {
    std::string Vertex;
    std::string Fragment;
};

class Shadering {
public:
	static ShaderSource ParseShader(const std::string& filepath);
    static unsigned int ComplileShader(const std::string& source, unsigned int type);
    static unsigned int CreateShader();
};