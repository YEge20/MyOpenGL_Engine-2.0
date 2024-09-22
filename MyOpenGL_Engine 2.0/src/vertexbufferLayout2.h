#pragma once
#include<gl/glew.h>
class vertexbufferLayout2
{
public:
	vertexbufferLayout2(const void* data, const void* layout, const int DataBuffer, const int LayoutNumber);
	~vertexbufferLayout2();

	void bind();
	void unbind();
	void AttribPointer(const unsigned int CountOfIndex, const int* DataBufferSize, const int stride);
	unsigned int VAOid();

private:
	unsigned int m_vao, m_vbo, m_offset;

};