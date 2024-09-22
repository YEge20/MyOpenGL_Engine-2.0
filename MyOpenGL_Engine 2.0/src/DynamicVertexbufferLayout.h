#pragma once
#include<gl/glew.h>
class DynamicVertexbufferLayout
{
public:
	DynamicVertexbufferLayout(const void* layout, const int DataBuffer, const int LayoutNumber);
	~DynamicVertexbufferLayout();

	void bind();
	void unbind();
	void AttribPointer(const int CountOfIndex, const int* DataBufferSize, const int stride);
	unsigned int VAOid();
private:
	unsigned int m_vao, m_vbo, m_offset;
};
