
#include"GL\glew.h"
#include"GLFW/glfw3.h"

using namespace std;

#include "Window.h"
#include "Shader.h"
#include "Mesh.h"

#include <math.h>
double pi = 3.14159265359;

#define rad(x) (x * (pi / 180))

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLfloat LeftBarOffset = 0.0f, RightBarOffset = 0.0f, yIncrement = 0.1f;

void key_callback(GLFWwindow* window, int key, int scancode, int action,
	int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		LeftBarOffset += yIncrement;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		LeftBarOffset -= yIncrement;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		RightBarOffset += yIncrement;
	}
	else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		RightBarOffset -= yIncrement;
	}
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

	GLuint BarIndices[6] = {
		0, 1, 2,
		3, 0, 2
	};
	GLuint BarnV = 4 * 2, BarnI = 6;
	GLfloat LeftBarVertices[4 * 2] = {
		-1.0f,  1.0f,
		-1.0f,  0.5f,
		-0.95f, 0.5f,
		-0.95f, 1.0f
	};

	GLfloat RightBarVertices[4 * 2] = {
		1.0f,  1.0f,
		1.0f,  0.5f,
		0.95f, 0.5f,
		0.95f, 1.0f
	};

	GLfloat BallVertices[361 * 2];
	GLuint BallIndices[359 * 3];
	GLuint BallnV = 361 * 2, BallnI = 359 * 3;
	GLfloat radius = 0.10f, angle = 0.0f;

	BallVertices[0] = BallVertices[1] = 0.0f;
	for (int i = 0; i < 360 * 2; i++)
	{
		if (i % 2 == 0)
		{
			BallVertices[i + 2] = radius * (GLfloat)cos(rad(angle));
		}
		else if (i & 1)
		{
			BallVertices[i + 2] = radius * (GLfloat)sin(rad(angle));
			angle++;
		}
	}

	GLuint current = 1;
	for (int i = 0; i < 358 * 3; i += 3)
	{
		BallIndices[i] = 0;
		BallIndices[i + 1] = current;
		BallIndices[i + 2] = current + 1;
		++current;
	}
	BallIndices[358 * 3] = 0;
	BallIndices[358 * 3 + 1] = 359;
	BallIndices[358 * 3 + 2] = 1;


	Mesh Ball(BallVertices, BallnV, BallIndices, BallnI);
	Mesh LeftBar(LeftBarVertices, BarnV, BarIndices, BarnI);
	Mesh RightBar(RightBarVertices, BarnV, BarIndices, BarnI);

	Shader shader("Source/Shader/vertex.glsl", "Source/Shader/fragment.glsl");

	GLfloat r = 0.0f, g = 0.0f, b = 1.0f;
	bool directionX = true, directionY = true;
	GLfloat BallOffsetX = 0.0f, BallOffsetY = 0.0f, BallMaxOffsetX = 0.9f, BallMaxOffsetY = 0.8f, Increment = 0.01f;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (directionX)
			BallOffsetX += Increment;
		else
			BallOffsetX -= Increment;

		if (directionY)
			BallOffsetY += Increment;
		else
			BallOffsetY -= Increment;

		if (abs(BallOffsetX) >= BallMaxOffsetX)
			directionX = !directionX;
		if (abs(BallOffsetY) >= BallMaxOffsetY)
			directionY = !directionY;

		shader.Bind();

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, LeftBarOffset, 0.0f));
		glUniform3f(shader.GetColorLocation(), 1.0, 0.0, 0.0);
		glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
		LeftBar.Render();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, RightBarOffset, 0.0f));
		glUniform3f(shader.GetColorLocation(), 0.0, 1.0, 0.0);
		glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
		RightBar.Render();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(BallOffsetX, BallOffsetY, 0.0f));
		glUniform3f(shader.GetColorLocation(), 1.0, 1.0, 0.0);
		glUniformMatrix4fv(shader.GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));
		Ball.Render();

		shader.UnBind();

		glfwSwapBuffers(window);
	}

	return 0;
}