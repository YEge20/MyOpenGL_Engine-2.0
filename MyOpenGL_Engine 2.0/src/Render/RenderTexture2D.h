#pragma once
#include<memory>
#include"shader.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"ImguiFunction.h"
#include"DynamicVertexbufferLayout.h"
#include"vertexbufferLayout.h"
#include"texture32.h"
#include"KeyControl.h"
#include"KeyControlFor3D.h"

class RenderTexture2D
{
public:
	RenderTexture2D(GLFWwindow* window);

	void renderContext(float timestep, float milltimestep);
	void renderImguiContext();

private:
	GLFWwindow* m_window;
	
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Shader> m_shader1;
	std::shared_ptr<DynamicVertexbufferLayout> m_dynamicLayout;
	std::shared_ptr<vertexbufferlayout> m_vertexLayout;
	std::unique_ptr<texture32> m_texture;
	std::unique_ptr<KeyControlFunction> m_keyboard;

	glm::mat4 m_project2;//��������ͶӰ����
	glm::vec3 m_layoutObject1;//��������1���õĳ�ʼλ��

	glm::vec3 m_camera;//����ģ���������λ��

	bool m_gravity, m_quake_switch;
	float m_XY[2];
	float m_time;
	float m_light[3];
	float m_rota;
};