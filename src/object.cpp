#include "object.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Object::Object(std::vector<float> vertices) : m_model(1.0f)
{
	m_vertices = vertices;
	m_vertices_count = m_vertices.size();

	unsigned int VBO;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float),
			m_vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glDeleteBuffers(1, &VBO);
};

Object::~Object()
{
	glDeleteBuffers(1, &m_VAO);
};

void Object::draw()
{
	glBindVertexArray(m_VAO);
	m_shader -> bind();

	glDrawArrays(GL_TRIANGLES, 0, m_vertices_count);
	glBindVertexArray(0);
};

void Object::rotate(float radians, glm::vec3 axis)
{
	m_model = glm::rotate(m_model, radians, axis);
};

void Object::translate(glm::vec3 trans)
{
	m_model = glm::translate(m_model, trans);
};

// getters
unsigned int Object::getVAO()
{
	return m_VAO;
};

unsigned int Object::getVerticesCount()
{
	return m_vertices_count;
};

Shader* Object::getShader()
{
	return m_shader;
};

glm::mat4 Object::getModel()
{
	return m_model;
};

std::vector<float> Object::getVertices()
{
	return m_vertices;
};

// setter
void Object::setMVP(glm::mat4 view, glm::mat4 projection)
{
	m_mvp = projection * view * m_model;
};

void Object::attachShader(Shader* shader)
{
	m_shader = shader;
};
