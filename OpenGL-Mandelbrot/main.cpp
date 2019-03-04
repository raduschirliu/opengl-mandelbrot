#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "program.h"

GLFWwindow* window;
Program program;

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
	program.setUniform("iters", 100);
	program.setUniform("limit", 25.0f);

	glBegin(GL_QUADS);
		glVertex2f(-1, -1);
		glVertex2f(1, -1);
		glVertex2f(1, 1);
		glVertex2f(-1, 1);
	glEnd();

	glfwSwapBuffers(window);
	glfwPollEvents();
}

int main()
{
	if (!glfwInit())
	{
		printf("Failed to initialize GLFW\n");
		return 1;
	}

	glfwSetErrorCallback(errorCallback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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