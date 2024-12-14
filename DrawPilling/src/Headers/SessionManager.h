#pragma once

struct SessionData
{
	int screenWidth;
	int screenHeight;
	GLFWwindow* window;
};


class Manager {
public:
	static SessionData Assembly(GLFWerrorfun glfw_error_callback);
	static void DisAssembly(GLFWwindow* window, unsigned int shader);
};
