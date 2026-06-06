#include <GL/glew.h>
#include "DrawLine.h"

#define MAXPOINTS 100

DrawLine::DrawLine(const glm::vec3& Start, const glm::vec3& End, const glm::vec4& color)
{
	float square[2 * 7] = {
		Start.x,Start.y,Start.z,	 color.r,color.g,color.b,color.a,
		End.x,	End.y,	End.z,		 color.r,color.g,color.b,color.a
	};
	unsigned int layout[2] =
	{
		0,1
	};
	int index[2] =
	{
		3,4
	};
	m_vetices.reset(new vertexbufferlayout(square, layout, 2*7, 2));
	m_vetices->AttribPointer(2, index, 7);
}

DrawLine::DrawLine(std::vector<LineVertex> VerticesGroup)
{
	unsigned int vbo, veo;
	m_count = VerticesGroup.size();
	unsigned int index[MAXPOINTS];
	for (int x = 0; x < MAXPOINTS; x++)
		index[x] = x;

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &veo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, m_count * sizeof(LineVertex),
		&VerticesGroup[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(GLuint),
		index, GL_STATIC_DRAW);

	// 设置顶点坐标指针
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex),
		(GLvoid*)0);
	// 设置法线指针
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(LineVertex),
		(GLvoid*)offsetof(LineVertex, Color));
}

DrawLine::~DrawLine()
{
	if (m_vao)
		glDeleteVertexArrays(1, &m_vao);
}

void DrawLine::DrawCall()
{
	if(m_vetices)
	{
		m_vetices->bind();
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, nullptr);
	}
	if (m_vao)
	{
		glBindVertexArray(m_vao);
		glDrawElements(GL_LINE_STRIP, m_count, GL_UNSIGNED_INT, nullptr);
	}
}