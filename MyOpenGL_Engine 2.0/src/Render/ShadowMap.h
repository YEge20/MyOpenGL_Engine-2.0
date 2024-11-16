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
	float m_count_day;//天数
	float m_temperature;//温度(注意：此数值只能在-1~1的范围)
	float m_red_factor;
	float m_white_factor;
	float m_rad;
	float m_float_time;
	float m_GrassFlower_wave;//花草的摇摆幅度增量
	float m_GrassFlower_wave_current;//花草的实时摇摆幅度增量
	float m_degreeOflight;//光线的角度
	float m_degreeOflight_speed;//光线角度的速度
	float m_degreeOflight_speed_current;//光线角度的实时速度
	bool m_day;//判断是否为白天
	float m_strength_light;//光的强度
	

	GLFWwindow* m_window;
	glm::mat4 m_project;//设置透视投影矩阵
	glm::vec3 m_move;//设置矿石整体的位置
	glm::vec3 m_moreObject[16];//设置多个矿石的位置
	glm::vec3 m_moreObject_2[10];//设置多个草的位置
	glm::vec3 m_moreObject_3[10];//设置花的位置
	glm::vec3 m_light_position;//平行光的方向
	glm::vec3 m_light_color;//平行光的颜色
	glm::vec3 m_grass_move;//草地的位置
	glm::vec3 m_grass_2_move;//（组合）草的位置
	glm::vec3 m_flower_move;//（组合）花的位置
	glm::vec3 m_france_position;//熔炉的位置


	glm::vec3 m_camera_Pos;//摄像机的位置
	glm::vec3 m_camera_Fro;//摄像机的方向
	glm::vec3 m_camera_Up;//摄像机的向上方向


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