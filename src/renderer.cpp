#include <iostream>
// for rand() that I haven't used.
/* #include <stdlib.h> */
#include <cmath>

#include "renderer/renderer.hpp"
#include <GLFW/glfw3.h>
// matrix and vector types, a buncha useful stuff!
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// anonymous namespace so other files can't see it. Not really useful here.
namespace {
	const int window_width = 800;
	const int window_height = 600;
}

int main(int argc, char** argv)
{
	Renderer renderer(window_width, window_height, "triangle");
	renderer.initRenderer();
	GLFWwindow* window = renderer.getContext();
	/* GLFWwindow* window = glfwCreateWindow(800, 600, "triangle", NULL, NULL); */

	// cube vertices
	/* float vertices[] = { */
    /* -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, */
     /* 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, */ 
     /* 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, */ 
	/* };// cube vertices */

	// render loop
	/* while(!renderer.shouldClose()) */
	while(!glfwWindowShouldClose(window))
	{
		// setting a gery background
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		// clearing color buffer and z buffer
		glClear(GL_COLOR_BUFFER_BIT);

		// setting up a basic identity matrix
		/* glDrawArrays(GL_TRIANGLES, 0, 3); */

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

