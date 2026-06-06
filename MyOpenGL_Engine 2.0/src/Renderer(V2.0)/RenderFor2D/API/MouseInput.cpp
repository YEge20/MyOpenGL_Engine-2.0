#include "MouseInput.h"
#include <iostream>

GLFWwindow* MouseInput::s_window = nullptr;

void MouseInput::Init(GLFWwindow* window)
{
	s_window = window;
}

glm::vec2 MouseInput::GetMousePosition()
{
	double X, Y;
	if (s_window)
	{
		glfwGetCursorPos(s_window, &X, &Y);
		glm::vec2 Position = { (float)X,(float)Y };
		return Position;
	}
	else
	{
		std::cout << "Do not init MouseInput class! Please call Init() first..." << std::endl;
		return glm::vec2(0.0f);
	}
}

bool MouseInput::IsMouseButtonPress(MouseButton keycode)
{
	if (s_window)
	{
		auto status = glfwGetMouseButton(s_window, (int)keycode);
		return status == GLFW_PRESS;
	}
	else
	{
		std::cout << "Do not init MouseInput class! Please call Init() first..." << std::endl;
		return false;
	}
}
