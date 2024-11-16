#include"Render/RenderControler.h"
#include<Windows.h>

RenderControler::RenderControler(GLFWwindow* window, usemode mode, int auto_ProjectNum)
	:m_window(window),m_singleObject(0)
{
	if (mode == AUTO)
		AutoRenderControl(auto_ProjectNum);
	else if (mode == MYSELF)
		MyselfRenderControl();
}

int RenderControler::renderContextControl(float timestep, float milltimestep)
{
	//注册渲染对象的渲染内容(必须)：
	if (m_singleObject == 0)
		m_Triangle->renderContext(timestep, milltimestep);
	else if (m_singleObject == 1)
		m_Render3D_Camera->renderContext(timestep, milltimestep);
	else if (m_singleObject == 2)
		m_RenderTexture2D->renderContext(timestep, milltimestep);
	else if (m_singleObject == 3)
		m_light->renderContext(timestep, milltimestep);
	else if (m_singleObject == 4)
		m_grass->renderContext(timestep, milltimestep);
	else if (m_singleObject == 5)
		m_ShadowMap->renderContext(timestep, milltimestep);
	else if (m_singleObject == 6)
		m_ShadowMap2->renderContext(timestep, milltimestep);
	else if (m_singleObject == 7)
		m_stencil_test->renderContext(timestep, milltimestep);
	else if (m_singleObject == 8)
		m_DynamicTextureBuffer_test->renderContext(timestep, milltimestep);
	else
		return -1;
}

void RenderControler::renderImguiContextControl()
{
	//注册渲染对象的Imgui渲染内容(可注册也可以不注册)：
	if (m_singleObject == 0)
		m_Triangle->renderImguiContext();
	else if (m_singleObject == 1)
		m_Render3D_Camera->renderImguiContext();
	else if (m_singleObject == 2)
		m_RenderTexture2D->renderImguiContext();
	else if (m_singleObject == 3)
		m_light->renderImguiContext();
	else if (m_singleObject == 4)
		m_grass->renderImguiContext();
	else if (m_singleObject == 5)
		m_ShadowMap->renderImguiContext();
	else if (m_singleObject == 6)
		m_ShadowMap2->renderImguiContext();
	else if (m_singleObject == 7)
		m_stencil_test->renderImguiContext();
	else if (m_singleObject == 8)
		m_DynamicTextureBuffer_test->renderImguiContext();

}

int RenderControler::AutoRenderControl(int projectnum)
{
	m_singleObject = projectnum;
	system("color 02");
	//注册渲染对象的初始化信息(必须)：
	if (m_singleObject == 0)
		m_Triangle = std::make_unique<Triangle>(m_window);
	else if (m_singleObject == 1)
		m_Render3D_Camera = std::make_unique<Render3D_Camera>(m_window);
	else if (m_singleObject == 2)
		m_RenderTexture2D = std::make_unique<RenderTexture2D>(m_window);
	else if (m_singleObject == 3)
		m_light = std::make_unique<light>(m_window);
	else if (m_singleObject == 4)
		m_grass = std::make_unique<GrassGround>(m_window);
	else if (m_singleObject == 5)
		m_ShadowMap = std::make_unique<ShadowMap>(m_window);
	else if (m_singleObject == 6)
		m_ShadowMap2 = std::make_unique<ShadowMap2>(m_window);
	else if (m_singleObject == 7)
		m_stencil_test = std::make_unique<stencil_test>(m_window);
	else if (m_singleObject == 8)
		m_DynamicTextureBuffer_test = std::make_unique<DynamicTextureBuffer>(m_window);
	else
	{
		system("color 04");
		std::cout << "<RenderControl error>:没有注册此渲染对象的相关信息，请检查Rendercontroler.cpp(或.h)文件" << std::endl;
	}
	return 0;
}

int RenderControler::MyselfRenderControl()
{
	//终端提示信息：
	std::cout << "ProjectNum:        Render.cpp:\n";
	std::cout << "#0                 Triangle.cpp(The easiest example)\n";
	std::cout << "#1                 Render3D_Camera.cpp\n";
	std::cout << "#2                 RenderTexture2D.cpp\n";
	std::cout << "#3                 light.cpp\n";
	std::cout << "#4                 Grassground.cpp\n";
	std::cout << "#5                 ShadowMap.cpp\n";
	std::cout << "#6                 ShadowMap2.cpp\n";
	std::cout << "#7                 stencil_test.cpp\n";
	std::cout << "#8                 DynamicTextureBuffer.cpp\n";
	std::cout << "please input a ProjectNum you want:";
	int x;
	scanf_s("%d", &x);
	AutoRenderControl(x);
	return 0;
}
