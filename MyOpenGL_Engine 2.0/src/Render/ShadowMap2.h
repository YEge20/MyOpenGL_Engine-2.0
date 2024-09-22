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
	float m_count_day = 0.0f;//天数
	float m_temperature = 0.0f;//温度(注意：此数值只能在-1~1的范围)
	float m_red_factor = 0.0f;
	float m_white_factor = 0.0f;
	float m_rad = 0.0f;//方块的旋转变量
	float m_float_time = 0.0f;//方块的漂浮效果变量
	float m_GrassFlower_wave = 0.0f;//花草的摇摆幅度增量
	float m_GrassFlower_wave_current = 0.0f;//花草的实时摇摆幅度增量
	float m_GrassFlower_Frequency = 0.5f;//花草的摇摆频率改变
	float m_GrassFlower_Frequency_current = 0.0f;//花草的实时摇摆频率改变
	float m_GrassFlower_shake_degree = 0.0f;//花草的摇摆变量
	float m_degreeOflight = 0.0f;//光线的角度
	float m_degreeOflight_speed = 0.05f;//光线角度的速度
	float m_degreeOflight_speed_current = 0.0f;//光线角度的实时速度
	bool m_day;//判断是否为白天
	float m_strength_light = 1.2f;//光的强度


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

