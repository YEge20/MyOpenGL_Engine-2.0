#pragma once
#include<memory>
#include<vector>
#include"shader.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"ImguiFunction.h"

#include"vertexbufferLayout.h"
#include"Render/KeyControlFor3D.h"

#include"DrawBlock.h"

class Render3D_Camera
{
public:
	Render3D_Camera(GLFWwindow* window);

	void renderContext(float timestep, float milltimestep);
	void renderImguiContext();
private:
	float m_fov;
	float m_rotadegree;

	GLFWwindow* m_window;
	glm::mat4 m_project;//设置透视投影矩阵
	glm::vec3 moreObject[8];//设置多个相同物体的位置
	glm::vec3 moreObject_CraftTable[8];//设置多个物体的位置

	glm::vec3 m_camera_Pos;//摄像机的位置
	glm::vec3 m_camera_Fro;//摄像机的方向
	glm::vec3 m_camera_Up;//摄像机的向上方向


	std::unique_ptr<KeyControlFor3D> m_control_Camera;

	std::shared_ptr<DrawBlock> m_block;
	std::shared_ptr<DrawBlock> m_block1;
	std::shared_ptr<Shader> m_block_shader;
};