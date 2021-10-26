
#include"GL\glew.h"
#include"GLFW/glfw3.h"

#include <iostream>
using namespace std;

#include "Window.h"
#include "Shader.h"
#include "Mesh.h"
#include "Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh m_LeftBar, m_RightBar, m_Ball;

Bar bar;
Ball ball;
LeftBar leftBar;
RightBar rightBar;

void key_callback(GLFWwindow* window, int key, int scancode, int action,
	int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		leftBar.Offset += bar.Increment;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		leftBar.Offset -= bar.Increment;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		rightBar.Offset += bar.Increment;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		rightBar.Offset -= bar.Increment;
	}
}

void CheckForCollision()
{
	GLfloat rdist, ldist;
	rdist = sqrt((ball.OffsetX - rightBar.centerPosX)* (ball.OffsetX - rightBar.centerPosX) + ((rightBar.centerPosY) - ball.OffsetY) * ((rightBar.centerPosY) - ball.OffsetY));
	ldist = sqrt((ball.OffsetX - leftBar.centerPosX) * (ball.OffsetX - leftBar.centerPosX) + ((leftBar.centerPosY) - ball.OffsetY) * ((leftBar.centerPosY) - ball.OffsetY));

	if (rdist <= 0.18f)
		ball.CollisionwRightBar = true;
	else if (ldist <= 0.18f)
		ball.CollisionwLeftBar = true;
}

int main()
{
	cout << "Welcome to Pong!" << endl;

	GLFWwindow* window = InitializeWindow(640, 480);
	if (window == nullptr)
	{
		glfwTerminate();
		return -1;
	}
	glfwSetKeyCallback(window, key_callback);

	m_Ball.CreateMesh(ball.Vertices, ball.nV, ball.Indices, ball.nI);
	m_LeftBar.CreateMesh(leftBar.Vertices, bar.nV, bar.Indices, bar.nI);
	m_RightBar.CreateMesh(rightBar.Vertices, bar.nV, bar.Indices, bar.nI);

	Shader shader("Source/Shader/vertex.glsl", "Source/Shader/fragment.glsl");

	while (!glfwWindowShouldClose(window))
	{
		if (leftBar.Offset < bar.MinOffset) leftBar.Offset = bar.MinOffset;
		if (leftBar.Offset > bar.MaxOffset) leftBar.Offset = bar.MaxOffset;
		if (rightBar.Offset < bar.MinOffset) rightBar.Offset = bar.MinOffset;
		if (rightBar.Offset > bar.MaxOffset) rightBar.Offset = bar.MaxOffset;

		if (ball.OffsetX < -0.9f || ball.OffsetX > 0.9f)
			ball.directionX = !ball.directionX;
		if (ball.OffsetY < -0.9f || ball.OffsetY > 0.9f)
			ball.directionY = !ball.directionY;

		CheckForCollision();

		glfwPollEvents();
		if (ball.CollisionwLeftBar)
		{
			glClearColor(leftBar.color.x, leftBar.color.y, leftBar.color.z, 1.0f);
			ball.directionX = !ball.directionX;
			ball.CollisionwLeftBar = false;
		}
		else if (ball.CollisionwRightBar)
		{
			glClearColor(rightBar.color.x, rightBar.color.y, rightBar.color.z, 1.0f);
			ball.directionX = !ball.directionX;
			ball.CollisionwRightBar = false;
		}
		else
			glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ball.Move();

		shader.Bind();

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, leftBar.Offset, 0.0f));
		glUniform3f(shader.GetColorLocation(), leftBar.color.x, leftBar.color.y, leftBar.color.z);
		glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
		m_LeftBar.Render();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, rightBar.Offset, 0.0f));
		glUniform3f(shader.GetColorLocation(), rightBar.color.x, rightBar.color.y, rightBar.color.z);
		glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
		m_RightBar.Render();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(ball.OffsetX, ball.OffsetY, 0.0f));
		glUniform3f(shader.GetColorLocation(), ball.color.x, ball.color.y, ball.color.z);
		glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
		m_Ball.Render();

		shader.UnBind();

		glfwSwapBuffers(window);
	}

	return 0;
}