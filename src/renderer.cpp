#include "renderer.h"
#include "object.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer() : m_view(1.0f), m_proj(1.0f)
{
	glEnable(GL_DEPTH_TEST);
};

Renderer::~Renderer()
{
	/* glfwTerminate(); */
};

void Renderer::init(glm::mat4 view, glm::mat4 proj)
{
	m_view = view;
	m_proj = proj;
};

void Renderer::addObject(Object* object)
{
	m_objects.push_back(object);
};

void Renderer::drawObjects()
{
	for (auto obj : m_objects)
	{
		GLuint VAO = obj -> getVAO();
		GLuint n = obj -> getVerticesLen();
		glm::mat4 model = obj -> getModel();

		glm::mat4 mvp = m_proj * m_view * model;

		Shader* shader = obj -> getShader();
		shader -> setMat4("mvp", mvp);
		shader -> bind();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, n);
		glBindVertexArray(0);
	}
};

void Renderer::updateView(glm::mat4 view)
{
	m_view = view;
}
