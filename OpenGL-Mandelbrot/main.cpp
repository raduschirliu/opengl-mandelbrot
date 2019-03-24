#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "program.h"

GLFWwindow* window;
Program program;
float minX = -2;
float maxX = 1;

float lerp(float start, float end, float p)
{
	return start + (end - start) * p;
}

void errorCallback(int error, const char* desc)
{
	printf("GLFW Error: %s\n", desc);
}

void draw()
{
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	program.use();
	program.setUniform("width", width);
	program.setUniform("height", height);

	program.setUniform("xBounds", minX, maxX);
	program.setUniform("yBounds", -1.5, 1.5);

	glBegin(GL_QUADS);
		glVertex2f(-1, -1);
		glVertex2f(1, -1);
		glVertex2f(1, 1);
		glVertex2f(-1, 1);
	glEnd();

	glfwSwapBuffers(window);
	glfwPollEvents();

	minX = lerp(minX, -2, 0.01);
	maxX = lerp(maxX, -1, 0.01);
}

int main()
{
	if (!glfwInit())
	{
		printf("Failed to initialize GLFW\n");
		return 1;
	}

	glfwSetErrorCallback(errorCallback);

	glfwWindowHint(GLFW_RESIZABLE, 0);

	window = glfwCreateWindow(1024, 768, "Mandelbrot", NULL, NULL);

	if (!window)
	{
		printf("Failed to create window\n");
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit())
	{
		printf("Glew init failed");
		return 1;
	}

	program.create();
	program.addShader(GL_FRAGMENT_SHADER, "shader.frag");
	program.link();


	while (!glfwWindowShouldClose(window))
	{
		draw();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}