#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "program.h"


GLFWwindow* window;
Program program;
int iters = 300;
int width, height;
bool isDragging = false;
double mouseStartX, mouseStartY;
double minX = -2, maxX = 1;
double minY = -1.5, maxY = 1.5;


// Linearly interpolates between two values
double lerp(double start, double end, double p)
{
	return start + (end - start) * p;
}

double map(double value, double inMin, double inMax, double outMin, double outMax)
{
	return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
}

// Called on GLFW errors
void errorCallback(int error, const char* desc)
{
	printf("\nGLFW Error: %s\n\n", desc);
}

// Called on mouse events
void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
	// Reset view by right clicking
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		if (isDragging)
		{
			printf("Cancelled selection\n");
			isDragging = false;
		}
		else
		{
			minX = -2, maxX = 1;
			minY = -1.5, maxY = 1.5;
			iters = 300;
			printf("Reset view\n");
			isDragging = false;
		}

		return;
	}

	double x, y;
	glfwGetCursorPos(window, &x, &y);

	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	{
		double xp = map(x, 0, width, minX, maxX);
		double yp = map(y, 0, height, minY, maxY);
		printf("(%lf, %lf)\t(%lf, %lf)\n", xp, yp, x, y);

		return;
	}	

	// Choose new view rect by left-click and dragging
	if (button != GLFW_MOUSE_BUTTON_LEFT) return;

	if (action == GLFW_PRESS)
	{
		isDragging = true;

		// Contain values to window
		if (x < 0) x = 0;
		if (y < 0) y = 0;

		if (x > width) x = width;
		if (y > height) y = height;

		mouseStartX = x;
		mouseStartY = y;
	}
	else if (action == GLFW_RELEASE && isDragging)
	{
		// Prevent accidentally setting viewport to be 1x1 px
		if (mouseStartY == y && mouseStartX == x)
		{
			isDragging = false;
			return;
		}

		// Contain values
		if (x < 0) x = 0;
		if (y < 0) y = 0;

		if (x > width) x = width;
		if (y > height) y = height;

		double newMinX = map(mouseStartX, 0, width, minX, maxX);
		double newMaxX = map(x, 0, width, minX, maxX);

		// Min and max flipped since 0 on Im axis is at the bottom, and 0 in OpenGL was mapped to the top
		double newMinY = map(mouseStartY, 0, height, maxY, minY);
		double newMaxY = map(y, 0, height, maxY, minY);

		minX = std::min(newMinX, newMaxX);
		maxX = std::max(newMinX, newMaxX);

		minY = std::min(newMinY, newMaxY);
		maxY = std::max(newMinY, newMaxY);

		isDragging = false;

		printf("New Bounds:\n\tX: %lf : %lf\tY: %lf : %lf\n", minX, maxX, minY, maxY);
	}
}

// Called on scroll events
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	iters = iters + yOffset * 300;
	
	if (iters < 300) iters = 300;

	printf("Iterations: %i\n", iters);
}

// Apply shader and draw mandelbrot
void drawMandelbrot(int x, int y, int w, int h)
{
	program.use();
	program.setUniform("width", width);
	program.setUniform("height", height);
	program.setUniform("iters", iters);

	program.setUniform("xBounds", minX, maxX);
	program.setUniform("yBounds", minY, maxY);

	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(w, y);
		glVertex2f(w, h);
		glVertex2f(x, h);
	glEnd();

	program.clear();
}

// Called to update window drawing
void draw()
{
	glfwGetFramebufferSize(window, &width, &height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	glOrtho(0, width, height, 0, -1, 1);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	drawMandelbrot(0, 0, width, height);

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

// Create window and initialize GLFW
int main()
{
	printf("Running...\n\n");

	if (!glfwInit())
	{
		printf("\nFailed to initialize GLFW\n\n");
		return 1;
	}

	glfwSetErrorCallback(errorCallback);

	glfwWindowHint(GLFW_RESIZABLE, 0);
	window = glfwCreateWindow(1024, 768, "Mandelbrot", NULL, NULL);

	if (!window)
	{
		printf("\nFailed to create window\n\n");
		return 1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit())
	{
		printf("\nGlew init failed\n\n");
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