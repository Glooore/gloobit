#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <iostream>
#include <vector>
#include <string>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"


namespace {

} // namespace

class Object 
{
	public:
		Object(std::vector<float> vertices)
			  : _model(1.0f)
		{
			_vertices = vertices;
			
			_len_vertices = _vertices.size();

			GLuint _VBO;

			glGenVertexArrays(1, &_VAO);
			glGenBuffers(1, &_VBO);

			glBindVertexArray(_VAO);

			glBindBuffer(GL_ARRAY_BUFFER, _VBO);
			glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float),
					_vertices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);
			glDeleteBuffers(1, &_VBO);
		};

		~Object()
		{
			glDeleteBuffers(1, &_VAO);
		};

		void draw()
		{
			glBindVertexArray(_VAO);
			_shader -> bind();

			glDrawArrays(GL_TRIANGLES, 0, _len_vertices);
			glBindVertexArray(0);
		}

		void rotate(float radians, glm::vec3 axis)
		{
			_model = glm::rotate(_model, radians, axis);
		}

		void translate(glm::vec3 trans)
		{
			_model = glm::translate(_model, trans);
		}

		// getters
		GLuint getVAO()
		{
			return _VAO;
		};

		GLuint getVerticesLen()
		{
			return _len_vertices;
		}

		Shader* getShader()
		{
			return _shader;
		}

		glm::mat4 getModel()
		{
			return _model;
		}

		std::vector<float> getVertices()
		{
			return _vertices;
		}

		// setter
		void setMVP(glm::mat4 view, glm::mat4 projection)
		{
			_mvp = projection * view * _model;
		}

		void attachShader(Shader* shader)
		{
			_shader = shader;
		}

	protected:
	private:
		struct Material
		{
			float color;
			float diffuse;
			float ambient;
			float specular;
		} _Material;
		std::vector<float> _vertices;
		GLuint _len_vertices;
		GLuint _VAO;
		Shader* _shader;
		glm::mat4 _model;
		glm::mat4 _mvp;

};

#endif
