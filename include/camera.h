#ifndef _CAMERA_H_
#define _CAMERA_H_

/* #include <GLFW/glfw.h> */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum camera_movement {FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN};

namespace {
	float YAW = -90.0f;
	float PITCH = 0.0f;

	float SPEED = 5.0f;
	float SENSITIVITY = 0.1f;
	float FOV = 45.0f;
} // namespace

class Camera
{
	public:
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

		void processKeyboard(camera_movement direction, float delta_time);
		void processMouseMovement(float x_offset, float y_offset, bool constrain_pitch = true);

		glm::mat4 getViewMatrix(void) const;
		float getFOV(void) const;
		glm::vec3 getPosition(void) const;

	private:
		glm::vec3 m_camera_pos, m_camera_up, m_camera_front, m_camera_right;
		glm::vec3 m_world_up;
		float m_fov;
		float m_yaw, m_pitch;
		float m_speed;
		float m_mouse_sensitivity;
		/* float m_last_x, m_last_y; */

		void updateCameraVectors();
};




#endif
