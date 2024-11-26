#pragma once
//导入要注册的渲染内容的头文件：
#include"Render3D_Camera.h"
#include"RenderTexture2D.h"
#include"light.h"
#include"Grassground.h"
#include"ShadowMap.h"
#include"ShadowMap2.h"
#include"stencil_test.h"
#include"Triangle.h"
#include"DynamicTextureBuffer.h"
#include"PointLight_ShadowCubemap.h"

#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
enum usemode
{
	AUTO = 0,MYSELF
};

class RenderControler
{
public:
	//mode的参数为'AUTO',和'MYSELF'(分别为自动初始化与手动初始化)
	//如果是'AUTO',请准确填已注册的ProjectNum参数到auto_ProjectNum,主要用在Debug配置下用
	//如果是'MYSELF',会在终端提醒输入,此处的auto_ProjectNum参数随意,主要用在Release配置下用
	RenderControler(GLFWwindow* window,usemode mode, int auto_ProjectNum);
	int renderContextControl(float timestep, float milltimestep);
	void renderImguiContextControl();

private:
	int m_singleObject;
	GLFWwindow* m_window;
	int AutoRenderControl(int projectnum);
	int MyselfRenderControl();
	//注册的渲染器信息实例：
	std::unique_ptr<Render3D_Camera> m_Render3D_Camera;
	std::unique_ptr<RenderTexture2D> m_RenderTexture2D;
	std::unique_ptr<light> m_light;
	std::unique_ptr<GrassGround> m_grass;
	std::unique_ptr<ShadowMap> m_ShadowMap;
	std::unique_ptr<ShadowMap2> m_ShadowMap2;
	std::unique_ptr<stencil_test> m_stencil_test;
	std::unique_ptr<Triangle> m_Triangle;
	std::unique_ptr<DynamicTextureBuffer> m_DynamicTextureBuffer_test;
	std::unique_ptr<Pointlight_ShadowCubemap> m_Pointlight_ShadowCubemap;
};