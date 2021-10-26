#pragma once

#include"GL\glew.h"

#include <math.h>
double pi = 3.14159265359;

#define rad(x) (x * (pi / 180))

GLfloat randomFloat(GLfloat low, GLfloat high)
{
	return low + static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX / (high - low));
}

GLfloat randomFloat()
{
	return static_cast <GLfloat> (rand()) / static_cast <GLfloat> (RAND_MAX);
}

struct Bar
{
	GLuint nV = 4 * 2, nI = 6;
	GLuint Indices[6] = {
		0, 1, 2,
		3, 0, 2
	};
	GLfloat Increment = 0.1f;
	GLfloat MaxOffset = 0.0f, MinOffset = -1.5f;
};

#include <glm/glm.hpp>

struct LeftBar
{
	GLfloat Vertices[4 * 2] = {
		-1.0f,  1.0f,
		-1.0f,  0.5f,
		-0.95f, 0.5f,
		-0.95f, 1.0f
	};
	glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
	GLfloat Offset = randomFloat(-1.5f, 0.0f);
	GLfloat centerPosX = -0.975f, centerPosY = Offset + 0.75f;
};

struct RightBar
{
	GLfloat Vertices[4 * 2] = {
		1.0f,  1.0f,
		1.0f,  0.5f,
		0.95f, 0.5f,
		0.95f, 1.0f
	};
	glm::vec3 color = glm::vec3(0.0f, 1.0f, 0.0f);
	GLfloat Offset = randomFloat(-1.5f, 0.0f);
	GLfloat centerPosX = 0.975f, centerPosY = Offset + 0.75f;
};

struct Ball
{
	Ball()
	{
		CreateVertices();
		CreateIndices();
		OffsetX = randomFloat(-0.9f, 0.9f);
		OffsetY = randomFloat(-0.9f, 0.9f);
		InitialiseDirection();
	}
	void InitialiseDirection()
	{
		GLfloat randomDirectionX = randomFloat(), randomDirectionY = randomFloat();
		if (randomDirectionX > 0.5f)
			directionX = true;
		if (randomDirectionY > 0.5f)
			directionY = false;
	}
	void CreateVertices()
	{
		Vertices[0] = Vertices[1] = 0.0f;
		for (int i = 0; i < 360 * 2; i++)
		{
			if (i % 2 == 0)
				Vertices[i + 2] = radius * (GLfloat)cos(rad(angle));
			else if (i & 1)
			{
				Vertices[i + 2] = radius * (GLfloat)sin(rad(angle));
				angle++;
			}
		}
	}

	void Move()
	{
		if (directionX)
			OffsetX += Increment;
		else
			OffsetX -= Increment;

		if (directionY)
			OffsetY += Increment;
		else
			OffsetY -= Increment;
	}

	void CreateIndices()
	{
		GLuint current = 1;
		for (int i = 0; i < 358 * 3; i += 3)
		{
			Indices[i] = 0;
			Indices[i + 1] = current;
			Indices[i + 2] = current + 1;
			++current;
		}
		Indices[358 * 3] = 0;
		Indices[358 * 3 + 1] = 359;
		Indices[358 * 3 + 2] = 1;
	}
	GLfloat Vertices[361 * 2];
	GLuint Indices[359 * 3];
	bool directionX = false, directionY = true;
	GLuint nV = 361 * 2, nI = 359 * 3;
	GLfloat radius = 0.10f, angle = 0.0f;
	GLfloat OffsetX, OffsetY;
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 0.0f);
	GLfloat MaxOffsetX = 0.9f, MaxOffsetY = 0.9f, Increment = 0.01f;
	bool CollisionwLeftBar = false, CollisionwRightBar = false;
};
