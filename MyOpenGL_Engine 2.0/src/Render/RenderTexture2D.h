#pragma once
#include<memory>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"shader.h"
#include"ImguiFunction.h"
#include"ResetWindowsize.h"

//test
#include"Renderer(V2.0)/RenderFor2D/API/2DCamera.h"
#include"Renderer(V2.0)/RenderFor2D/API/DrawSquare.h"
#include"Renderer(V2.0)/RenderFor2D/API/ObjectKeyControl.h"
#include"texture(v2.0).h"

class RenderTexture2D
{
public:
	RenderTexture2D(GLFWwindow* window);

	void renderContext(float timestep, float milltimestep);
	void renderImguiContext();

private:
	GLFWwindow* m_window;
	std::shared_ptr<CameraFor2D> m_Camera;
	std::shared_ptr<ResetWindowsize> m_WindowSizeControler;
	std::shared_ptr<KeyControl> m_KeyControlr;

	void m_testSquareTexture(glm::mat4 Cam_proj);
	glm::vec3 m_Square_Pos = { 0.0f,0.0f,0.0f };
	std::shared_ptr<DrawSquare2D> m_Square1;
	std::shared_ptr<Texture_2D> m_Texture;
	std::shared_ptr<Shader> m_SquareShader;

	void m_testFlowerTexture(glm::mat4 Cam_proj);
	void m_testFlowerTextureStencilTest(glm::mat4 Cam_proj);
	std::shared_ptr<Shader> m_stencilShader;
	glm::vec3 m_FlowerPos = { 0.0f,7.5f,0.1f };
	std::shared_ptr<DrawSquare2D> m_Flower;
	std::shared_ptr<Texture_2D> m_FlowerTexture;

	float m_scale = 10.0f;
};