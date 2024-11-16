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
	glm::mat4 m_project_ortho;

	glm::vec3 m_camera_Pos;//摄像机的位置
	glm::vec3 m_camera_Fro;//摄像机的方向
	glm::vec3 m_camera_Up;//摄像机的向上方向
	float m_fov;

	std::shared_ptr<Shader> m_shader_block;
	std::shared_ptr<DrawBlock> m_block_model;
	glm::vec3 m_block_position;
	float m_block_rotation;

	std::shared_ptr<Shader> m_shader_blue_block;
	std::shared_ptr<DrawBlock> m_block_blue;
	glm::vec3 m_block_blue_position;

	std::shared_ptr<Shader> m_shader_DynamicTest;
	std::shared_ptr<DrawBlock> m_block_Dynamic;
	glm::vec3 m_DynamicScreen_position;
	float m_alpha;

	std::shared_ptr<KeyControlFor3D> m_control_Camera;
	std::unique_ptr<DynamicEnvironmentBuffer> m_DynamicEnvironment;

};

