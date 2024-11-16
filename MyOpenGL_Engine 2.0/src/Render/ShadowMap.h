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
#include"TextureBlock.h"
#include"Render/KeyControlFor3D.h"
#include"DepthMapBuffer.h"

class ShadowMap
{
public:
	ShadowMap(GLFWwindow* window);

	void renderContext(float timestep, float milltimestep);
	void renderImguiContext();

private:
	float m_fov;
	float m_rotaspeed;
	float m_speed_add;
	float m_count_day;//����
	float m_temperature;//�¶�(ע�⣺����ֵֻ����-1~1�ķ�Χ)
	float m_red_factor;
	float m_white_factor;
	float m_rad;
	float m_float_time;
	float m_GrassFlower_wave;//���ݵ�ҡ�ڷ�������
	float m_GrassFlower_wave_current;//���ݵ�ʵʱҡ�ڷ�������
	float m_degreeOflight;//���ߵĽǶ�
	float m_degreeOflight_speed;//���߽Ƕȵ��ٶ�
	float m_degreeOflight_speed_current;//���߽Ƕȵ�ʵʱ�ٶ�
	bool m_day;//�ж��Ƿ�Ϊ����
	float m_strength_light;//���ǿ��
	

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
	std::unique_ptr<texture32> m_texture32;
	std::unique_ptr<TextureBlock> m_textureblock;
	std::unique_ptr<DepthMapBuffer> m_depth_texture;

};