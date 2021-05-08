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
		Object(std::vector<float> vertices);
		~Object();

		void draw();
		void rotate(float radians, glm::vec3 axis);
		void translate(glm::vec3 trans);
		// getters
		unsigned int getVAO();
		unsigned int getVerticesCount();
		Shader* getShader();
		glm::mat4 getModel();
		std::vector<float> getVertices();
		// setter
		void setMVP(glm::mat4 view, glm::mat4 projection);
		void attachShader(Shader* shader);

	protected:
	private:
		struct Material
		{
			float color;
			float diffuse;
			float ambient;
			float specular;
		} m_Material;
		std::vector<float> m_vertices;
		unsigned int m_vertices_count;
		unsigned int m_VAO;
		Shader* m_shader;
		glm::mat4 m_model;
		glm::mat4 m_mvp;

};

#endif
