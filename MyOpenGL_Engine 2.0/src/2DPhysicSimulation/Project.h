#pragma once
#include <GLFW/glfw3.h>
class Project
{
public:
	virtual void Create() = 0;
	virtual void OnUpData(float timestep) = 0;
	virtual void OnImGuiRender() = 0;
	virtual void Destroy() = 0;
private:
	GLFWwindow* m_WindowHandle;
};