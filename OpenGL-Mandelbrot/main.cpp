#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

GLFWwindow* window;
GLuint fragShader;

void errorCallback(int error, const char* desc)
{
	printf("GLFW Error: %s\n", desc);
}

void draw()
{
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);



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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(640, 480, "Mandelbrot", NULL, NULL);

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
	}

	while (!glfwWindowShouldClose(window))
	{
		draw();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}