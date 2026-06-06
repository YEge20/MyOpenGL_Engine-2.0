#pragma once
#include<memory>
#include<glm/glm.hpp>
#include"vertexbufferLayout.h"

class DrawCircle
{
public:
	DrawCircle(float size, const glm::vec3& color);
	DrawCircle(float size, const glm::vec3& RGB_1, const glm::vec3& RGB_2, const glm::vec3& RGB_3, const glm::vec3& RGB_4);
	void DrawCall();

private:
	std::shared_ptr<vertexbufferlayout> m_vertices;
};