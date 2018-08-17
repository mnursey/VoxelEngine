#include "InputManager.h"
#include <iostream>

int MOUSE_X = 0;
int MOUSE_Y = 0;

static void MousePosCallback(GLFWwindow* window, double posX, double posY)
{
	MOUSE_X = posX;
	MOUSE_Y = posY;
}

InputManager::InputManager(GLFWwindow* window)
	:m_pWindow(window)
{
	glfwSetInputMode((GLFWwindow *)window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetCursorPosCallback((GLFWwindow *)window, MousePosCallback);
}

InputManager::~InputManager()
{

}

void InputManager::HandleInput()
{
	keyboardInput[0] = glfwGetKey(m_pWindow, GLFW_KEY_W);
	keyboardInput[1] = glfwGetKey(m_pWindow, GLFW_KEY_S);
	keyboardInput[2] = glfwGetKey(m_pWindow, GLFW_KEY_A);
	keyboardInput[3] = glfwGetKey(m_pWindow, GLFW_KEY_D);
	keyboardInput[4] = glfwGetKey(m_pWindow, GLFW_KEY_SPACE);
	keyboardInput[5] = glfwGetKey(m_pWindow, GLFW_KEY_LEFT_CONTROL);
	keyboardInput[6] = glfwGetKey(m_pWindow, GLFW_KEY_LEFT_SHIFT);
}

void InputManager::GetKeyInput(bool*& keyInput)
{
	keyInput = keyboardInput;
}
