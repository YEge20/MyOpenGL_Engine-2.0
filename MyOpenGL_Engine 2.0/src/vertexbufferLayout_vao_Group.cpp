#include"vertexbufferLayout_vao_Group.h"

vertexbufferLayout_vao_Group::vertexbufferLayout_vao_Group()
	:m_vao{0}, m_offset(0), m_vbo{0}, m_veo{0}
{
	glGenVertexArrays(10, m_vao);

	glGenBuffers(10, m_vbo);

	glGenBuffers(10, m_veo);
}

vertexbufferLayout_vao_Group::~vertexbufferLayout_vao_Group()
{
	glDeleteVertexArrays(10, m_vao);
}

void vertexbufferLayout_vao_Group::importVertex(const void* data, const void* layout, const int DataBuffer, const int LayoutNumber, const int vao_group)
{
	glBindVertexArray(m_vao[vao_group]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[vao_group]);
	glBufferData(GL_ARRAY_BUFFER, DataBuffer * sizeof(float), data, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_veo[vao_group]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, LayoutNumber * sizeof(unsigned int), layout, GL_STATIC_DRAW);
}

void vertexbufferLayout_vao_Group::bind(const int vao_group)
{
	glBindVertexArray(m_vao[vao_group]);
}

void vertexbufferLayout_vao_Group::unbind()
{
	glBindVertexArray(0);
}

void vertexbufferLayout_vao_Group::AttribPointer(const unsigned int CountOfIndex, const int* DataBufferSize, const int stride, const int vao_group)
{
	glBindVertexArray(m_vao[vao_group]);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo[vao_group]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_veo[vao_group]);
	m_offset = 0;
	for (unsigned int i = 0; i < CountOfIndex; i++)
	{
		glVertexAttribPointer(i, DataBufferSize[i], GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(m_offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		m_offset += DataBufferSize[i];
	}
}

unsigned int vertexbufferLayout_vao_Group::VAOid(const int vao_group)
{
	return m_vao[vao_group];
}

