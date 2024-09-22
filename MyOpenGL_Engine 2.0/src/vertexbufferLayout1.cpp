#include"vertexbufferLayout1.h"

vertexbufferLayout1::vertexbufferLayout1(const void* data, const void* layout, const int DataBuffer, const int LayoutNumber)
	:m_vao(0), m_offset(0), m_vbo(0)

{
	unsigned int vertexlayout;
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, DataBuffer * sizeof(float), data, GL_STATIC_DRAW);

	glGenBuffers(1, &vertexlayout);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexlayout);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, LayoutNumber * sizeof(unsigned int), layout, GL_STATIC_DRAW);
}

vertexbufferLayout1::~vertexbufferLayout1()
{
	glDeleteVertexArrays(1, &m_vao);
}

void vertexbufferLayout1::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void vertexbufferLayout1::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vertexbufferLayout1::AttribPointer(const unsigned int CountOfIndex, const int* DataBufferSize, const int stride)
{
	for (unsigned int i = 0; i < CountOfIndex; i++)
	{
		glVertexAttribPointer(i, DataBufferSize[i], GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(m_offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		m_offset += DataBufferSize[i];
	}
}

unsigned int vertexbufferLayout1::VAOid()
{
	return m_vao;
}
