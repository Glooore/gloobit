#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace {

} // namespace

class Object 
{
	public:
		Object(float* vertices)
		{
			_vertices = vertices;

			/* glGenVertexArrays(1, &_VAO); */
			/* glGenBuffers(1, &_VBO); */

			/* glBindVertexArray(_VAO); */

			/* glBindBuffer(GL_ARRAY_BUFFER, _VBO); */
			/* glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW); */

			/* glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0); */
			/* glEnableVertexAttribArray(0); */

			/* glBindVertexArray(0); */
		};

		unsigned int getVAO()
		{
			return _VAO;
		};

		unsigned int getVBO()
		{
			return _VBO;
		};

		float* getVertices()
		{
			return _vertices;
		}

		void setVAO(unsigned int VAO)
		{
			_VAO = VAO;
		}

		void setVBO(unsigned int VBO)
		{
			_VBO = VBO;
		}
	protected:
	private:
		float* _vertices;
		unsigned int _VAO, _VBO;
		//Shader shader;

};

#endif
