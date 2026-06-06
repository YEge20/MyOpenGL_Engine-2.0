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

	GLFWwindow* m_window;
	glm::mat4 m_project;//设置透视投影矩阵
	glm::vec3 m_camera_Pos;//摄像机的位置
	glm::vec3 m_camera_Fro;//摄像机的方向
	glm::vec3 m_camera_Up;//摄像机的向上方向
	std::unique_ptr<KeyControlFor3D> m_control_Camera;

	float m_rotadegree;
	std::shared_ptr<Shader> m_block_shader;

	std::shared_ptr<DrawBlock> m_block;
	void Furance(glm::mat4& project, glm::mat4& Camera, glm::vec3& Cam_Pos);
	glm::vec3 moreObject = { 0.0f,0.0f,0.0f };//设置物体的位置

	std::shared_ptr<DrawBlock> m_block1;
	void CraftTable(glm::mat4& project, glm::mat4& Camera, glm::vec3& Cam_Pos);
	glm::vec3 moreObject_CraftTable = { 0.0f,8.8f,-4.0f };//设置物体的位置

	std::shared_ptr<Shader> m_pureColorShader;
	std::shared_ptr<DrawBlock> m_testColorBlock;
	void ColorBlock(glm::mat4& project, glm::mat4& Camera, glm::vec3& Cam_Pos);
	glm::vec3 m_colorBlock_Pos = { -10.0f,0.0f,-8.0f };

};