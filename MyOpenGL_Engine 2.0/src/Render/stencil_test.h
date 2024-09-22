#pragma once
#include<memory>
#include"shader.h"
#include"shader1.h"
#include"shader2.h"
#include"shader3.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"ImguiFunction.h"
#include"vertexbufferLayout.h"
#include"vertexbufferLayout1.h"
#include"vertexbufferLayout2.h"
#include"texture32.h"
#include"TextureBlock.h"
#include"Render/KeyControlFor3D.h"
class stencil_test
{
public:
	stencil_test(GLFWwindow* window);

	void renderContext();
	void renderImguiContext();
private:
	float m_fov;
	float m_skyboxLight;//��պе�����
	float m_Plight_dis;//���Դ֮��ľ������
	float m_object_dis;//����֮��ľ������
	bool m_option_stencil = false;
	bool m_stencil_Xray = false;

	GLFWwindow* m_window;
	glm::mat4 m_project;//����͸��ͶӰ����
	glm::vec3 m_move;//�������λ��
	glm::vec3 m_location[9];//ÿ�������λ��
	glm::vec3 m_move1[6];//��Դ��λ��
	glm::vec3 m_lightcolor;//��Դ����ɫ


	glm::vec3 m_camera_Pos;//�������λ��
	glm::vec3 m_camera_Fro;//������ķ���
	glm::vec3 m_camera_Up;//����������Ϸ���


	std::unique_ptr<Shader> m_shader;
	std::unique_ptr<Shader1> m_shader1;
	std::unique_ptr<Shader2> m_shader_stencil;
	std::unique_ptr<shader3> m_shaderSkybox;
	std::unique_ptr<vertexbufferlayout> m_vertexbufferlayout;
	std::unique_ptr<vertexbufferLayout1> m_vertexbufferlayout1;
	std::unique_ptr<vertexbufferLayout2> m_vertexbufferlayout2;
	std::unique_ptr<texture32> m_texture32;
	std::unique_ptr<TextureBlock> m_textureblock;
	std::unique_ptr<KeyControlFor3D> m_control_Camera;

};

