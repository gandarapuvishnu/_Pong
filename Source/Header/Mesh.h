#pragma once

#include "GL\glew.h"

class Mesh
{
private:
	GLuint MeshId, VAO, VBO, EBO, indexCount;
public:
	Mesh(const GLfloat* vertices, const GLuint numVertices, const GLuint* indices, const GLuint numIndices) :indexCount(numIndices)
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices,
				GL_STATIC_DRAW);
		glBindVertexArray(0);
	}
	void Render()
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	}
	~Mesh()
	{
		glDeleteVertexArrays(1, &VAO);
	}
};
