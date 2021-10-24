
#include"GL\glew.h"
#include"GLFW/glfw3.h"

using namespace std;

#include "Window.h"
#include "Shader.h"
#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static glm::vec4 LeftBarVec(-1.0f, 0.5f, 0.0f, 1.0f);
static glm::vec4 RightBarVec(1.0f, 0.5f, 0.0f, 1.0f);

void key_callback(GLFWwindow* window, int key, int scancode, int action,
	int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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

	GLuint indices1[] = {
		0, 1, 2,
		3, 0, 2
	};

	GLfloat vertices1[] = {
		-1.0f,  1.0f, //0
		-1.0f,  0.5f, //1
		-0.95f, 0.5f, //2
		-0.95f, 1.0f  //3
	};

	GLfloat vertices2[] = {
		1.0f,  1.0f, //0
		1.0f,  0.5f, //1
		0.95f, 0.5f, //2
		0.95f, 1.0f  //3
	};

	Mesh LeftBar(vertices1, 8, indices1, 6);
	Mesh RightBar(vertices2, 8, indices1, 6);

	Shader shader("Source/Shader/vertex.glsl", "Source/Shader/fragment.glsl");

	GLfloat r = 0.0f, g = 0.0f, b = 1.0f;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Bind();

		LeftBar.Render();

		RightBar.Render();

		shader.UnBind();

		glfwSwapBuffers(window);
	}

	return 0;
}