#pragma once
#include<iostream>
#include<Windows.h>
#include<gl/glew.h>
//��������֡���巽������������ĳ�������������ͼ
enum Param
{
	LINEAR_MODE = 0, NEARLIST_MODE
};

class DynamicEnvironmentBuffer
{
public:
	//������ͼ�ĳߴ磬�����Ҫ��Ⱦ��ƽ��Ĵ�С��ͬ,param��������ͼ�Ĺ���ģʽ
	DynamicEnvironmentBuffer(int size, Param param = LINEAR_MODE);
	~DynamicEnvironmentBuffer();
	//�󶨵���Ӧ��GL_TEXTURE�����ȥ
	void setGLTextureSlot(int GL_Texture_slot);
	//��Ҫ��ʼ���ɵĳ���ǰ��,��ı��ӿڵĴ�С
	void Bind();
	//����������ͼ����Ⱦ�����ֶ�����glviewport()�ֶ���ԭ��ԭ�����ӿڴ�С��
	void UnBind();
private:
	unsigned int m_FBO;
	unsigned int m_DynamicEnvironmentTexture;
	unsigned int m_RBO;
	int m_width, m_height;
	Param m_param;//��ͼ�Ĺ���ģʽ
};