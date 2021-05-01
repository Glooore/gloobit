#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
	public:
		Shader();
		~Shader();

		void compileVertexShader(const char* vertex_path);
		void compileFragmentShader(const char* fragment_path);
		void compileGeometryShader(const char* geometry_path);

		void bind() const;
		void unbind() const;

		void setBool(const std::string &name, const bool &value) const;
		void setInt(const std::string &name, const int &value) const;
		void setFloat(const std::string &name, const float &value) const;
		void setVec2(const std::string &name, const glm::vec2 &vec) const;
		void setVec3(const std::string &name, const glm::vec3 &vec) const;
		void setVec4(const std::string &name, const glm::vec4 &vec) const;
		void setMat2(const std::string &name, const glm::mat2 &mat) const;
		void setMat3(const std::string &name, const glm::mat3 &mat) const;
		void setMat4(const std::string &name, const glm::mat4 &mat) const;
	private:
		unsigned int m_program_id;
		/* std::string m_vertex_path, m_fragment_path, m_geometry_path; */
		// does this even need it?
		/* std::string m_vertex_shader, m_fragment_shader, m_geometry_shader; */
};

#endif
