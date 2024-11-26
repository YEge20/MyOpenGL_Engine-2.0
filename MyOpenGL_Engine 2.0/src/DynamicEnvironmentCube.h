#pragma once
#include<gl/glew.h>
#include"shader.h"
#include<memory>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

class DynamicEnvironmentCube
{
public:
	//size为分辨率；parma为过滤，true是使用GL_LINEAR，false是使用GL_NEAREST；position为动态立方的几何中心坐标
	DynamicEnvironmentCube(int size, bool parma, glm::vec3 position);
	~DynamicEnvironmentCube();

	//渲染面顺序：右(face:0)->左(face:1)->上(face:2)->下(face:3)->前(face:4)->后(face:5),diract与face的值一样
	void bind(int face);

	//////渲染立方图时请务必使用这下面的两个矩阵渲染，才可以使得到立方贴图完整且正确//////
	/*相机矩阵函数，diract为6个面对应的方向*/
	glm::mat4 Dynamic_Cam(int diract);
	/*视图矩阵函数，返回一个正确的透视矩阵*/
	glm::mat4 Dynamic_Project();

	//结束渲染后请务必使用解绑并恢复到正常渲染，请手动调用glviewport()手动复原回原来的视口大小！
	void UnBind();
	//在渲染时必须调用:
	void UseDynamicCubeTexture();
	//用于改变反射位置的坐标:
	inline void Modifie_position(glm::vec3 new_position) { m_position = new_position; };

	////以下的三个函数提供测试你的动态立方贴图的样子，使用顺序如下////
	/*先初始化着色器（只执行一次）：*/
	void TestShader();
	/*然后绑定着色器（在循环中执行）：*/
	void TestShaderBind();
	/*最后设置MVP（在循环中更新）：*/
	void SetTestShaderMVP(glm::mat4 MVP);
private:
	unsigned int m_texture = 0, m_FBO = 0, m_RBO = 0;
	int m_width = 0, m_height = 0;
	bool m_param;
	glm::vec3 m_position = { 0.0f,0.0f,0.0f };
	std::shared_ptr<Shader> m_test_shader;//内置测试着色器
	bool m_intalize = false;//检查着色器是否已经加载，确保不会执行多次初始化
};