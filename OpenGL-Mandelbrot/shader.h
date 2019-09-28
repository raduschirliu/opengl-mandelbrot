#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Wrapper for OpenGL shader loading and attaching functions
class Shader
{
	public:
		// Create a new shader ID with specified type
		Shader(GLenum type);
		
		// Read and compile shader from file
		void load(const char* file);

		// Attach shader to program ID
		void attach(GLuint program);

	private:
		GLuint id;
};