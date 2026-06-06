#include<GL/glew.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include "ImportModel.h"

ImportModel::ImportModel(GLFWwindow* window)
	:m_window(window)
{
	m_shader = std::make_shared<Shader>(false, "./shader/Test3DModel.shader");
	m_Camera = std::make_shared<KeyControlFor3D>(window, false, false);
	m_BackPack = std::make_shared<Model>("./texture/backpack/backpack2/backpack.obj");
	m_WindowSizeControl = std::make_shared<ResetWindowsize>(window, 1200, 800);

	m_roughnessTexture = std::make_shared<texture>("./texture/backpack/backpack2/roughness-1.jpg", false);
	unsigned int roughness_texture_unit = m_BackPack->GetTexture_MaxIndex() + 1;
	m_roughnessTexture->bind(roughness_texture_unit);
	m_shader->setuniform1i("extra_roughness", roughness_texture_unit);

	//3D渲染必须启动深度测试否侧渲染过程不正确：
	glEnable(GL_DEPTH_TEST);
}

void ImportModel::renderContext(float timestep, float milltimestep)
{
	m_WindowSizeControl->Resetsize();
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)m_WindowSizeControl->GetWidth() / (float)m_WindowSizeControl->GetHeight(), 0.1f, 450.0f);
	glm::mat4 CameraView = m_Camera->CameraMove(&m_CamPos, &m_camera_Fro, &m_camera_Up, 2.5f * timestep);
	glm::mat4 Rota = glm::toMat4(glm::quat(m_rotate));
	glm::mat4 MVP = Projection * CameraView * Rota;

	if(!m_WindowSizeControl->m_WindowHide)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 0.5f);

		m_shader->setuniformVEC3("u_CamPos", m_CamPos.x, m_CamPos.y, m_CamPos.z);
		m_shader->setuniformMat4f("u_Rota", Rota);
		m_BackPack->Draw(m_shader, MVP);
	}
}

void ImportModel::renderImguiContext()
{
	ImGui::DragFloat(u8"镜头距离", &m_CamPos.z, 0.02f);
	ImGui::DragFloat(u8"垂直旋转", &m_rotate.x, glm::radians(0.2f));
	ImGui::DragFloat(u8"水平旋转", &m_rotate.y, glm::radians(0.2f));
	ImGui::Text(u8"已加载进显存的材质:");
	ImGui::Image((ImTextureID)m_BackPack->GetTexture(0).id, ImVec2(200, 200));
	ImGui::SameLine();
	ImGui::Image((ImTextureID)m_BackPack->GetTexture(1).id, ImVec2(200, 200));
	ImGui::Image((ImTextureID)m_roughnessTexture->GetTextureID(), ImVec2(200, 200));
}