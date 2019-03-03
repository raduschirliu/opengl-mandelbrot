#include "shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

Shader::Shader(GLenum type)
{
	id = glCreateShader(type);
}

void Shader::load(const char* filePath)
{
	std::ifstream file(filePath);

	if (file.is_open())
	{
		std::string str;
		std::string line;

		while (!file.eof())
		{
			std::getline(file, line);
			str += line;
			str.push_back('\n');
		}
		
		const char* cStr = str.c_str();
		glShaderSource(id, 1, &cStr, NULL);
		glCompileShader(id);

		int success;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			char info[512];
			glGetShaderInfoLog(id, 512, NULL, info);
			printf("Shader compilation error for '%s': %s\n", filePath, info);
		}
	}

	file.close();
}

void Shader::attach(GLuint program)
{
	glAttachShader(program, id);
}