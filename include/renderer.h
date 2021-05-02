#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <vector>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object.hpp"

class Renderer
{
	public:
		Renderer();
		~Renderer();

		void init(glm::mat4 view, glm::mat4 proj);

		void addObject(Object* object);

		void drawObjects();
		void updateView(glm::mat4 view);
	protected:
	private:
		/* std::vector<std::unique_ptr<Object>> _objects; */
		glm::mat4 m_view, m_proj;
		std::vector<Object*> m_objects;
};

#endif
