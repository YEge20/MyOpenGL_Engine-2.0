#pragma once
#include<GL/glew.h>
#include <GLFW/glfw3.h>
class KeyControlFunction
{
public:
	KeyControlFunction(GLFWwindow* window);

	void KeyUp_Down_Left_Right(float* f1, float* f2, float speed);

private:
	GLFWwindow* Window;
};
