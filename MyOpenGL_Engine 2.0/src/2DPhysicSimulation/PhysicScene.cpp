#include <GL/glew.h>
#include <Windows.h>
#include <iostream>
#include "PhysicScene.h"

#include "Hello_Box2D.h"
#include "Plunger.h"

PhysicRenderer::PhysicRenderer(GLFWwindow* window, unsigned int Project_Num)
	:m_window(window), m_Proj(Project_Num)
{
	system("color 03");
	switch (m_Proj)
	{
	case 0: m_Test = std::make_shared<HelloB2D>(m_window); m_Test->Create(); break;
	case 1: m_Test = std::make_shared<Plunger>(m_window);  m_Test->Create(); break;
	default:std::cout << "Unknow Porject number: " << m_Proj << std::endl; break;
	}
}

void PhysicRenderer::PhysicUpData(float timestep)
{
	m_Test->OnUpData(timestep);
}

void PhysicRenderer::ImguiUpData()
{
	m_Test->OnImGuiRender();
}

void PhysicRenderer::DeletePhysicScene()
{
	m_Test->Destroy();
}
