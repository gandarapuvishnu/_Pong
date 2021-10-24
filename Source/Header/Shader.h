#pragma once

#include "GL\glew.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Shader
{
private:
	GLint success;
	GLchar infoLog[512];
	GLuint shaderProgram, vertexShader, fragmentShader;
	string vertexShaderSource, fragmentShaderSource;

public:
	GLuint GetShaderProgram() { return shaderProgram; }
	string ReadFromFile(const char* ShaderPath)
	{
		ifstream ShaderFile;
		ShaderFile.open(ShaderPath);
		stringstream ShaderStream;
		ShaderStream << ShaderFile.rdbuf();
		ShaderFile.close();

		return ShaderStream.str();
	}
	Shader(const char* vShaderPath, const char* fShaderPath)
	{
		vertexShaderSource = ReadFromFile(vShaderPath);
		fragmentShaderSource = ReadFromFile(fShaderPath);
		vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource.c_str());
		fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource.c_str());

		shaderProgram = LinkProgram();
	}
	~Shader()
	{
		glDeleteProgram(shaderProgram);
	}
	GLuint CompileShader(GLuint type, const GLchar* shaderSource)
	{
		GLuint Shader = glCreateShader(type);
		glShaderSource(Shader, 1, &shaderSource, NULL);
		glCompileShader(Shader);
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(Shader, 512, NULL, infoLog);
			if (type == GL_VERTEX_SHADER)
				cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED - " <<
				infoLog << endl;
			else if (type == GL_FRAGMENT_SHADER)
				cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED - " <<
				infoLog << endl;
		}
		return Shader;
	}

	GLuint LinkProgram()
	{
		GLuint Program = glCreateProgram();
		glAttachShader(Program, vertexShader);
		glAttachShader(Program, fragmentShader);
		glLinkProgram(Program);
		glGetProgramiv(Program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(Program, 512, NULL, infoLog);
			cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED - " <<
				infoLog << endl;
		}

		glValidateProgram(Program);
		glGetProgramiv(Program, GL_VALIDATE_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(Program, 512, NULL, infoLog);			cout << "ERROR::SHADER::PROGRAM::VALIDATING_FAILED - " << infoLog << endl;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return Program;
	}

	void Bind()
	{
		glUseProgram(shaderProgram);
	}

	void UnBind()
	{
		glUseProgram(0);
	}
};
