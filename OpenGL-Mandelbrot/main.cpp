#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "program.h"

GLFWwindow* window;
Program program;
int iters = 300;
int width, height;
bool isDragging = false;
double mouseStartX, mouseStartY;
double minX = -2, maxX = 1;
double minY = -1.5, maxY = 1.5;
double zoomSpeed = 0.005;
double targetX = -1.375;
double targetY = 0;
double targetSpeed = 0.005;

double lerp(double start, double end, double p)
{
	return start + (end - start) * p;
}

double map(double value, double inMin, double inMax, double outMin, double outMax)
{
	return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
}

void errorCallback(int error, const char* desc)
{
	printf("GLFW Error: %s\n", desc);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		minX = -2, maxX = 1;
		minY = -1.5, maxY = 1.5;
		iters = 300;
		printf("\nReset view\n\n");
		isDragging = false;
	}

	if (button != GLFW_MOUSE_BUTTON_LEFT) return;

	double x, y;
	glfwGetCursorPos(window, &x, &y);

	if (action == GLFW_PRESS)
	{
		isDragging = true;
		mouseStartX = x;
		mouseStartY = y;
	}
	else if (action == GLFW_RELEASE && isDragging)
	{
		double newMinX = map(mouseStartX, 0, width, minX, maxX);
		double newMinY = map(mouseStartY, 0, height, minY, maxY);
		
		maxX = map(x, 0, width, minX, maxX);
		maxY = map(y, 0, height, minY, maxY);

		minX = newMinX;
		minY = newMinY;

		isDragging = false;

		printf("New Bounds:\n\tX: %lf : %lf\tY: %lf : %lf\n", minX, maxX, minY, maxY);
	}
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	iters = iters + yOffset * 300;
	
	if (iters < 300) iters = 300;

	printf("Iterations: %i\n", iters);
}

void draw()
{
	glfwGetFramebufferSize(window, &width, &height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	glOrtho(0, width, height, 0, -1, 1);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	program.use();
	program.setUniform("width", width);
	program.setUniform("height", height);
	program.setUniform("iters", iters);

	program.setUniform("xBounds", minX, maxX);
	program.setUniform("yBounds", minY, maxY);

	glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(width, 0);
		glVertex2f(width, height);
		glVertex2f(0, height);
	glEnd();

	glUseProgram(0);

	if (isDragging)
	{
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		glBegin(GL_QUADS);
			glColor4f(0.8f, 0.1f, 0.1f, 0.6f);
			glVertex2f(mouseStartX, mouseStartY);
			glVertex2f(mouseX, mouseStartY);
			glVertex2f(mouseX, mouseY);
			glVertex2f(mouseStartX, mouseY);
		glEnd();
	}

	glfwSwapBuffers(window);
	glfwPollEvents();
}

int main()
{
	printf("Running...\n");

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glfwSetMouseButtonCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	while (!glfwWindowShouldClose(window))
	{
		draw();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}