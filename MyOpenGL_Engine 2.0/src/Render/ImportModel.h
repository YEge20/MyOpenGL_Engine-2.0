#pragma once
#include<memory>
#include<vector>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"shader.h"
#include"ImguiFunction.h"
#include"Render/KeyControlFor3D.h"
#include"ResetWindowsize.h"
#include"texture.h"

#include"../Renderer(V2.0)/Mesh/Model.h"

class ImportModel
{
public:
	ImportModel(GLFWwindow* window);

	void renderContext(float timestep, float milltimestep);
	void renderImguiContext();
private:
	GLFWwindow* m_window;
	std::shared_ptr<ResetWindowsize> m_WindowSizeControl;
	std::shared_ptr<Shader> m_shader;

	std::shared_ptr<KeyControlFor3D> m_Camera;
	glm::vec3 m_CamPos = { 0.0f,0.0f,5.0f };
	glm::vec3 m_camera_Fro = { 0.0f,0.0f,-1.0f };//摄像机的方向
	glm::vec3 m_camera_Up = { 0.0f,1.0f,0.0f };//摄像机的向上方向

	std::shared_ptr<Model> m_BackPack;
	std::shared_ptr<texture> m_roughnessTexture;
	glm::vec3 m_rotate = { 0.0f,0.0f,0.0f };
};