#pragma once
#include"GLFW/glfw3.h"
#include"GL\glew.h"

#include <iostream>
using namespace std;

GLFWwindow* InitializeWindow(int width, int height)
{
	if (!glfwInit())
	{
		cout << "Failed to initialize GLFW\n";
		return nullptr;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Pong", nullptr,
		nullptr);
	if (window == nullptr)
	{
		cout << "Failed to create GLFW window" << endl;
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << endl;
		return nullptr;
	}

	cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl;
	glViewport(0, 0, width, height);
	return window;
}
