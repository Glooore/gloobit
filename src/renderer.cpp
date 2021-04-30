#include <iostream>
// for rand() that I haven't used.
/* #include <stdlib.h> */
#include <cmath>

#include "renderer/renderer.hpp"
#include "object/object.hpp"
#include "shader/shader.h"

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
	float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
	};

	/* Object triangle(vertices); */
	Renderer renderer(window_width, window_height, "triangle");
	renderer.initRenderer();
	GLFWwindow* window = renderer.getContext();

	Shader shader("./shaders/shader.vert", "./shaders/shader.frag");
	shader.use();

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	while(!glfwWindowShouldClose(window))
	{
		// setting a gery background
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		// clearing color buffer and z buffer
		glClear(GL_COLOR_BUFFER_BIT);

		/* triangle.draw(); */
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

