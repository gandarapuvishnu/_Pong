#include "Mesh.h"

Mesh::Mesh()
{
	MeshId = 0;
}

void Mesh::CreateMesh(const GLfloat* vertices, const GLuint numVertices, const GLuint* indices, const GLuint numIndices)
{
	indexCount = numIndices;

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
void Mesh::Render()
{
	glBindVertexArray(VAO);
	// Wireframe
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
}