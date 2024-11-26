#pragma once
#include<iostream>
#include<Windows.h>
#include<gl/glew.h>
#include<memory>
#include"shader.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
//这是设置帧缓冲方法，用于生成某个场景画面的贴图
enum Param
{
	LINEAR_MODE = 0, NEARLIST_MODE
};

class DynamicEnvironmentBuffer
{
public:
	//初始化：size设置贴图的分辨率，param是设置贴图的过滤模式
	DynamicEnvironmentBuffer(int size, Param param = LINEAR_MODE);
	~DynamicEnvironmentBuffer();

	//在要开始生成的场景前绑定,会改变视口的大小
	void Bind();

	////使用该API推荐用这里提供的自动计算所需要的视图矩阵和相机矩阵////
	/*计算正交矩阵视图，width为渲染对象的宽度，height为渲染对象高度,farplane为能看到最远的距离*/
	glm::mat4 Caculate_Ortho_Project(float width, float height, float farplane);
	/*计算透视矩阵，fov_angle为视角夹角，单位是度，width是渲染对象的宽度，height为渲染对象高度,farplane为能看到最远的距离*/
	glm::mat4 Caculate_Perspective_Project(float fov_angle, float width, float height, float farplane);
	/*计算相机矩阵，Cam_Pos是观察时的位置，Cam_Fro是观察的方向（例如方向是沿着x轴的正方向，那就可以填入坐标glm::vec3(1.0f,0.0f,0.0f)）*/
	glm::mat4 Caculate_Camera(glm::vec3 Cam_Pos, glm::vec3 Cam_Fro);

	//结束渲染后请务必使用解绑并恢复到正常渲染，请手动调用glviewport()手动复原回原来的视口大小！
	void UnBind();
	//绑定到即将使用对应的GL_TEXTURE插槽上去
	void setGLTextureSlot(int GL_Texture_slot);

	////以下的三个函数提供测试你的动态立方贴图的样子，使用顺序如下////
	/*先初始化着色器（只执行一次）：*/
	void TestShader();
	/*然后绑定着色器（在循环中执行）：*/
	void TestShaderBind();
	/*最后设置MVP（在循环中更新）：*/
	void SetTestShaderMVP(glm::mat4 MVP);
private:
	unsigned int m_FBO;
	unsigned int m_DynamicEnvironmentTexture;
	unsigned int m_RBO;
	int m_width, m_height;
	Param m_param;//贴图的过滤模式
	std::shared_ptr<Shader> m_test_shader;
	bool m_shader_intalize = false;
};