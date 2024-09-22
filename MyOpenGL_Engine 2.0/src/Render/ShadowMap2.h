#pragma once
#include<memory>
#include<vector>
#include"shader.h"
#include"shader1.h"
#include"shader3.h"
#include"shader2.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"ImguiFunction.h"
#include"vertexbufferLayout.h"
#include"vertexbufferLayout1.h"
#include"vertexbufferLayout_vao_Group.h"
#include"texture32.h"
#include"TextureBlock8.h"
#include"Render/KeyControlFor3D.h"
#include"DepthMapBuffer.h"
class ShadowMap2
{
public:
	ShadowMap2(GLFWwindow* window);

	void renderContext();
	void renderImguiContext();
private:
	float m_fov;
	float m_rotaspeed;
	float m_speed_add;
	float m_count_day = 0.0f;//����
	float m_temperature = 0.0f;//�¶�(ע�⣺����ֵֻ����-1~1�ķ�Χ)
	float m_red_factor = 0.0f;
	float m_white_factor = 0.0f;
	float m_rad = 0.0f;//�������ת����
	float m_float_time = 0.0f;//�����Ư��Ч������
	float m_GrassFlower_wave = 0.0f;//���ݵ�ҡ�ڷ�������
	float m_GrassFlower_wave_current = 0.0f;//���ݵ�ʵʱҡ�ڷ�������
	float m_GrassFlower_Frequency = 0.5f;//���ݵ�ҡ��Ƶ�ʸı�
	float m_GrassFlower_Frequency_current = 0.0f;//���ݵ�ʵʱҡ��Ƶ�ʸı�
	float m_GrassFlower_shake_degree = 0.0f;//���ݵ�ҡ�ڱ���
	float m_degreeOflight = 0.0f;//���ߵĽǶ�
	float m_degreeOflight_speed = 0.05f;//���߽Ƕȵ��ٶ�
	float m_degreeOflight_speed_current = 0.0f;//���߽Ƕȵ�ʵʱ�ٶ�
	bool m_day;//�ж��Ƿ�Ϊ����
	float m_strength_light = 1.2f;//���ǿ��


	GLFWwindow* m_window;
	glm::mat4 m_project;//����͸��ͶӰ����
	glm::vec3 m_move;//���ÿ�ʯ�����λ��
	glm::vec3 m_moreObject[16];//���ö����ʯ��λ��
	glm::vec3 m_moreObject_2[10];//���ö���ݵ�λ��
	glm::vec3 m_moreObject_3[10];//���û���λ��
	glm::vec3 m_light_position;//ƽ�й�ķ���
	glm::vec3 m_light_color;//ƽ�й����ɫ
	glm::vec3 m_grass_move;//�ݵص�λ��
	glm::vec3 m_grass_2_move;//����ϣ��ݵ�λ��
	glm::vec3 m_flower_move;//����ϣ�����λ��
	glm::vec3 m_france_position;//��¯��λ��


	glm::vec3 m_camera_Pos;//�������λ��
	glm::vec3 m_camera_Fro;//������ķ���
	glm::vec3 m_camera_Up;//����������Ϸ���


	std::unique_ptr<Shader> m_shader;
	std::unique_ptr<Shader1> m_shader_1;
	std::unique_ptr<shader3> m_shader_2;
	std::unique_ptr<Shader2> m_shader_depth;
	std::unique_ptr<vertexbufferlayout> m_vertexbufferlayout;
	std::unique_ptr<vertexbufferLayout1> m_vertexbufferlayout_1;
	std::unique_ptr<vertexbufferLayout_vao_Group> m_vertexbufferlayout_2;
	std::unique_ptr<KeyControlFor3D> m_control_Camera;
	std::unique_ptr<texture32> m_texture32;
	std::unique_ptr<TextureBlock8> m_textureblock1;
	std::unique_ptr<DepthMapBuffer> m_depth_texture;

};

