#include "shader.h"

#include "glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Shader::Shader(char* vertex_path, const char* fragment_path, const char* geometry_path) */
Shader::Shader()
{
	m_program_id = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(m_program_id);
}

void Shader::compileVertexShader(const char* vertex_path)
{
	std::string vertex_code;
	std::ifstream vertex_file;

	vertex_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vertex_file.open(vertex_path);
		std::stringstream vertex_stream;

		vertex_stream << vertex_file.rdbuf();
		vertex_file.close();
		vertex_code = vertex_stream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Vertex shader file has not been successfuly read" << std::endl;
	}

	const char* vertex_source = vertex_code.c_str();

	unsigned int vertex_shader;
	int success;
	char info_log[512];

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_source, NULL);
	glCompileShader(vertex_shader);

	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		std::cout << "Vertex shader compilation failed.\n" << info_log << std::endl;
	}

	glAttachShader(m_program_id, vertex_shader);
	glLinkProgram(m_program_id);
	glDeleteShader(vertex_shader);
}

void Shader::compileFragmentShader(const char* fragment_path)
{
	std::string fragment_code;
	std::ifstream fragment_file;

	fragment_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		fragment_file.open(fragment_path);
		std::stringstream fragment_stream;

		fragment_stream << fragment_file.rdbuf();
		fragment_file.close();
		fragment_code = fragment_stream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Fragment shader file has not been successfuly read" << std::endl;
	}

	const char* fragment_source = fragment_code.c_str();

	unsigned int fragment_shader;
	int success;
	char info_log[512];

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_source, NULL);
	glCompileShader(fragment_shader);

	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		std::cout << "Fragment shader compilation failed.\n" << info_log << std::endl;
	}

	glAttachShader(m_program_id, fragment_shader);
	glLinkProgram(m_program_id);
	glDeleteShader(fragment_shader);
}

void Shader::compileGeometryShader(const char* geometry_path)
{
	std::string geometry_code;
	std::ifstream geometry_file;

	geometry_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		geometry_file.open(geometry_path);
		std::stringstream geometry_stream;

		geometry_stream << geometry_file.rdbuf();
		geometry_file.close();
		geometry_code = geometry_stream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Geometry shader file has not been successfuly read" << std::endl;
	}

	const char* geometry_source = geometry_code.c_str();

	unsigned int geometry_shader;
	int success;
	char info_log[512];

	geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(geometry_shader, 1, &geometry_source, NULL);
	glCompileShader(geometry_shader);

	glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(geometry_shader, 512, NULL, info_log);
		std::cout << "Geometry shader compilation failed.\n" << info_log << std::endl;
	}

	glAttachShader(m_program_id, geometry_shader);
	glLinkProgram(m_program_id);
	glDeleteShader(geometry_shader);
}

void Shader::bind() const
{
	glUseProgram(m_program_id);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setBool(const std::string &name, const bool &value) const
{
	glUniform1i(glGetUniformLocation(m_program_id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, const int &value) const
{
	glUniform1i(glGetUniformLocation(m_program_id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, const float &value) const
{
	glUniform1f(glGetUniformLocation(m_program_id, name.c_str()), value);
}

void Shader::setVec2(const std::string &name, const glm::vec2 &vec) const
{
	glUniform2fv(glGetUniformLocation(m_program_id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setVec3(const std::string &name, const glm::vec3 &vec) const
{
	glUniform3fv(glGetUniformLocation(m_program_id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setVec4(const std::string &name, const glm::vec4 &vec) const
{
	glUniform4fv(glGetUniformLocation(m_program_id, name.c_str()), 1, glm::value_ptr(vec));
}

void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(m_program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_program_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
