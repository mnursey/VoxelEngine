#pragma once
#include "GLFW/glfw3.h"

static void MousePosCallback(GLFWwindow* window, double posX, double posY);
extern int MOUSE_X;
extern int MOUSE_Y;

class InputManager {
	static const int KEYINPUTS = 12;

	/*
	w - 0
	s - 1
	a - 2
	d - 3
	space - 4
	ctr - 5
	shift - 6
	*/
	bool keyboardInput[KEYINPUTS];
	GLFWwindow* m_pWindow;
public:
	InputManager(GLFWwindow* window);
	~InputManager();

	void HandleInput();
	void GetKeyInput(bool*& inputs);
};