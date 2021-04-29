#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream>
#include <string>


#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

			glViewport(0, 0, _window_width, _window_height);

			return 0;
		};

		GLFWwindow* getContext()
		{
			return glfwGetCurrentContext();
		};

		/* void getWindowWidth(); */
		/* void getWindowHeight(); */
		int _window_width, _window_height;
	protected:
		GLFWwindow* _window;
		std::string _window_name;
	private:
		/* void framebufferSizeCallback(GLFWwindow* window, int width, int height) */
		/* { */
		/* 	glViewport(0, 0, width, height); */
		/* }; */
};

#endif
