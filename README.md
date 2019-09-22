# opengl-mandelbrot
A very simple Mandelbrot renderer created in C++, using OpenGL and GLFW. This is by no means a fast or efficient way to do it, as it was only really meant for learning OpenGL and GLSL.

### Usage
First, the project requires the following dependencies:
- GLEW 2.1.0
- GLFW 3.2.1

The solution is configured to look for them in a `lib` folder in the project root. It also requires that `glew32.dll` is placed inside the the `OpenGL-Mandelbrot` folder in order to run/debug from inside Visual Studio.

If using Visual Studio 2017, the project solution should just be ready to open and then build for Win32 Debug/Release.

_Note: This has only been tested using Visual Studio 2017 on Windows 7/10_