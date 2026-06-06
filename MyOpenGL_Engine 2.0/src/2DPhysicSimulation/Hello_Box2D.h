#pragma once
#include "Project.h"
#include <box2d/b2_world.h>
#include <box2d//b2_body.h>
#include <glm/glm.hpp>

#include <memory>
#include "../Renderer(V2.0)/RenderFor2D/API/2DCamera.h"
#include "../Renderer(V2.0)/RenderFor2D/API/DrawSquare.h"
#include "../Renderer(V2.0)/RenderFor2D/API/DrawLine.h"
#include "../Renderer(V2.0)/RenderFor2D/API/MouseInput.h"

#include "../ResetWindowsize.h"
#include "../shader.h"

class HelloB2D : public Project
{
public:
	HelloB2D(GLFWwindow* window);
	virtual void Create() override;
	virtual void OnUpData(float timestep) override;
	virtual void OnImGuiRender() override;
	virtual void Destroy() override;
private:
	void PhysicSystemCaculation(float timestep);

	GLFWwindow* m_WindowHandle;
	std::shared_ptr<Shader> m_SquareShader;
	CameraFor2D m_Camera;
	ResetWindowsize m_SizeControler;
	MouseInput m_MouseControler;
	bool m_imguiWindowhover = false;

	b2World* m_world = nullptr;

	b2Body* m_StaticBody = nullptr;
	std::shared_ptr<DrawSquare2D> m_StaticSquare;
	glm::vec3 m_StaticPosition = { 0.0f,-8.0f,0.0f };

	bool m_MouseApplyForce = false;
	b2Body* m_DynamicBody = nullptr;
	std::shared_ptr<DrawSquare2D> m_DynamicSquare;
	glm::vec3 m_DynamicPosition = { 0.0f,4.0f,0.0f };
	float m_DynamicRotation = 0.0f;

	std::shared_ptr<DrawSquare2D> m_JointSquare;
	glm::vec2 m_fixPosition = { 0.0f,10.0f };
	b2Body* m_JointBodyA = nullptr;
	glm::vec3 m_JointAPosition = { 2.5f,10.0f,0.0f };
	float m_ARotation = 0.0f;
	b2Body* m_JointBodyB = nullptr;
	glm::vec3 m_JointBPosition = { 7.5f,10.0f,0.0f };
	float m_BRotation = 0.0f;

	std::shared_ptr<Shader> m_LineShader;
	b2Body* m_LineBody = nullptr;
	std::shared_ptr<DrawLine> m_RainbowLine;
	glm::vec3 m_RainbowLinePosition = { 0.0f,20.0f,0.0f };
};
