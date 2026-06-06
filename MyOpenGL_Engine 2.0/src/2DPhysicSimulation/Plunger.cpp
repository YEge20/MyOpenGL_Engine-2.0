#include "Plunger.h"
#include <imGUI/imgui.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_edge_shape.h>
#include <box2d/b2_chain_shape.h>
#include <box2d/b2_circle_shape.h>
#include <box2d/b2_fixture.h>

//Util
#include "MouseUtils.h"

Plunger::Plunger(GLFWwindow* window)
	:m_WindowHandle(window){}

void Plunger::Create()
{
	//3D渲染必须启动深度测试否侧渲染过程不正确：
	glEnable(GL_DEPTH_TEST);
	m_Camera = CameraFor2D(m_WindowHandle, 1200, 800);
	m_Camera.Modifile_Scale(30);
	m_SizeControler = ResetWindowsize(m_WindowHandle, 1200, 800);
	m_MouseControler.Init(m_WindowHandle);

	m_SquareShader = std::make_shared<Shader>(false, "./shader/PhysicSimulationShader/DrawSquare.shader");
	m_CircleShader = std::make_shared<Shader>(false, "./shader/PhysicSimulationShader/DrawCircle.shader");
	m_LineShader = std::make_shared<Shader>(false, "./shader/PhysicSimulationShader/DrawLine.shader");

	b2Vec2 gravity(0.0f, 0.0f);
	m_world = new b2World(gravity);
	/////////////ground create/////////////////
	{
		b2BodyDef bodydef;
		bodydef.type = b2_staticBody;
		bodydef.position.Set(m_ground_pos.x, m_ground_pos.y);
		m_Ground = m_world->CreateBody(&bodydef);

		m_LongLine = std::make_shared<DrawLine>(glm::vec3(-20.0f, 0.0f, 0.0f), glm::vec3(20.0f, 0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		b2EdgeShape shape;
		b2Vec2 point1 = b2Vec2(-20.0f, 0.0f);
		b2Vec2 point2 = b2Vec2(20.0f, 0.0f);
		shape.SetTwoSided(point1, point2);
		m_Ground->CreateFixture(&shape, 1.0f);
	}
	//////////Plunger create//////////////////
	{
		b2BodyDef bodydef;
		bodydef.type = b2_dynamicBody;
		bodydef.position.Set(m_plunger_pos.x, m_plunger_pos.y);
		bodydef.fixedRotation = true;
		m_plunger = m_world->CreateBody(&bodydef);

		m_Square = std::make_shared<DrawSquare2D>(5.0f, 5.0f);
		b2PolygonShape shape;
		shape.SetAsBox(2.5f, 2.5f);
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 1.2f;
		fixture.friction = 0.1f;
		fixture.restitution = 0.2f;
		fixture.restitutionThreshold = 1.0f;
		m_plunger->CreateFixture(&fixture);
	}
	/////////////////conect plunger and ground with prismatic joint///////////////////
	{
		std::vector<LineVertex> vertex = {
			{glm::vec3(0.0f,2.5f,1.0f),glm::vec4(0.0f,1.0f,0.0f,1.0f)},
			{glm::vec3(0.0f,15.0f,1.0f),glm::vec4(1.0f,0.0f,0.0f,1.0f)}
		};
		m_Line = std::make_shared<DrawLine>(vertex);

		b2PrismaticJointDef jointdef;
		jointdef.Initialize(m_Ground, m_plunger, b2Vec2(0.0f, 5.0f), b2Vec2(0.0f, 1.0f));
		jointdef.lowerTranslation =  -2.5f;
		jointdef.upperTranslation = 10.0f;
		jointdef.enableLimit = true;

		m_world->CreateJoint(&jointdef);
	}
	////////////////FlyWheel create////////////////////////
	{
		b2BodyDef bodydef;
		bodydef.type = b2_dynamicBody;
		bodydef.position.Set(m_flywheel_pos.x, m_flywheel_pos.y);
		m_flyWheel = m_world->CreateBody(&bodydef);

		m_Circle = std::make_shared<DrawCircle>(5.0f, glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0.3f, 1.0f, 0.3f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 2.0f));
		b2CircleShape shape;
		shape.m_radius = 5.0f;
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 2.0f;
		fixture.friction = 0.1f;
		fixture.restitution = 0.1f;
		fixture.restitutionThreshold = 1.0f;
		m_flyWheel->CreateFixture(&fixture);
	}
	//////////////conect flywheel and ground with joint/////////////////////
	{
		b2RevoluteJointDef jointdef;
		jointdef.Initialize(m_Ground, m_flyWheel, b2Vec2(m_flywheel_pos.x, m_flywheel_pos.y));
		jointdef.maxMotorTorque = pow(abs(m_speed) * 1000.0f, 2);
		jointdef.motorSpeed = m_speed * 2 * b2_pi;
		jointdef.enableMotor = m_option;
		m_motorjoint = (b2RevoluteJoint*)m_world->CreateJoint(&jointdef);
	}
	////////////////bar create/////////////////////
	{
		b2BodyDef bodydef;
		bodydef.type = b2_dynamicBody;
		bodydef.position.Set(m_bar_pos.x, m_bar_pos.y);
		bodydef.fixedRotation = false;
		m_bar = m_world->CreateBody(&bodydef);

		m_LongSquare = std::make_shared<DrawSquare2D>(1.0f, 17.5f);
		b2PolygonShape shape;
		shape.SetAsBox(0.5f, 8.75f);
		b2FixtureDef fixture;
		fixture.shape = &shape;
		fixture.density = 0.5f;
		fixture.friction = 0.1f;
		fixture.restitution = 0.1f;
		fixture.restitutionThreshold = 1.0f;
		m_bar->CreateFixture(&fixture);
	}
	///////////////conect bar and plunger with joint///////////////////
	{
		b2RevoluteJointDef joint;
		joint.Initialize(m_bar, m_plunger, b2Vec2(m_plunger_pos.x, m_plunger_pos.y));
		joint.collideConnected = false;
		m_world->CreateJoint(&joint);
	}
	//////////////conect bar and flywheel with joint///////////////////
	{
		b2RevoluteJointDef joint;
		joint.Initialize(m_bar, m_flyWheel, b2Vec2(m_flywheel_pos.x, m_flywheel_pos.y - 4.5f));
		joint.collideConnected = false;
		m_world->CreateJoint(&joint);
	}
}

void Plunger::OnUpData(float timestep)
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

		glm::mat4 SquareModel = glm::translate(glm::mat4(1.0f), m_plunger_pos);
		glm::mat4 Square = CameraProj * SquareModel;
		m_SquareShader->setuniformMat4f("u_MVP", Square);
		m_SquareShader->setuniformVEC4("u_PureColor", 0.8f, 0.0f, 0.2f, 1.0f);
		m_Square->DrawCall();

		glm::mat4 BarModel = glm::translate(glm::mat4(1.0f), m_bar_pos) * 
						     glm::rotate(glm::mat4(1.0f), m_bar_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 Bar = CameraProj * BarModel;
		m_SquareShader->setuniformMat4f("u_MVP", Bar);
		m_SquareShader->setuniformVEC4("u_PureColor", 0.5f, 0.2f, 0.8f, 1.0f);
		m_LongSquare->DrawCall();
	}
	{
		m_CircleShader->bind();
		glm::mat4 CircleTranslate = glm::translate(glm::mat4(1.0f), m_flywheel_pos);
		glm::mat4 CircleRota = glm::rotate(glm::mat4(1.0f), m_flywheel_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 Circle = CameraProj * CircleTranslate * CircleRota;
		m_CircleShader->setuniformMat4f("u_MVP", Circle);
		m_CircleShader->setuniformMat4f("u_Rota", CircleRota);
		m_CircleShader->setuniform1f("u_Fade", 0.1f);
		m_Circle->DrawCall();
	}
	{
		m_LineShader->bind();

		glm::mat4 GroundModel = glm::translate(glm::mat4(1.0f), m_ground_pos);
		glm::mat4 Ground = CameraProj * GroundModel;
		m_LineShader->setuniformMat4f("u_MVP", Ground);
		m_LongLine->DrawCall();

		glm::mat4 LineModel = CameraProj;
		m_LineShader->setuniformMat4f("u_MVP", LineModel);
		m_Line->DrawCall();
	}
}

void Plunger::OnImGuiRender()
{
	glm::vec2 Mouse_WindowPos = m_MouseControler.GetMousePosition();
	glm::vec3 Mouse_WorldPos = Utils::WindowPos_to_WorldPos(Mouse_WindowPos, m_SizeControler.GetWidth(), m_SizeControler.GetHeight(), m_Camera);

	ImGui::Text("Plunger: (%.2f %.2f)",m_plunger_pos.x,m_plunger_pos.y);
	ImGui::Text("Mouse: (%.2f,%.2f)", Mouse_WorldPos.x, Mouse_WorldPos.y);
	ImGui::Checkbox("start engine", &m_option);
	ImGui::DragInt("set speed", &m_speed, 0.01f, -20, 20);
	float speed = m_flyWheel->GetAngularVelocity() / (2 * b2_pi);
	ImGui::Text("current speed: %.2f r/s",speed);
}

void Plunger::Destroy()
{
	delete m_world;
}

void Plunger::PhysicSystemCaculation(float timestep)
{
	if (m_option)
	{
		m_motorjoint->EnableMotor(true);
		m_motorjoint->SetMaxMotorTorque(pow(abs(m_speed) * 1000.0f, 2));
		m_motorjoint->SetMotorSpeed(m_speed * 2 * b2_pi);
	}
	else
	{
		m_motorjoint->EnableMotor(false);
		m_flyWheel->SetAngularVelocity(m_flyWheel->GetAngularVelocity() * (1 - timestep * 0.05f));
	}

	const unsigned int velocityIterations = 6;
	const unsigned int positionIterations = 2;
	m_world->Step(timestep, velocityIterations, positionIterations);

	b2Vec2 plunger_pos = m_plunger->GetPosition();
	m_plunger_pos = glm::vec3(plunger_pos.x, plunger_pos.y, m_plunger_pos.z);

	float flywheel_rotation = m_flyWheel->GetAngle();
	m_flywheel_rotation = flywheel_rotation;

	b2Vec2 bar_pos = m_bar->GetPosition();
	float bar_rota = m_bar->GetAngle();
	m_bar_pos = glm::vec3(bar_pos.x, bar_pos.y, m_bar_pos.z);
	m_bar_rotation = bar_rota;
}

