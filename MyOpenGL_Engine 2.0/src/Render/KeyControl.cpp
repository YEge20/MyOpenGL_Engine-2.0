#include"KeyControl.h"
#define translation_move 40.0f
KeyControlFunction::KeyControlFunction(GLFWwindow* window)
	:Window(window)
{
}

void KeyControlFunction::KeyUp_Down_Left_Right(float* f1, float* f2, float speed)
{

	if (glfwGetKey(Window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		*f1 = speed;
	}
	if (glfwGetKey(Window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		*f1 = -speed;
	}
	if (glfwGetKey(Window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		*f2 = -speed;
	}
	if (glfwGetKey(Window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		*f2 = speed;
	}
	if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(Window, true);
}
