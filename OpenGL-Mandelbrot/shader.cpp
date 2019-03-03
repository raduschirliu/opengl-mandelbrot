#include "shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>

Shader::Shader(GLenum type)
{
	id = glCreateShader(type);
}

void Shader::load(const char* file)
{
	std::ifstream fileStream;
	fileStream.open(file);

	char* text = new char();
	
	if (fileStream.is_open())
	{
		while (!fileStream.eof())
		{
			fileStream >> text;
		}
	}

	fileStream.close();
	glShaderSource(id, 1, &text, NULL);
}

void Shader::compile()
{
	glCompileShader(id);
}

void Shader::attach(GLuint program)
{
	glAttachShader(program, id);
}