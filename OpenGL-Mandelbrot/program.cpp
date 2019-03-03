#include "program.h"

void Program::create()
{
	id = glCreateProgram();
}

void Program::addShader(GLenum type, const char* filePath)
{
	Shader shader(type);
	shader.load(filePath);
	shader.attach(id);

	shaders.push_back(shader);
}

void Program::link()
{
	glLinkProgram(id);
}

void Program::use()
{
	glUseProgram(id);
}