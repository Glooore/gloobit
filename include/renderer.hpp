#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object.hpp"

class Renderer
{
	public:
		Renderer() : _view(1.0f), _proj(1.0f)
		{
			glEnable(GL_DEPTH_TEST);
		};

		~Renderer()
		{
			glfwTerminate();
		};

		void init(glm::mat4 view, glm::mat4 proj)
		{
			_view = view;
			_proj = proj;
		};

		void addObject(Object* object)
		{
			_objects.push_back(object);
		};

		void drawObjects()
		{
			for (auto obj : _objects)
			{
				GLuint VAO = obj -> getVAO();
				GLuint n = obj -> getVerticesLen();
				glm::mat4 model = obj -> getModel();

				glm::mat4 mvp = _proj * _view * model;

				Shader* shader = obj -> getShader();
				shader -> setMat4("mvp", mvp);
				shader -> bind();

				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, n);
				glBindVertexArray(0);
			}
		};

		void updateView(glm::mat4 view)
		{
			_view = view;
		}

	protected:
	private:
		/* std::vector<std::unique_ptr<Object>> _objects; */
		glm::mat4 _view, _proj;
		std::vector<Object*> _objects;
};

#endif
