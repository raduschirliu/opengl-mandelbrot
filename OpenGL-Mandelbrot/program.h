#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "shader.h"

class Program
{
	public:
		void create();
		void addShader(GLenum type, const char* filePath);
		void link();
		void use();

		int getUniformLocation(const char* name);
		void setUniform(const char* name, int v1);
		void setUniform(const char* name, float v1);
		void setUniform(const char* name, float v1, float v2);
		void setUniform(const char* name, float v1, float v2, float v3, float v4);
		
		GLuint id;

	private:
		std::vector<Shader> shaders;
};