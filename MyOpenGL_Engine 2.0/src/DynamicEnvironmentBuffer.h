#pragma once
#include<iostream>
#include<Windows.h>
#include<gl/glew.h>
//这是设置帧缓冲方法，用于生成某个场景画面的贴图
enum Param
{
	LINEAR_MODE = 0, NEARLIST_MODE
};

class DynamicEnvironmentBuffer
{
public:
	//设置贴图的尺寸，最好与要渲染的平面的大小相同,param是设置贴图的过滤模式
	DynamicEnvironmentBuffer(int size, Param param = LINEAR_MODE);
	~DynamicEnvironmentBuffer();
	//绑定到对应的GL_TEXTURE插槽上去
	void setGLTextureSlot(int GL_Texture_slot);
	//在要开始生成的场景前绑定,会改变视口的大小
	void Bind();
	//结束场景贴图的渲染，请手动调用glviewport()手动复原回原来的视口大小！
	void UnBind();
private:
	unsigned int m_FBO;
	unsigned int m_DynamicEnvironmentTexture;
	unsigned int m_RBO;
	int m_width, m_height;
	Param m_param;//贴图的过滤模式
};