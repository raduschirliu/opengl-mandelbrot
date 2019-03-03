#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
	public:
		Shader(GLenum type);
		void load(const char* file);
		void compile();
		void attach(GLuint program);

	private:
		GLuint id;
};