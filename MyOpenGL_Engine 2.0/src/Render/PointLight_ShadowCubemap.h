#pragma once
#include<memory>
#include<vector>
#include"shader.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"ImguiFunction.h"

#include"Render/KeyControlFor3D.h"
#include"TextureBlock.h"

#include"DrawBlock.h"

//test:
#include"DynamicEnvironmentCube.h"
class Pointlight_ShadowCubemap
{
public:
	Pointlight_ShadowCubemap(GLFWwindow* window);
	void renderContext(float timestep, float milltimestep);
	void renderImguiContext();
private:
	GLFWwindow* m_window;

	std::shared_ptr<KeyControlFor3D> m_camera_controler;
	glm::vec3 m_camera_Pos = {0.0f,0.0f,5.0f};//摄像机的位置
	glm::vec3 m_camera_Fro = {0.0f,0.0f,-1.0f};//摄像机的方向
	glm::vec3 m_camera_Up = {0.0f,1.0f,0.0f};//摄像机的向上方向
	float m_fov = 0.0f;
	glm::mat4 m_projeect = { 0.0f }, m_Camera = { 0.0f };

	std::shared_ptr<Shader> m_sky_shader;
	std::shared_ptr<Shader> m_glass_shader;

	void m_scene_1(glm::mat4 project, glm::mat4 Camera, glm::vec3 Cam_Pos);
	std::shared_ptr<DrawBlock> m_glass_block;
	glm::vec3 m_glass_Pos[4] = { {5.0f,0.0f,5.0f},{-5.0f,0.0f,-5.0f},{-5.0f,0.0f,5.0f},{5.0f,0.0f,-5.0f} };
	float m_glass_rota = 0.0f;

	std::shared_ptr<DrawBlock> m_sky;
	std::shared_ptr<TextureBlock> m_SkyTexture;

	void m_test_scene(glm::mat4 project, glm::mat4 Camera, glm::vec3 Cam_Pos);
	std::shared_ptr<DynamicEnvironmentCube> m_dynamic_cube;
	std::shared_ptr<DrawBlock> m_dynamic_cube_model;
	glm::vec3 m_dynamic_Pos = { 0.0f,0.0f,0.0f };
};