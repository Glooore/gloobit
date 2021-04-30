#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

#include "window/window.hpp"

#include <GLFW/glfw3.h>
// matrix and vector types, a buncha useful stuff!
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer/renderer.hpp"
#include "object/object.hpp"
#include "shader/shader.h"
#include "camera/camera.h"

void process_input(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double x_position, double y_position);
// anonymous namespace so other files can't see it. Not really useful here.
namespace {
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float last_x = 400;
	float last_y = 300;
	bool first_mouse = true;

	float delta_time = 0.0f;
	float last_frame = 0.0f;
	float current_frame = 0.0f;
}

int main(int argc, char** argv)
{
	std::vector<float> vertices = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
	};

	std::vector<float> vertices2 = {
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f, 
     0.5f,  0.5f, -0.5f, 
     0.5f,  0.5f, -0.5f, 
    -0.5f,  0.5f, -0.5f, 
    -0.5f, -0.5f, -0.5f, 

    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,

    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,

     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,

    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
	};// cube vertices

	Window window(800, 600, "gloobit");
	window.init();

	Renderer renderer;

	glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), 
			(float) 800 / (float) 600, 0.1f, 100.0f);
	/* renderer.initRenderer(); */
	renderer.init(camera.getViewMatrix(), projection);

	GLFWwindow* window_context = window.getContext();

	glfwSetCursorPosCallback(window_context, mouse_callback);
	glfwSetInputMode(window_context, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Object cube(vertices2, "./shaders/shader.vert", "./shaders/shader.frag");
	renderer.addObject(new Object(vertices, "./shaders/shader.vert", "./shaders/shader.frag"));
	renderer.addObject(&cube);




	while(!glfwWindowShouldClose(window_context))
	{
		renderer.updateView(camera.getViewMatrix());

		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		process_input(window_context);

		// setting a gery background
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		/* // clearing color buffer and z buffer */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer.drawObjects();

		glfwSwapBuffers(window_context);
		glfwPollEvents();
	}

	return 0;
}

void process_input(GLFWwindow* window)
{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{ 
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.processKeyboard(FORWARD, delta_time);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.processKeyboard(BACKWARD, delta_time);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.processKeyboard(RIGHT, delta_time);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.processKeyboard(LEFT, delta_time);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.processKeyboard(UP, delta_time);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		camera.processKeyboard(DOWN, delta_time);
	}
}

void mouse_callback(GLFWwindow* window, double x_position, double y_position)
{
	if (first_mouse)
	{
		last_x = x_position;
		last_y = y_position;
		first_mouse = false;
	}

	float x_offset = x_position - last_x;
	float y_offset = y_position - last_y;

	last_x = x_position;
	last_y = y_position;

	camera.processMouseMovement(x_offset, y_offset);
}
