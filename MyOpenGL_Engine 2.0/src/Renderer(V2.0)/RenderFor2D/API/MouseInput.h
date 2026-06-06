#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

enum class MouseButton
{
	LEFT = 0,
	RIGHT = 1,
	MIDDLE = 2
};

class MouseInput
{
public:
	static void Init(GLFWwindow* window);
	static glm::vec2 GetMousePosition();
	static bool IsMouseButtonPress(MouseButton keycode);

private:
	static GLFWwindow* s_window;
};