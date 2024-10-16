#pragma once
#include<memory>
#include<vector>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"shader.h"
#include"ImguiFunction.h"
#include"vertexbufferLayout.h"

class Triangle
{
public:
	Triangle(GLFWwindow* window);

	void renderContext();
	void renderImguiContext();
private:
	GLFWwindow* m_window;
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout;
};