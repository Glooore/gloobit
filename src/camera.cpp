#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
	m_camera_pos = position;
	m_world_up = up;
	m_camera_front = glm::vec3(0.0f, 0.0f, -1.0f);
	m_yaw = yaw;
	m_pitch = pitch;
	m_fov = FOV;
	m_speed = SPEED;
	m_mouse_sensitivity = SENSITIVITY;

	updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix(void) const
{
	return glm::lookAt(m_camera_pos,  m_camera_pos + m_camera_front, m_camera_up);
}

float Camera::getFOV(void) const
{
	return m_fov;
}

glm::vec3 Camera::getPosition(void) const
{
	return m_camera_pos;
}

void Camera::processKeyboard(camera_movement direction, float delta_time)
{
	float m_velocity = m_speed * delta_time;
	if (direction == FORWARD) m_camera_pos += m_camera_front * m_velocity;
	if (direction == BACKWARD) m_camera_pos -= m_camera_front * m_velocity;
	if (direction == LEFT) m_camera_pos -= m_camera_right * m_velocity;
	if (direction == RIGHT) m_camera_pos += m_camera_right * m_velocity;
	if (direction == UP) m_camera_pos += m_world_up * m_velocity;
	if (direction == DOWN) m_camera_pos -= m_world_up * m_velocity;
}

void Camera::processMouseMovement(float x_offset, float y_offset, bool constrain_pitch)
{
	x_offset *= m_mouse_sensitivity;
	y_offset *= m_mouse_sensitivity;

	m_yaw += x_offset;
	m_pitch -= y_offset;

	if (constrain_pitch)
	{
		if (m_pitch > 89.0f) m_pitch = 89.0f;
		if (m_pitch < -89.0f) m_pitch = -89.0f;
	}
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	m_camera_front = glm::normalize(front);
	m_camera_right = glm::normalize(glm::cross(m_camera_front, m_world_up));
	m_camera_up = glm::normalize(glm::cross(m_camera_right, m_camera_front));
}
