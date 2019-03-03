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
	
	private:
		std::vector<Shader> shaders;
		GLuint id;
};