#pragma once
#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include "vertexbufferLayout.h"

struct LineVertex
{
	glm::vec3 Position;
	glm::vec4 Color;
};

//用于绘制线段
class DrawLine
{
public:
	DrawLine(const glm::vec3& Start, const glm::vec3& End, const glm::vec4& color);
	DrawLine(std::vector<LineVertex> VerticesGroup);
	~DrawLine();
	void DrawCall();
private:
	std::shared_ptr<vertexbufferlayout> m_vetices = nullptr;
	unsigned int m_vao = 0;
	unsigned int m_count = 0;
};
