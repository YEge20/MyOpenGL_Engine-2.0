#pragma once
#include<memory>
#include<vector>
#include"shader.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"ImguiFunction.h"

#include"Render/KeyControlFor3D.h"

#include"DrawBlock.h"
#include"DynamicEnvironmentBuffer.h"
class DynamicTextureBuffer
{
public:
	DynamicTextureBuffer(GLFWwindow* window);
	void renderContext(float timestep, float milltimestep);
	void renderImguiContext();
private:
	GLFWwindow* m_window;

	glm::mat4 m_project;
	std::shared_ptr<KeyControlFor3D> m_control_Camera;
	glm::vec3 m_camera_Pos;//摄像机的位置
	glm::vec3 m_camera_Fro;//摄像机的方向
	glm::vec3 m_camera_Up;//摄像机的向上方向
	float m_fov;

	void scene_0(glm::mat4 project, glm::mat4 Camera);
	std::shared_ptr<Shader> m_shader_block;
	std::shared_ptr<DrawBlock> m_block_model;
	glm::vec3 m_block_position;
	float m_block_rotation;

	void scene_1(glm::mat4 project, glm::mat4 Camera);
	std::shared_ptr<Shader> m_shader_blue_block;
	std::shared_ptr<DrawBlock> m_block_blue;
	glm::vec3 m_block_blue_position;

	void scene_2(glm::mat4 project, glm::mat4 Camera);
	std::shared_ptr<Shader> m_shader_DynamicTest;
	std::shared_ptr<DrawBlock> m_block_Dynamic;
	glm::vec3 m_DynamicScreen_position;
	float m_alpha;
	std::unique_ptr<DynamicEnvironmentBuffer> m_DynamicEnvironment;

};

