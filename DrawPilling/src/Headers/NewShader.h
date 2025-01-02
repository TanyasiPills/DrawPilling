#pragma once

#include <string>
#include <unordered_map>

struct ShaderSource {
	std::string Vertex;
	std::string Fragment;
};

class NewShader 
{
private:
	unsigned int shaderId;
	std::unordered_map<std::string, int> UniformLocs;
public:
	NewShader(const std::string& filepath);
	~NewShader();

	void Bind() const;
	void UnBind() const;

	void SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4);
private:
	ShaderSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(const std::string& source, unsigned int type);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int GetUniformLocation(const std::string& name);
};
