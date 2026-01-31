#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Logger.h"

class window
{
private:
	unsigned int shaderProgram;
	GLFWwindow* window;

public:
	void initialise();
	void generateShaders();
	void render();


private:
	


};

