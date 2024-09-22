#pragma once
#include<gl/glew.h>
class vertexbufferLayout1
{
public:
	vertexbufferLayout1(const void* data, const void* layout, const int DataBuffer, const int LayoutNumber);
	~vertexbufferLayout1();

	void bind();
	void unbind();
	void AttribPointer(const unsigned int CountOfIndex, const int* DataBufferSize, const int stride);
	unsigned int VAOid();
private:
	unsigned int m_vao, m_vbo, m_offset;
};