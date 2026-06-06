#include <GL/glew.h>
#include "Hello_Box2D.h"
#include <imGUI/imgui.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_chain_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_revolute_joint.h>

//Utils
#include "MouseUtils.h"

HelloB2D::HelloB2D(GLFWwindow* window)
	:m_WindowHandle(window){}

void HelloB2D::Create()
{
	//3D渲染必须启动深度测试否侧渲染过程不正确：
	glEnable(GL_DEPTH_TEST);
	m_SquareShader = std::make_shared<Shader>(false, "./shader/PhysicSimulationShader/DrawSquare.shader");
	m_LineShader = std::make_shared<Shader>(false, "./shader/PhysicSimulationShader/DrawLine.shader");
	m_Camera = CameraFor2D(m_WindowHandle, 1200, 800);
	m_Camera.Modifile_Scale(40.0f);
	m_SizeControler = ResetWindowsize(m_WindowHandle, 1200, 800);
	m_MouseControler.Init(m_WindowHandle);

	b2Vec2 gravity(0.0f, -9.8f);
	m_world = new b2World(gravity);
	//////////////GroundBody Create/////////////
	{
		b2BodyDef bodydef;
		bodydef.type = b2_staticBody;
		bodydef.position.Set(m_StaticPosition.x, m_StaticPosition.y);
		m_StaticBody = m_world->CreateBody(&bodydef);

		m_StaticSquare = std::make_shared<DrawSquare2D>(20.0f, 2.5f);
		b2PolygonShape shape;
		shape.SetAsBox(10.0f, 1.25f);
		m_StaticBody->CreateFixture(&shape, 0.0f);
	}

	////////////JointBody Create////////////////
	{
		b2BodyDef bodydef;

		b2PolygonShape shape;
		shape.SetAsBox(2.5f, 0.5f);
		b2FixtureDef Fixture;
		Fixture.shape = &shape;
		Fixture.density = 2.0f;
		Fixture.friction = 0.2f;
		Fixture.restitution = 0.8f;
		Fixture.restitutionThreshold = 1.0f;

		m_JointSquare = std::make_shared<DrawSquare2D>(5.0f, 1.0f);

		/////A body/////
		bodydef.type = b2_dynamicBody;
		bodydef.position.Set(m_JointAPosition.x, m_JointAPosition.y);
		m_JointBodyA = m_world->CreateBody(&bodydef);
		m_JointBodyA->CreateFixture(&Fixture);
		/////B body/////
		bodydef.type = b2_dynamicBody;
		bodydef.position.Set(m_JointBPosition.x, m_JointBPosition.y);
		m_JointBodyB = m_world->CreateBody(&bodydef);
		m_JointBodyB->CreateFixture(&Fixture);

		/////create joint/////
		b2RevoluteJointDef jointDef;

		jointDef.Initialize(m_StaticBody, m_JointBodyA, b2Vec2(m_fixPosition.x, m_fixPosition.y));
		m_world->CreateJoint(&jointDef);

		jointDef.Initialize(m_JointBodyA, m_JointBodyB, b2Vec2(m_JointAPosition.x + 0.5f * 5.0f, 10));
		jointDef.collideConnected = false;
		m_world->CreateJoint(&jointDef);
	}

	////////////DyanmicBox Create///////////////
	{
		b2BodyDef bodydef;
		bodydef.type = b2_dynamicBody;
		bodydef.position.Set(m_DynamicPosition.x, m_DynamicPosition.y);
		bodydef.fixedRotation = false;//固定旋转，并取消角动量
		m_DynamicBody = m_world->CreateBody(&bodydef);

		m_DynamicSquare = std::make_shared<DrawSquare2D>(2.0f, 2.0f);
		b2PolygonShape shape;
		shape.SetAsBox(0.5f * 2.0f, 0.5f * 2.0f);
		b2FixtureDef Fixture;
		Fixture.shape = &shape;
		Fixture.density = 1.0f;
		Fixture.friction = 0.1f;
		Fixture.restitution = 0.8f;
		Fixture.restitutionThreshold = 1.0f;
		m_DynamicBody->CreateFixture(&Fixture);
	}

	///////////////////RainbowLine Create//////////////////////
	{
		b2BodyDef bodydef;
		bodydef.type = b2_staticBody;
		bodydef.position.Set(m_RainbowLinePosition.x,m_RainbowLinePosition.y);
		m_LineBody = m_world->CreateBody(&bodydef);

		std::vector<LineVertex> vertices = {
			{glm::vec3(-50.0f, 40.0f, 0.0f), glm::vec4(0.0f,1.0f,0.0f,1.0f)},
			{glm::vec3(-50.0f,-40.0f, 0.0f), glm::vec4(0.0f,0.0f,1.0f,1.0f)},
			{glm::vec3( 50.0f,-40.0f, 0.0f), glm::vec4(1.0f,1.0f,0.0f,1.0f)},
			{glm::vec3( 50.0f, 40.0f, 0.0f), glm::vec4(1.0f,0.0f,0.0f,1.0f)}
		};
		m_RainbowLine = std::make_shared<DrawLine>(vertices);
		//顺时针设置顶点顺序，法线朝内，碰撞面在里面，反之朝外
		b2Vec2 v[4];
		v[3].Set(-50.0f, 40.0f);
		v[2].Set(-50.0f,-40.0f);
		v[1].Set( 50.0f,-40.0f);
		v[0].Set( 50.0f, 40.0f);
		b2ChainShape shape;
		shape.CreateChain(v, 4, v[0], v[3]);
		m_LineBody->CreateFixture(&shape, 0.0f);
	}
}

void HelloB2D::OnUpData(float timestep)
{
	m_SizeControler.Resetsize();
	m_Camera.Modifile_ortho(m_SizeControler.GetWidth(), m_SizeControler.GetHeight());
	m_Camera.ControlCamera(timestep * 5.0f);
	
	glm::mat4 CameraProj = m_Camera.GetCameraMatrix();
	PhysicSystemCaculation(1.0f / 60.0f);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	{
		m_SquareShader->bind();
		glm::mat4 GroundModel = glm::translate(glm::mat4(1.0f), m_DynamicPosition) * glm::rotate(glm::mat4(1.0f),m_DynamicRotation,glm::vec3(0.0f,0.0f,1.0f));
		glm::mat4 Ground = CameraProj * GroundModel;
		m_SquareShader->setuniformMat4f("u_MVP", Ground);
		m_SquareShader->setuniformVEC4("u_PureColor", 0.2f, 0.8f, 0.2f, 1.0f);
		m_DynamicSquare->DrawCall();

		glm::mat4 DynamicModel = glm::translate(glm::mat4(1.0f), m_StaticPosition);
		glm::mat4 Dynamic = CameraProj * DynamicModel;
		m_SquareShader->setuniformMat4f("u_MVP", Dynamic);
		m_SquareShader->setuniformVEC4("u_PureColor", 0.8f, 0.2f, 0.2f, 1.0f);
		m_StaticSquare->DrawCall();

		glm::mat4 A_JointModel = glm::translate(glm::mat4(1.0f), m_JointAPosition)
							   * glm::rotate(glm::mat4(1.0f), m_ARotation, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 A_Joint = CameraProj * A_JointModel;
		m_SquareShader->setuniformMat4f("u_MVP",A_Joint);
		m_SquareShader->setuniformVEC4("u_PureColor", 0.8f, 0.4f, 0.0f, 1.0f);
		m_JointSquare->DrawCall();

		glm::mat4 B_JointModel = glm::translate(glm::mat4(1.0f), m_JointBPosition)
			* glm::rotate(glm::mat4(1.0f), m_BRotation, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 B_Joint = CameraProj * B_JointModel;
		m_SquareShader->setuniformMat4f("u_MVP", B_Joint);
		m_SquareShader->setuniformVEC4("u_PureColor", 0.4f, 0.0f, 8.0f, 1.0f);
		m_JointSquare->DrawCall();
	}
	{
		m_LineShader->bind();
		glm::mat4 RainbowLineModel = glm::translate(glm::mat4(1.0f), m_RainbowLinePosition);
		glm::mat4 Rainbow = CameraProj * RainbowLineModel;
		m_LineShader->setuniformMat4f("u_MVP", Rainbow);
		m_RainbowLine->DrawCall();
	}
}

void HelloB2D::OnImGuiRender()
{
	glm::vec3 Position = m_Camera.GetCameraPosition();
	bool awake = m_DynamicBody->IsAwake();
	glm::vec2 Mouse_WindowPos = m_MouseControler.GetMousePosition();
	glm::vec3 Mouse_WorldPos = Utils::WindowPos_to_WorldPos(Mouse_WindowPos, m_SizeControler.GetWidth(), m_SizeControler.GetHeight(), m_Camera);

	ImGui::Text("DynamicBox awake: %s", awake ? "true" : "false");
	ImGui::Text("DynamicBox: (%.2f,%.2f,%.2f)", m_DynamicPosition.x, m_DynamicPosition.y, m_DynamicPosition.z);
	ImGui::Separator();
	ImGui::Text("Camera World Pos: (%.2f,%.2f,%.2f)", Position.x, Position.y, Position.z);
	ImGui::Separator();
	ImGui::Text("Mouse World Pos: (%.2f,%.2f,%.2f)", Mouse_WorldPos.x, Mouse_WorldPos.y, Mouse_WorldPos.z);
	ImGui::Text("You can drag green box!");
	if (ImGui::Button("Reset green box"))
	{
		m_DynamicPosition = { 0.0f,4.0f,0.0f };;
		m_DynamicBody->SetTransform(b2Vec2(m_DynamicPosition.x, m_DynamicPosition.y), 0.0f);
		m_DynamicBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

		m_StaticPosition = { 0.0f,-8.0f,0.0f };
		m_StaticBody->SetTransform(b2Vec2(m_StaticPosition.x, m_StaticPosition.y), 0.0f);
	}
	m_imguiWindowhover = ImGui::IsItemHovered();
}

void HelloB2D::Destroy()
{
	delete m_world;
}

void HelloB2D::PhysicSystemCaculation(float timestep)
{
	if(!m_imguiWindowhover)
	{
		glm::vec2 Mouse_WindowPos = m_MouseControler.GetMousePosition();
		glm::vec3 Mouse_WorldPos = Utils::WindowPos_to_WorldPos(Mouse_WindowPos, m_SizeControler.GetWidth(), m_SizeControler.GetHeight(), m_Camera);
		if (!m_MouseControler.IsMouseButtonPress(MouseButton::LEFT))
			m_MouseApplyForce = Utils::IsSquareObject_Picked(Mouse_WorldPos, m_DynamicPosition, glm::vec2(2.0f, 2.0f), m_DynamicRotation);
		if (m_MouseApplyForce && m_MouseControler.IsMouseButtonPress(MouseButton::LEFT))
		{
			glm::vec3 force = Mouse_WorldPos - m_DynamicPosition;
			b2Vec2 b2_force = 50.0f * b2Vec2(force.x, force.y);
			b2Vec2 b2_Point = b2Vec2(m_DynamicPosition.x, m_DynamicPosition.y);
			m_DynamicBody->ApplyForce(b2_force, b2_Point, true);
			m_DynamicBody->SetLinearVelocity(0.90f * m_DynamicBody->GetLinearVelocity());
			m_DynamicBody->SetAngularVelocity(0.85f * m_DynamicBody->GetAngularVelocity());
		}
	}

	const unsigned int velocityIterations = 6;
	const unsigned int positionIterations = 2;
	m_world->Step(timestep, velocityIterations, positionIterations);

	b2Vec2 DynamicPosition = m_DynamicBody->GetPosition();
	float Dynamic_ZRotation = m_DynamicBody->GetAngle();
	m_DynamicPosition = glm::vec3(DynamicPosition.x, DynamicPosition.y, m_DynamicPosition.z);
	m_DynamicRotation = Dynamic_ZRotation;

	b2Vec2 JointA = m_JointBodyA->GetPosition();
	float ARotation = m_JointBodyA->GetAngle();
	b2Vec2 JointB = m_JointBodyB->GetPosition();
	float BRotation = m_JointBodyB->GetAngle();

	m_JointAPosition = glm::vec3(JointA.x, JointA.y, m_JointAPosition.z);
	m_ARotation = ARotation;
	m_JointBPosition = glm::vec3(JointB.x, JointB.y, m_JointBPosition.z);
	m_BRotation = BRotation;
}
