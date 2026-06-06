#include <GL/glew.h>
#include "DrawCircle.h"

DrawCircle::DrawCircle(float size, const glm::vec3& color)
{
	float square[36] = {
		//vertex:			RGB:						local_pos
		 size,-size, 0.0f,  color.r,color.g,color.b,     1.0f,-1.0f,0.0f,
		-size,-size, 0.0f,  color.r,color.g,color.b,    -1.0f,-1.0f,0.0f,
		 size, size, 0.0f,  color.r,color.g,color.b,     1.0f, 1.0f,0.0f,
		-size, size, 0.0f,  color.r,color.g,color.b,    -1.0f, 1.0f,0.0f
	};
	unsigned int layout[6] =
	{
		0,1,2,
		1,2,3
	};
	int index[3] =
	{
		3,3,3
	};
	m_vertices.reset(new vertexbufferlayout(square, layout, 36, 6));
	m_vertices->AttribPointer(3, index, 9);
}

DrawCircle::DrawCircle(float size, const glm::vec3& RGB_1, const glm::vec3& RGB_2, const glm::vec3& RGB_3, const glm::vec3& RGB_4)
{
	float square[36] = {
		//vertex:			RGB:						 local_pos
		 size,-size, 0.0f,  RGB_1.r,RGB_1.g,RGB_1.b,      1.0f,-1.0f,0.0f,
		-size,-size, 0.0f,  RGB_2.r,RGB_2.g,RGB_2.b,     -1.0f,-1.0f,0.0f,
		 size, size, 0.0f,  RGB_3.r,RGB_3.g,RGB_3.b,      1.0f, 1.0f,0.0f,
		-size, size, 0.0f,  RGB_4.r,RGB_4.g,RGB_4.b,     -1.0f, 1.0f,0.0f
	};
	unsigned int layout[6] =
	{
		0,1,2,
		1,2,3
	};
	int index[3] =
	{
		3,3,3
	};
	m_vertices.reset(new vertexbufferlayout(square, layout, 36, 6));
	m_vertices->AttribPointer(3, index, 9);
}

void DrawCircle::DrawCall()
{
	if(m_vertices)
	{
		m_vertices->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}
