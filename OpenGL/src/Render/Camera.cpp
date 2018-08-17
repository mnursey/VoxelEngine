#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetViewMatrix()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front = glm::normalize(front);

	m_Right = glm::normalize(glm::cross(m_Front, m__WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));

	glm::mat4 view;
	view = glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
	return view;
}

void Camera::ProcessKeyboard(Direction direction, float deltaTime)
{
	float velocity = m_MovementSpeed * deltaTime;
	switch (direction)
	{
	case FORWARD:
		m_Pos += m_Front * velocity;
		break;
	case BACKWARD:
		m_Pos += -m_Front * velocity;
		break;
	case LEFT:
		m_Pos += -m_Right * velocity;
		break;
	case RIGHT:
		m_Pos += m_Right * velocity;
		break;
	case UP:
		m_Pos += m_Up * velocity;
		break;
	case DOWN:
		m_Pos += -m_Up * velocity;
	default:
		break;
	}
}

void Camera::MouseInput(double xpos, double ypos)
{
	if (m_firstMouse)
	{
		m_lastX = xpos;
		m_lastY = ypos;
		m_firstMouse = false;
	}

	float xoffset = xpos - m_lastX;
	float yoffset = m_lastY - ypos;
	m_lastX = xpos;
	m_lastY = ypos;

	xoffset *= m_MouseSensitivity;
	yoffset *= m_MouseSensitivity;

	m_Yaw += xoffset;
	m_Pitch += yoffset;

	if (m_Pitch > 89.0f)
		m_Pitch = 89.0f;
	if (m_Pitch < -89.0f)
		m_Pitch = -89.0f;
}

glm::vec3 Camera::GetPosition()
{
	return m_Pos;
}
