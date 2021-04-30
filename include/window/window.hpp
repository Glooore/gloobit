#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>


void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
};

class Window
{
	public:
		Window(int width, int height, std::string name)
		{
			_window_width = width;
			_window_height = height;
			_window_name = name;
			_window = NULL;
		};
		
		int init()
		{
			if (!glfwInit())
			{
				std::cout << "GLFW initialization failed" << std::endl;
				return -1;
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			_window = glfwCreateWindow(_window_width, _window_height, _window_name.c_str(),
					NULL, NULL);

			if (_window == NULL)
			{
				std::cout << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
				return -1;
			}

			glfwMakeContextCurrent(_window);
			glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);

			if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
			{
				std::cout << "Failed to initialize GLAD" << std::endl;
				return -1;
			}

			glViewport(0, 0, _window_width, _window_height);
			return 0;
		};

		void resize(int width, int height)
		{
			glViewport(0, 0, width, height);
		};

		GLFWwindow* getContext()
		{
			return glfwGetCurrentContext();
		};
	protected:
	private:
		unsigned int _window_width, _window_height;
		std::string _window_name;
		GLFWwindow* _window;
};



#endif
