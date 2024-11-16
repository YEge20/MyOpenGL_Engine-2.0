#pragma once
#include<gl/glew.h>
//��������֡���巽�������ڳ��������ͼ��ͼ
class DepthMapBuffer
{
public:
	DepthMapBuffer(int size);
	~DepthMapBuffer();

	unsigned int FBOid();
	void bind();//��Ҫ��ʼ���ɵĳ���ǰ��
	void unbind();//����������ͼ����Ⱦ
	void use(unsigned int slot);//�Զ�����ͼʹ�õ�GL_TEXTURE��ۣ������õĻ�Ĭ��ʹ��GL_TEXTURE0

private:
	unsigned int m_FBO;
	unsigned int m_depthMap;
};