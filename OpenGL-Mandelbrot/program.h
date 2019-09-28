#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "shader.h"

// Wrapper for all OpenGL program/shader functions
class Program
{
	public:
		// Create a new program ID
		void create();

		// Create a new shader and add it to the program
		void addShader(GLenum type, const char* filePath);
		
		// Link the OpenGL program
		void link();

		// Use the OpenGL program
		void use();

		// Clear current OpenGL program
		void clear();

		// Return location of uniform by name
		int getUniformLocation(const char* name);
		
		// Set uniform variable inside shader
		void setUniform(const char* name, int v1);
		void setUniform(const char* name, float v1);
		void setUniform(const char* name, float v1, float v2);
		void setUniform(const char* name, double v1, double v2);
		void setUniform(const char* name, float v1, float v2, float v3, float v4);
		
		// Program ID
		GLuint id;

	private:
		std::vector<Shader> shaders;
};