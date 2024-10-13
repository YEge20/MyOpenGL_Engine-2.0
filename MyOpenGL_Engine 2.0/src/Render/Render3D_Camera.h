#pragma once
#include<memory>
#include<vector>
#include"shader.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"ImguiFunction.h"

#include"vertexbufferLayout.h"
#include"TextureBlock8.h"
#include"Render/KeyControlFor3D.h"

class Render3D_Camera
{
public:
	Render3D_Camera(GLFWwindow* window);

	void renderContext();
	void renderImguiContext();
private:
	float m_fov,m_fire_light;
	bool m_key_check;
	float m_rotadegree;

	GLFWwindow* m_window;
	glm::mat4 m_project;//设置透视投影矩阵
	glm::vec3 m_move;//用于调试改变物体的位置
	glm::vec3 moreObject[8];//设置多个相同物体的位置
	glm::vec3 m_light_diraction;
	glm::vec3 m_light_color;

	glm::vec3 m_camera_Pos;//摄像机的位置
	glm::vec3 m_camera_Fro;//摄像机的方向
	glm::vec3 m_camera_Up;//摄像机的向上方向


	std::unique_ptr<Shader> m_shader;
	std::unique_ptr<vertexbufferlayout> m_vertexbufferlayout;
	std::unique_ptr<KeyControlFor3D> m_control_Camera;
	std::unique_ptr<TextureBlock8> m_textureblock;
};