#pragma once
#include "Project.h"
#include <box2d/b2_world.h>
#include <box2d//b2_body.h>
#include <box2d/b2_revolute_joint.h>
#include <box2d/b2_prismatic_joint.h>
#include <box2d/b2_wheel_joint.h>
#include <glm/glm.hpp>

#include <memory>
#include "../Renderer(V2.0)/RenderFor2D/API/2DCamera.h"
#include "../Renderer(V2.0)/RenderFor2D/API/DrawSquare.h"
#include "../Renderer(V2.0)/RenderFor2D/API/DrawLine.h"
#include "../Renderer(V2.0)/RenderFor2D/API/DrawCircle.h"
#include "../Renderer(V2.0)/RenderFor2D/API/MouseInput.h"

#include "../ResetWindowsize.h"
#include "../shader.h"

class Plunger : public Project
{
public:
	Plunger(GLFWwindow* window);
	virtual void Create() override;
	virtual void OnUpData(float timestep) override;
	virtual void OnImGuiRender() override;
	virtual void Destroy() override;
private:
	void PhysicSystemCaculation(float timestep);

	GLFWwindow* m_WindowHandle;
	CameraFor2D m_Camera;
	ResetWindowsize m_SizeControler;
	MouseInput m_MouseControler;
	b2World* m_world = nullptr;

	std::shared_ptr<Shader> m_SquareShader = nullptr;
	std::shared_ptr<Shader> m_CircleShader = nullptr;
	std::shared_ptr<Shader> m_LineShader = nullptr;

	std::shared_ptr<DrawSquare2D> m_Square = nullptr;
	std::shared_ptr<DrawSquare2D> m_LongSquare = nullptr;
	std::shared_ptr<DrawCircle> m_Circle = nullptr;
	std::shared_ptr<DrawLine> m_Line = nullptr;
	std::shared_ptr<DrawLine> m_LongLine = nullptr;

	glm::vec3 m_ground_pos = { 0.0f,-15.0f,0.0f };
	b2Body* m_Ground = nullptr;

	glm::vec3 m_plunger_pos = { 0.0f,5.0f,-2.0f };
	b2Body* m_plunger = nullptr;
	bool m_force_control = false;

	glm::vec3 m_flywheel_pos = { 0.0f,-8.0f,0.0f };
	float m_flywheel_rotation = 0.0f;
	b2Body* m_flyWheel = nullptr;

	bool m_option = false;
	int m_speed = 2;
	b2RevoluteJoint* m_motorjoint = nullptr;

	glm::vec3 m_bar_pos = { 0.0f,-4.0f,-1.0f };
	float m_bar_rotation = 0.0f;
	b2Body* m_bar = nullptr;
};