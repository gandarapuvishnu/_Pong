#pragma once

#include "GL\glew.h"

class Mesh
{
private:
	GLuint MeshId, VAO, VBO, EBO, indexCount;
public:
	Mesh();
	void CreateMesh(const GLfloat* vertices, const GLuint numVertices, const GLuint* indices, const GLuint numIndices);
	~Mesh();
	void Render();
};