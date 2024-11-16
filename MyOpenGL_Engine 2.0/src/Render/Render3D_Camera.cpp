#include"Render3D_Camera.h"

Render3D_Camera::Render3D_Camera(GLFWwindow* window)
	:m_window(window),m_rotadegree(0),
	m_camera_Pos(0.0f, 0.0f, 30.0f), m_camera_Fro(0.0f,0.0f,-1.0f),m_camera_Up(0.0f,1.0f,0.0f),
	moreObject{ 
		{ 1.0f,0.0f,0.0f }, { 40.0f,25.0f,40.8f }, {-33.8f,10.0f,14.4f},{45.0f,-75.0f,-18.0f},{ -57.5f,-34.0f,40.0f},
		{30.0f,-12.0f,-75.0f},{ -21.0f,-27.0f,30.0f},{46.7f,-30.0f,35.0f}
	},
	moreObject_CraftTable{
		{-11.0f,0.0f,-8.8f},{17.9f,8.8f,-10.0f},{20.0f,16.6f,0.0f},{-18.8f,20.0f,0.0f},{-22.2f,-17.9f,0.0f},{21.4f,-18.9f,0.0f},
		{1.5f,0.0f,18.8f},{0.0f,0.0f,-20.0f}
	}
{
	std::cout << "Runnig Render3D_Camera.cpp" << std::endl;
	m_block1.reset(new DrawBlock(4.0f, 4.0f, 4.0f));
	m_block.reset(new DrawBlock(5.0f, 5.0f, 5.0f));


	m_block_shader.reset(new Shader("./shader/BasicShader3D(color_version).shader"));

	//材质设定：
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	std::vector<std::string> face =
	{
		"./texture/crafttable/crafting_table_top.png",
		"./texture/crafttable/oak_planks.png",
		"./texture/crafttable/crafting_table_side.png",
		"./texture/crafttable/crafting_table_side.png",
		"./texture/crafttable/crafting_table_front.png",
		"./texture/crafttable/crafting_table_front.png"
	};
	std::vector<std::string> face1 =
	{
		"./texture/furnace/furnace_top.png",
		"./texture/furnace/furnace_top.png",
		"./texture/furnace/furnace_side.png",
		"./texture/furnace/furnace_side.png",
		"./texture/furnace/furnace_front_on.png",
		"./texture/furnace/furnace_side.png"
	};
	m_block1->ImportTexture(face, false, SlotID_1);
	m_block->ImportTexture(face1, false, SlotID_1);

	//3D渲染必须启动深度测试否侧渲染过程不正确：
	glEnable(GL_DEPTH_TEST);

	m_control_Camera = std::make_unique<KeyControlFor3D>(m_window,true,true);
}

void Render3D_Camera::renderContext(float timestep, float milltimestep)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	m_fov = m_control_Camera->MousescrollFunction();
	m_project = glm::perspective(glm::radians(45.0f + m_fov), (float)960 / (float)640, 0.1f, 450.0f);
	glm::mat4 CameraView = m_control_Camera->CameraMove(&m_camera_Pos, &m_camera_Fro, &m_camera_Up, 0.5f);
	m_block_shader->bind();
	m_block_shader->setuniform1i("u_texture", 0);


	for (int x = 0; x < 8; x++)
	{	
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f),glm::radians(m_rotadegree),moreObject[x]);
		glm::mat4 position = glm::translate(glm::mat4(1.0f),moreObject[x]);
		glm::mat4 model = position * rotation;
		glm::mat4 MVP = m_project * CameraView * model;
		m_block_shader->setuniformMat4f("u_MVP", MVP);
		m_block->DrawCallTexture(0, 0, 0);
	}
	for (int i = 0; i < 8; i++)
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotadegree), moreObject_CraftTable[i]);
		glm::mat4 position = glm::translate(glm::mat4(1.0f), moreObject_CraftTable[i]);
		glm::mat4 model = position * rotation;
		glm::mat4 MVP1 = m_project * CameraView * model;
		m_block_shader->setuniformMat4f("u_MVP", MVP1);
		m_block1->DrawCallTexture(0, 0, 0);
	}
}

void Render3D_Camera::renderImguiContext()
{
	ImGui::SliderFloat("degree", &m_rotadegree, -90.0f, 90.0f);
	ImGui::Text("camera position: x:%.2f  y:%.2f  z:%2.f", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z);
	ImGui::Text("fov: %.2f", m_fov + 45.0f);
}
