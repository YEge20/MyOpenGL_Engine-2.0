#pragma once
#include<gl/glew.h>
//这是设置帧缓冲方法，用于场景的深度图贴图
class DepthMapBuffer
{
public:
	DepthMapBuffer(int size);
	~DepthMapBuffer();

	unsigned int FBOid();
	void bind();//在要开始生成的场景前绑定
	void unbind();//结束场景贴图的渲染
	void use(unsigned int slot);//自定义贴图使用的GL_TEXTURE插槽，不调用的话默认使用GL_TEXTURE0

private:
	unsigned int m_FBO;
	unsigned int m_depthMap;
};