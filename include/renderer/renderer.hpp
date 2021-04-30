#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream>
#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object/object.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
};

class Renderer
{
	public:
		Renderer(int width, int height, std::string name)
		{
			_window_width = width;
			_window_height = height;
			_window_name = name;
		};

		~Renderer()
		{
			glfwTerminate();
		};

		int initRenderer()
		{
			if (!glfwInit())
			{
				std::cout << "GLFW initialization failed" << std::endl;
				return -1;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			//create window
			GLFWwindow* _window = glfwCreateWindow(_window_width, _window_height, _window_name.c_str(), 
					NULL, NULL);
			if (_window == NULL)
			{
				std::cout << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
				return -1;
			}

			glfwMakeContextCurrent(_window);

			if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return -1;
			}

			glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);
			glViewport(0, 0, _window_width, _window_height);

			return 0;
		};

		GLFWwindow* getContext()
		{
			return glfwGetCurrentContext();
		};

		int getWindowWidth()
		{
			return _window_width;
		};
		int getWindowHeight()
		{
			return _window_height;
		};

		/* void addObject(Object* object) */
		/* { */
		/* 	_object = object; */
		/* }; */

		/* void initObject() */
		/* { */
		/* 	unsigned int VAO = _object -> getVAO(); */
		/* 	unsigned int VBO = _object -> getVBO(); */
		/* 	float* vertices = _object -> getVertices(); */

		/* 	glGenVertexArrays(1, &VAO); */
		/* 	glGenBuffers(1, &VBO); */

		/* 	glBindVertexArray(VAO); */

		/* 	glBindBuffer(GL_ARRAY_BUFFER, VBO); */
		/* 	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); */

		/* 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0); */
		/* 	glEnableVertexAttribArray(0); */

		/* 	glBindVertexArray(0); */

		/* 	_object -> setVAO(VAO); */
		/* 	_object -> setVBO(VBO); */
		/* } */

		/* void drawObject() */
		/* { */
		/* 	unsigned int VAO = _object -> getVAO(); */

		/* 	glBindVertexArray(VAO); */
		/* 	glDrawArrays(GL_TRIANGLES, 0, 3); */
		/* 	glBindVertexArray(0); */
		/* } */
	protected:
		GLFWwindow* _window;
		std::string _window_name;
		int _window_width, _window_height;
	private:
};

#endif
