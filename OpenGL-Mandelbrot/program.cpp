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

int Program::getUniformLocation(const char* name)
{
	return glGetUniformLocation(id, name);
}

void Program::setUniform(const char* name, int v1)
{
	glUniform1i(getUniformLocation(name), v1);
}

void Program::setUniform(const char* name, float v1)
{
	glUniform1f(getUniformLocation(name), v1);
}

void Program::setUniform(const char* name, float v1, float v2)
{
	glUniform2f(getUniformLocation(name), v1, v2);
}

void Program::setUniform(const char* name, double v1, double v2)
{
	glUniform2d(getUniformLocation(name), v1, v2);
}

void Program::setUniform(const char* name, float v1, float v2, float v3, float v4)
{
	glUniform4f(getUniformLocation(name), v1, v2, v3, v4);
}