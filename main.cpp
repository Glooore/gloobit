#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

#include "window.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
// matrix and vector types, a buncha useful stuff!
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer.h"
#include "object.h"
#include "shader.h"
#include "camera.h"

std::vector<float> generateCylinderVertices(float height, float radius, unsigned int N);
std::vector<float> generateConeVertices(float height, float radius, unsigned int N);
std::vector<float> generateSphereVertices(float radius, unsigned int N, unsigned int M); 

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
	std::vector<float> cylinder_vertices = generateCylinderVertices(6.0f, 1.0f, 10);
	std::vector<float> cone_vertices = generateConeVertices(6.0f, 2.0f, 10);
	std::vector<float> sphere_vertices = generateSphereVertices(3.0f, 10, 10);

	Window window(800, 600, "gloobit");
	window.init();
	GLFWwindow* window_context = window.getContext();

	Renderer renderer;

	glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), 
			(float) 800 / (float) 600, 0.1f, 100.0f);
	/* renderer.initRenderer(); */
	renderer.init(camera.getViewMatrix(), projection);

	glfwSetCursorPosCallback(window_context, mouse_callback);
	glfwSetInputMode(window_context, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader shader;
	shader.compileVertexShader("./shaders/shader.vert");
	shader.compileFragmentShader("./shaders/shader.frag");
	shader.bind();

	/* Object cube(vertices2); */
	/* unsigned int VAO = cube.getVAO(); */
	/* unsigned int n = cube.getVerticesLen(); */
	/* Shader* shader = cube.getShader(); */

	Object cylinder(cylinder_vertices);
	Object cone(cone_vertices);
	Object sphere(sphere_vertices);

	cylinder.translate(glm::vec3(0.0f, 0.0f, -25.0f));
	cone.translate(glm::vec3(0.0f, 0.0f, -15.0f));
	sphere.translate(glm::vec3(0.0f, 0.0f, -5.0f));

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	cylinder.attachShader(&shader);
	cone.attachShader(&shader);
	sphere.attachShader(&shader);

	/* cube.attachShader(&shader); */
	/* renderer.addObject(new Object(vertices, "./shaders/shader.vert", "./shaders/shader.frag")); */
	renderer.addObject(&cylinder);
	renderer.addObject(&cone);
	renderer.addObject(&sphere);

	while(!glfwWindowShouldClose(window_context))
	{

		current_frame = glfwGetTime();
		delta_time = current_frame - last_frame;
		last_frame = current_frame;

		process_input(window_context);

		renderer.updateView(camera.getViewMatrix());

		// setting a gery background
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		/* // clearing color buffer and z buffer */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* renderer.draw(VAO, n, mvp, shader); */
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


// height, radius < 1.0f
std::vector<float> generateCylinderVertices(float height, float radius, unsigned int N)
{
	std::vector<float> vertices;

	glm::vec3 top_middle = glm::vec3(0.0f, height/2.0f, 0.0f);
	glm::vec3 bottom_middle = glm::vec3(0.0f, -height/2.0f, 0.0f);

	// genereate top circle vertices;
	float angle_step = (2 * M_PI)/N;

	for (unsigned int i = 0; i < N; i++)
	{
		/* std::cout << "Generating vertices for triangle: " << i << std::endl; */
		// push middle point
		vertices.push_back(top_middle.x); //x
		vertices.push_back(top_middle.y); //y
		vertices.push_back(top_middle.z); //z

		// first circle point
		vertices.push_back(cos(i * angle_step) * radius);
		vertices.push_back(top_middle.y);
		vertices.push_back(sin(i * angle_step) * radius);

		// second circle point
		vertices.push_back(cos((i + 1) * angle_step) * radius);
		vertices.push_back(top_middle.y);
		vertices.push_back(sin((i + 1) * angle_step) * radius);
	}

	// generate bottom circle vertices;
	for (unsigned int i = 0; i < N; i++)
	{
		/* std::cout << "Generating vertices for triangle: " << i << std::endl; */
		// push middle point
		vertices.push_back(bottom_middle.x); //x
		vertices.push_back(bottom_middle.y); //y
		vertices.push_back(bottom_middle.z); //z

		// first circle point
		vertices.push_back(cos(i * angle_step) * radius);
		vertices.push_back(bottom_middle.y);
		vertices.push_back(sin(i * angle_step) * radius);

		// second circle point
		vertices.push_back(cos((i + 1) * angle_step) * radius);
		vertices.push_back(bottom_middle.y);
		vertices.push_back(sin((i + 1) * angle_step) * radius);
	}

	// generate side vertices;
	for (unsigned int i = 0; i < N; i++)
	{
		// first rectangle triangle
		vertices.push_back(cos(i * angle_step) * radius);
		vertices.push_back(top_middle.y);
		vertices.push_back(sin(i * angle_step) * radius);

		vertices.push_back(cos(i * angle_step) * radius);
		vertices.push_back(bottom_middle.y);
		vertices.push_back(sin(i * angle_step) * radius);

		vertices.push_back(cos((i + 1) * angle_step) * radius);
		vertices.push_back(top_middle.y);
		vertices.push_back(sin((i + 1) * angle_step) * radius);

		// second rectangle triangle
		vertices.push_back(cos((i + 1) * angle_step) * radius);
		vertices.push_back(bottom_middle.y);
		vertices.push_back(sin((i + 1) * angle_step) * radius);

		vertices.push_back(cos((i + 1) * angle_step) * radius);
		vertices.push_back(top_middle.y);
		vertices.push_back(sin((i + 1) * angle_step) * radius);

		vertices.push_back(cos(i * angle_step) * radius);
		vertices.push_back(bottom_middle.y);
		vertices.push_back(sin(i * angle_step) * radius);
	}

	return vertices;
}

std::vector<float> generateConeVertices(float height, float radius, unsigned int N)
{
	std::vector<float> vertices;

	glm::vec3 top_middle = glm::vec3(0.0f, height/2.0f, 0.0f);
	glm::vec3 bottom_middle = glm::vec3(0.0f, -height/2.0f, 0.0f);

	float angle_step = (2 * M_PI)/N;

	for (unsigned int i = 0; i < N; i++)
	{
		/* std::cout << "Generating vertices for triangle: " << i << std::endl; */
		// push middle point
		vertices.push_back(bottom_middle.x); //x
		vertices.push_back(bottom_middle.y); //y
		vertices.push_back(bottom_middle.z); //z

		// first circle point
		vertices.push_back(cos(i * angle_step) * radius);
		vertices.push_back(bottom_middle.y);
		vertices.push_back(sin(i * angle_step) * radius);

		// second circle point
		vertices.push_back(cos((i + 1) * angle_step) * radius);
		vertices.push_back(bottom_middle.y);
		vertices.push_back(sin((i + 1) * angle_step) * radius);
	}

	for (unsigned int i = 0; i < N; i++)
	{
		vertices.push_back(top_middle.x); //x
		vertices.push_back(top_middle.y); //y
		vertices.push_back(top_middle.z); //z

		// first circle point
		vertices.push_back(cos(i * angle_step) * radius);
		vertices.push_back(bottom_middle.y);
		vertices.push_back(sin(i * angle_step) * radius);

		// second circle point
		vertices.push_back(cos((i + 1) * angle_step) * radius);
		vertices.push_back(bottom_middle.y);
		vertices.push_back(sin((i + 1) * angle_step) * radius);
	}
	return vertices;
}

std::vector<float> generateSphereVertices(float radius, unsigned int N, unsigned int M)
{
	std::vector<float> vertices;

	glm::vec3 top_middle = glm::vec3(0.0f, radius, 0.0f);
	glm::vec3 bottom_middle = glm::vec3(0.0f, -radius, 0.0f);

	float v_step = M_PI  / (M + 2);
	float h_step = (2 * M_PI) / N;

	//generate top hat vertices
	for (unsigned int i = 0; i < N; i++)
	{
		vertices.push_back(top_middle.x);
		vertices.push_back(top_middle.y);
		vertices.push_back(top_middle.z);

		vertices.push_back(radius * cos(i * h_step) * cos(M_PI/2 - v_step));
		vertices.push_back(radius * sin(M_PI/2 - v_step));
		vertices.push_back(radius * sin(i * h_step) * cos(M_PI/2 - v_step));

		vertices.push_back(radius * cos((i + 1) * h_step) * cos(M_PI/2 - v_step));
		vertices.push_back(radius * sin(M_PI/2 - v_step));
		vertices.push_back(radius * sin((i + 1) * h_step) * cos(M_PI/2 - v_step));
	}

	//generate sides
	for (unsigned int i = 0; i < N; i++)
	{
		for (unsigned int j = 1; j <= M; j++)
		{
			// top triangle
			vertices.push_back(radius * cos(i * h_step) * cos(M_PI/2 - j * v_step));
			vertices.push_back(radius * sin(M_PI/2 - j * v_step));
			vertices.push_back(radius * sin(i * h_step) * cos(M_PI/2 - j * v_step));

			vertices.push_back(radius * cos(i * h_step) * cos(M_PI/2 - (j + 1) * v_step));
			vertices.push_back(radius * sin(M_PI/2 - (j + 1) * v_step));
			vertices.push_back(radius * sin(i * h_step) * cos(M_PI/2 - (j + 1) * v_step));

			vertices.push_back(radius * cos((i + 1) * h_step) * cos(M_PI/2 - j * v_step));
			vertices.push_back(radius * sin(M_PI/2 - j * v_step));
			vertices.push_back(radius * sin((i + 1) * h_step) * cos(M_PI/2 - j * v_step));

			// bottom triangle
			vertices.push_back(radius * cos((i + 1) * h_step) * cos(M_PI/2 - j * v_step));
			vertices.push_back(radius * sin(M_PI/2 - j * v_step));
			vertices.push_back(radius * sin((i + 1) * h_step) * cos(M_PI/2 - j * v_step));

			vertices.push_back(radius * cos(i * h_step) * cos(M_PI/2 - (j + 1) * v_step));
			vertices.push_back(radius * sin(M_PI/2 - (j + 1) * v_step));
			vertices.push_back(radius * sin(i * h_step) * cos(M_PI/2 - (j + 1) * v_step));

			vertices.push_back(radius * cos((i + 1) * h_step) * cos(M_PI/2 - (j + 1) * v_step));
			vertices.push_back(radius * sin(M_PI/2 - (j + 1) * v_step));
			vertices.push_back(radius * sin((i + 1) * h_step) * cos(M_PI/2 - (j + 1) * v_step));
		}
	}

	// generate bottom hat
	for (unsigned int i = 0; i < N; i++)
	{
		vertices.push_back(bottom_middle.x);
		vertices.push_back(bottom_middle.y);
		vertices.push_back(bottom_middle.z);

		vertices.push_back(radius * cos(i * h_step) * cos(-M_PI/2 + v_step));
		vertices.push_back(radius * sin(-M_PI/2 + v_step));
		vertices.push_back(radius * sin(i * h_step) * cos(-M_PI/2 + v_step));

		vertices.push_back(radius * cos((i + 1) * h_step) * cos(-M_PI/2 + v_step));
		vertices.push_back(radius * sin(-M_PI/2 + v_step));
		vertices.push_back(radius * sin((i + 1) * h_step) * cos(-M_PI/2 + v_step));
	}

	return vertices;
}
