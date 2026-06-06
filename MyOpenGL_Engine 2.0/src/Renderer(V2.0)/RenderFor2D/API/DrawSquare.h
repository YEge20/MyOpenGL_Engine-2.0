#pragma once
#include<memory>
#include"vertexbufferLayout.h"

class DrawSquare2D
{
public:
	DrawSquare2D(float X, float Y, float Z_position = 0.0f);
	void DrawCall();

private:
	float m_SizeX, m_SizeY, m_ZPos;
	std::shared_ptr<vertexbufferlayout> m_vao;
};