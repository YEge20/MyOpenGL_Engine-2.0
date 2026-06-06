#include<GL/glew.h>
#include"DrawSquare.h"

DrawSquare2D::DrawSquare2D(float X, float Y, float Z_position)
	:m_SizeX(X / 2.0f), m_SizeY(Y / 2.0f), m_ZPos(Z_position)
{
#define SquareFace 32
#define SquareElement 6
#define SquareIndex 3
	float square[SquareFace] = {
		//vertex:                   //uv:                //normalize:
		 m_SizeX,-m_SizeY, m_ZPos,    1.0f,0.0f,         0.0f,0.0f,1.0f,//0
		-m_SizeX,-m_SizeY, m_ZPos,    0.0f,0.0f,         0.0f,0.0f,1.0f,//1
		 m_SizeX, m_SizeY, m_ZPos,    1.0f,1.0f,         0.0f,0.0f,1.0f,//2
		-m_SizeX, m_SizeY, m_ZPos,    0.0f,1.0f,         0.0f,0.0f,1.0f,//3
	};
	unsigned int layout[SquareElement] =
	{
		0,1,2,
		1,2,3
	};
	int index[SquareIndex] =
	{
		3,2,3
	};
	int stride = 0;
	for (int i = 0; i < SquareIndex; i++)
		stride += index[i];

	m_vao.reset(new vertexbufferlayout(square, layout, SquareFace, SquareElement));
	m_vao->AttribPointer(SquareIndex, index, stride);
}

void DrawSquare2D::DrawCall()
{
	m_vao->bind();
	glDrawElements(GL_TRIANGLES, SquareElement, GL_UNSIGNED_INT, nullptr);
}
