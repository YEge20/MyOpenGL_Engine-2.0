#pragma once
#include <memory>
#include <GLFW/glfw3.h>
#include "Project.h"

class PhysicRenderer
{
public:
	PhysicRenderer() = default;
	PhysicRenderer(GLFWwindow* window, unsigned int Project_Num);
	void PhysicUpData(float timestep);
	void ImguiUpData();
	void DeletePhysicScene();
private:
	unsigned int m_Proj;
	GLFWwindow* m_window = nullptr;
	std::shared_ptr<Project> m_Test = nullptr;
};