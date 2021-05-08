#include "renderer.h"
#include "object.h"

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

void Renderer::draw(unsigned int VAO, unsigned int vertices_count, glm::mat4 mvp, Shader shader)
{
	shader.setMat4("mvp", mvp);
	shader.bind();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, vertices_count);
	glBindVertexArray(0);
};

void Renderer::drawObjects()
{
	for (auto obj : m_objects)
	{
		unsigned int VAO = obj -> getVAO();
		unsigned int n = obj -> getVerticesCount();
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
