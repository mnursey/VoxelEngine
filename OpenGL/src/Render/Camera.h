#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <stdio.h>
#include <math.h>

enum Direction {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera {
private:

	glm::vec3 m_Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 m__WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float m_Yaw;
	float m_Pitch;

	float m_MovementSpeed = 10.0f;
	float m_MouseSensitivity = 0.2f;
	float m_Zoom = 1.0f;

	bool m_firstMouse = false;
	float m_lastX;
	float m_lastY;

public:
	Camera();
	~Camera();

	glm::mat4 GetViewMatrix();

	void ProcessKeyboard(Direction direction,float deltaTime);

	void MouseInput(double xpos, double ypos);

	glm::vec3 GetPosition();
};