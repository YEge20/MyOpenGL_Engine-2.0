#pragma once
#include<memory>
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
	std::shared_ptr<Shader> m_shader2;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout2;
};

/*ע��:����򵥵�������ʹ�õ�����ָ�뷽ʽ����������Ŀ����ͬ
* ���ӣ�m_vertexbufferlayout.reset(new vertexbufferlayout(trianglevertex, TLayout, triangle, triangleLayout));
* ���� .reset(new <����>(��������1����������2��...))�ķ�ʽ��ʼ�����������ĺô��ǲ���Ҫ�ٴθ������һ���µ�cpp���ļ���
*/