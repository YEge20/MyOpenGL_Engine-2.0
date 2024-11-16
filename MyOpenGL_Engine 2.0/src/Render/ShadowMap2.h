#pragma once
#include<memory>
#include<vector>
#include"shader.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"ImguiFunction.h"
#include"vertexbufferLayout.h"
#include"vertexbufferLayout_vao_Group.h"
#include"texture32.h"
#include"TextureBlock8.h"
#include"Render/KeyControlFor3D.h"
#include"DepthMapBuffer.h"

#include"DrawBlock.h"
#include"DynamicEnvironmentBuffer.h"
class ShadowMap2
{
public:
	ShadowMap2(GLFWwindow* window);

	void renderContext(float timestep, float milltimestep);
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


	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Shader> m_shader_1;
	std::shared_ptr<Shader> m_shader_2;
	std::shared_ptr<Shader> m_shader_depth;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout_1;
	std::unique_ptr<vertexbufferLayout_vao_Group> m_vertexbufferlayout_2;
	std::unique_ptr<KeyControlFor3D> m_control_Camera;
	std::shared_ptr<texture32> m_texture32;
	std::unique_ptr<TextureBlock8> m_textureblock1;
	std::unique_ptr<DepthMapBuffer> m_depth_texture;


	//�����¼���
	bool m_rain_occure_controler = false;//���������¼��Ƿ���

	std::shared_ptr<Shader> m_rainPartical_shader;
	std::shared_ptr<DrawBlock> m_rain_partical;//��ˮ������ģ��
	float m_partical_tick = 0.0f;
	float m_hight = 5.0f;//���ӵ�������߶�
	float m_partical_alpha = 0.0f;
	glm::vec3 m_partical[4] = { {0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} };
	glm::vec3 m_partical_center = { 0.0f,-114.5f,0.0f };//����Ч��������λ�õ���������
	glm::vec3 m_partical_front[4] = { {1.0f,0.0f,1.0f},{-1.0f,0.0f,-1.0f},{-1.0f,0.0f,1.0f},{1.0f,0.0f,-1.0f} };//ƫ�Ƶķ���


	std::shared_ptr<Shader> m_rain_shader;
	std::shared_ptr<DrawBlock> m_rain_drop;//��ˮ��ģ��
	float m_drop_Yposition[5] = {45.0f,45.0f,45.0f,45.0f,45.0f};//���������y����
	int m_drop_lay_count = 0;
	float m_drop_speed = 1.0f;

	std::shared_ptr<Shader> m_reflect_shader;
	std::shared_ptr<DrawBlock> m_water_reflect;
	std::shared_ptr<DynamicEnvironmentBuffer> m_reflect_texture;
	float m_reflect_alpha = 0.0f;
	float m_reflect_alpha_setup = 0.0f;
	glm::vec3 m_water_position = { 0.0f,-114.0f,0.0f };

	bool m_rain_drop_controler = true;//��������Ƿ��½�

	float m_rain_strength_light;//����ʱ���������ƽ�й������

	//ImGui��ť�б�����ã�
	bool m_GUIbutton_ore_pos_setup = false;
	bool m_GUIbutton_time_speed_setup = false;
	bool m_GUIbutton_rain_event_setup = false;
};

