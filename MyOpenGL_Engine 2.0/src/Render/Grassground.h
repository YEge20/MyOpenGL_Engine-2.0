#pragma once

#include<memory>
#include"shader.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"ImguiFunction.h"
#include"vertexbufferLayout.h"
#include"texture32.h"
#include"Render/KeyControlFor3D.h"

class GrassGround
{
public:
	GrassGround(GLFWwindow* window);

	void renderContext();
	void renderImguiContext();
private:
	float m_fov;
	float m_rotaspeed;
	float m_speed_add;
	float m_red;
	float m_rad;

	GLFWwindow* m_window;
	glm::mat4 m_project;//����͸��ͶӰ����
	glm::vec3 m_move;//���ڵ��Ըı������λ��
	glm::vec3 m_moreObject[16];//���ö����¯��λ��
	glm::vec3 m_moreObject_2[10];//���ö���ݵ�λ��
	glm::vec3 m_moreObject_3[10];//���û���λ��
	glm::vec3 m_light_diraction;//ƽ�й�ķ���
	glm::vec3 m_light_color;//ƽ�й����ɫ
	glm::vec3 m_grass_move;//�ݵص�λ��
	glm::vec3 m_grass_2_move;//����ϣ��ݵ�λ��


	glm::vec3 m_camera_Pos;//�������λ��
	glm::vec3 m_camera_Fro;//������ķ���
	glm::vec3 m_camera_Up;//����������Ϸ���


	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Shader> m_shader_1;
	std::shared_ptr<Shader> m_shader_2;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout_1;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout_2;
	std::unique_ptr<KeyControlFor3D> m_control_Camera;
	std::unique_ptr<texture32> m_texture32;
};