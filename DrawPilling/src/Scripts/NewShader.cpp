#include "NewShader.h"
#include "GLEW/glew.h"
#include <GLFW/glfw3.h> 
#include <fstream>
#include <sstream>
#include <iostream>


NewShader::NewShader(const std::string& filepath) : shaderId(0)
{
    ShaderSource source = ParseShader(filepath);
    shaderId = CreateShader(source.Vertex, source.Fragment);
}
NewShader::~NewShader()
{
    glDeleteProgram(shaderId);
}

void NewShader::Bind() const
{
    glUseProgram(shaderId);
}
void NewShader::UnBind() const
{
    glUseProgram(0);
}

unsigned int NewShader::GetUniformLocation(const std::string& name)
{
    if (UniformLocs.find(name) != UniformLocs.end())
        return UniformLocs[name];

    unsigned int location = glGetUniformLocation(shaderId, name.c_str());
    UniformLocs[name] = location;
    return location;
}

void NewShader::SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4)
{
    glUniform4f(GetUniformLocation(name), f1, f2, f3, f4);
}


unsigned int NewShader::CompileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = (char*)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

ShaderSource NewShader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }
    return { ss[0].str(), ss[1].str() };
}

unsigned int NewShader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{

    ShaderSource source = NewShader::ParseShader("Resources/shaders/Style.shader");

    unsigned int program = glCreateProgram();
    unsigned int vertShader = NewShader::CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fragShader = NewShader::CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    glUseProgram(program);

    return program;
}