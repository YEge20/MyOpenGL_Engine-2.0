#pragma once
#include<gl/glew.h>
class DepthMapBuffer
{
public:
	DepthMapBuffer(int size);
	~DepthMapBuffer();

	unsigned int FBOid();
	void bind();
	void unbind();
	void use(unsigned int slot);

private:
	unsigned int m_FBO;
	unsigned int m_depthMap;
};