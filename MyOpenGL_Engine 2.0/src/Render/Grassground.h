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
	glm::mat4 m_project;//设置透视投影矩阵
	glm::vec3 m_move;//用于调试改变物体的位置
	glm::vec3 m_moreObject[16];//设置多个熔炉的位置
	glm::vec3 m_moreObject_2[10];//设置多个草的位置
	glm::vec3 m_moreObject_3[10];//设置花的位置
	glm::vec3 m_light_diraction;//平行光的方向
	glm::vec3 m_light_color;//平行光的颜色
	glm::vec3 m_grass_move;//草地的位置
	glm::vec3 m_grass_2_move;//（组合）草的位置


	glm::vec3 m_camera_Pos;//摄像机的位置
	glm::vec3 m_camera_Fro;//摄像机的方向
	glm::vec3 m_camera_Up;//摄像机的向上方向


	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Shader> m_shader_1;
	std::shared_ptr<Shader> m_shader_2;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout_1;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout_2;
	std::unique_ptr<KeyControlFor3D> m_control_Camera;
	std::unique_ptr<texture32> m_texture32;
};