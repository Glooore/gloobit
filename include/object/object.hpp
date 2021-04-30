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

#include "shader/shader.h"


namespace {

} // namespace

class Object 
{
	public:
		Object(std::vector<float> vertices, std::string vertex, std::string fragment)
			: _shader(vertex.c_str(), fragment.c_str()),
			  _model(1.0f)
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

		};

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
			return &_shader;
		}

		glm::mat4 getModel()
		{
			return _model;
		}

		std::vector<float> getVertices()
		{
			return _vertices;
		}

		void setMVP(glm::mat4 view, glm::mat4 projection)
		{
			_mvp = projection * view * _model;
		}

	protected:
	private:
		std::vector<float> _vertices;
		GLuint _len_vertices;
		GLuint _VAO;
		Shader _shader;
		glm::mat4 _model;
		glm::mat4 _mvp;

};

#endif
