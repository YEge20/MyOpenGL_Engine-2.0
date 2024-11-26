#include "DynamicTextureBuffer.h"

DynamicTextureBuffer::DynamicTextureBuffer(GLFWwindow* window)
	:m_window(window), m_camera_Up{ 0.0f,1.0f,0.0f }, m_camera_Pos{ 0.0f,0.0f,10.0f }, m_camera_Fro{ 0.0f,0.0f,-1.0f },
	m_block_position{ 0.0f,0.0f,0.0f }, m_block_blue_position{ 0.0f,0.0f,-30.0f }, m_DynamicScreen_position{ 0.0f,0.0f,-20.0f }, m_alpha(1.0),
	m_block_rotation(0)
{
	std::cout << "Running DynamicTextureBuffer.cpp" << std::endl;

	m_block_model.reset(new DrawBlock(5.0f, 5.0f, 5.0f));
	m_shader_block.reset(new Shader("./shader/DynamicTextureTest/BasicShader3D(color_version).shader"));
	std::vector<std::string> model_texture =
	{
		"./texture/crafttable/crafting_table_top.png",
		"./texture/crafttable/oak_planks.png",
		"./texture/crafttable/crafting_table_side.png",
		"./texture/crafttable/crafting_table_side.png",
		"./texture/crafttable/crafting_table_front.png",
		"./texture/crafttable/crafting_table_front.png"
	};
	m_block_model->ImportTexture(model_texture, false, SlotID_1);

	m_block_blue.reset(new DrawBlock(10.0f, 10.0f, 10.0f));
	m_shader_blue_block.reset(new Shader("./shader/DynamicTextureTest/BasicShader3D_blueblock.shader"));

	m_block_Dynamic.reset(new DrawBlock(120.0f, 80.0f, 0.0f));
	m_shader_DynamicTest.reset(new Shader("./shader/DynamicTextureTest/2nd_BasicShader3D(color_version).shader"));

	//�����趨��
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//3D��Ⱦ����������Ȳ��Է����Ⱦ���̲���ȷ��
	glEnable(GL_DEPTH_TEST);

	m_control_Camera = std::make_unique<KeyControlFor3D>(m_window, true, true);
	m_DynamicEnvironment.reset(new DynamicEnvironmentBuffer(1024));
}

void DynamicTextureBuffer::renderContext(float timestep, float milltimestep)
{
	m_fov = m_control_Camera->MousescrollFunction();
	m_project = glm::perspective(glm::radians(45.0f + m_fov), (float)1200 / (float)800, 0.1f, 450.0f);
	glm::mat4 CameraView = m_control_Camera->CameraMove(&m_camera_Pos, &m_camera_Fro, &m_camera_Up, 10.0f * timestep);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//����֡��Ⱦ������
	m_DynamicEnvironment->Bind();
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 project_martix = m_DynamicEnvironment->Caculate_Ortho_Project(120.0f, 80.0f, 100.0f);
	glm::mat4 camera_martix = m_DynamicEnvironment->Caculate_Camera(m_DynamicScreen_position, glm::vec3(0.0f, 0.0f, 1.0f));
	scene_0(project_martix, camera_martix);
	//�ָ���ʵ���������Ⱦ����
	m_DynamicEnvironment->UnBind();
	glViewport(0, 0, 1200, 800);//������ֶ���ԭ�����������ӿڵĴ�С�ᱻ�޸ģ������ܿ����ķ�Χ���д���

	scene_0(m_project, CameraView);
	scene_1(m_project, CameraView);
	scene_2(m_project, CameraView);
}

void DynamicTextureBuffer::renderImguiContext()
{
	ImGui::SliderFloat("alpha", &m_alpha, 0.1, 1.0, "%.2f");
	ImGui::SliderFloat3("position", &m_block_position.x, -30.0f, 30.0f);
	if (ImGui::Button("reset position"))
		m_block_position = { 0.0f,0.0f,0.0f };
	ImGui::SliderFloat("rota", &m_block_rotation, -180.0f, 180.0f, "%.2f");
	ImGui::Text("camera position: x:%.2f  y:%.2f  z:%2.f", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z);
	ImGui::Text("Camera look at: x:%.2f  y:%.2f,  z:%.2f", m_control_Camera->GetCamera_Fro().x, m_control_Camera->GetCamera_Fro().y, m_control_Camera->GetCamera_Fro().z);
	ImGui::Text("Camera direct: x:%.2f  y:%.2f  z:%.2f", m_control_Camera->GetCamera_Normalize_Fro().x, m_control_Camera->GetCamera_Normalize_Fro().y, m_control_Camera->GetCamera_Normalize_Fro().z);
	ImGui::Text("fov: %.2f", m_fov + 45.0f);
}

void DynamicTextureBuffer::scene_0(glm::mat4 project, glm::mat4 Camera)
{
	m_shader_block->bind();
	glm::mat4 test_rota0 = glm::rotate(glm::mat4(1.0f), glm::radians(m_block_rotation), glm::vec3(1.0f, 1.0f, 0.0f));
	glm::mat4 test_position0 = glm::translate(glm::mat4(1.0f), m_block_position * glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 test_model0 = test_position0 * test_rota0;
	glm::mat4 test_MVP0 = project * Camera * test_model0;
	m_shader_block->setuniformMat4f("u_MVP", test_MVP0);
	m_shader_block->setuniform1i("u_texture", 1);
	m_block_model->DrawCallTexture(1, 0, 0);
}

void DynamicTextureBuffer::scene_1(glm::mat4 project, glm::mat4 Camera)
{
	m_shader_blue_block->bind();
	glm::mat4 test_blue_model = glm::translate(glm::mat4(1.0f), m_block_blue_position);
	glm::mat4 test_blue_MVP = project * Camera * test_blue_model;
	m_shader_blue_block->setuniformMat4f("u_MVP", test_blue_MVP);
	m_shader_blue_block->setuniformVEC3("u_block_color", 0.5f, 0.5f, 1.0f);
	m_block_blue->DrawCall();
}

void DynamicTextureBuffer::scene_2(glm::mat4 project, glm::mat4 Camera)
{
	m_shader_DynamicTest->bind();
	m_DynamicEnvironment->setGLTextureSlot(0);
	glm::mat4 test_Dynamic_model = glm::translate(glm::mat4(1.0f), m_DynamicScreen_position);
	glm::mat4 Dynamic_MVP = project * Camera * test_Dynamic_model;
	m_shader_DynamicTest->setuniformMat4f("u_MVP", Dynamic_MVP);
	m_shader_DynamicTest->setuniform1i("u_screenTexture", 0);//�ѻ���֡�õ�����ͼ�󶨵�ĳ��ƽ����
	m_shader_DynamicTest->setuniform1f("u_alpha", m_alpha);
	m_block_Dynamic->DrawCall();
}
