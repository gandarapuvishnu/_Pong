#pragma once

#include "GL\glew.h"

#include <string>

using namespace std;

class Shader
{
private:
	GLint success;
	GLchar infoLog[512];
	GLuint shaderProgram, vertexShader, fragmentShader, uniformModel, uniformColor;
	string vertexShaderSource, fragmentShaderSource;

public:
	string ReadFromFile(const char* ShaderPath);
	Shader(const char* vShaderPath, const char* fShaderPath);
	~Shader();
	void CompileUniforms();
	GLuint GetModelLocation() { return uniformModel;  }
	GLuint GetColorLocation() { return uniformColor;  }
	GLuint CompileShader(GLuint type, const GLchar* shaderSource);
	GLuint LinkProgram();

	void Bind() const;
	void UnBind() const;
};
