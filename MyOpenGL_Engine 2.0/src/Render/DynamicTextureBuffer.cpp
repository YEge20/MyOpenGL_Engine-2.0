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

	//材质设定：
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//3D渲染必须启动深度测试否侧渲染过程不正确：
	glEnable(GL_DEPTH_TEST);

	m_control_Camera = std::make_unique<KeyControlFor3D>(m_window, true, true);
	m_DynamicEnvironment.reset(new DynamicEnvironmentBuffer(1024));
}

void DynamicTextureBuffer::renderContext(float timestep, float milltimestep)
{
	m_fov = m_control_Camera->MousescrollFunction();
	m_project = glm::perspective(glm::radians(45.0f + m_fov), (float)1200 / (float)800, 0.1f, 450.0f);
	m_project_ortho = glm::ortho(-60.0f, 60.0f, -40.0f, 40.0f, 0.1f, 100.0f);
	glm::mat4 CameraView = m_control_Camera->CameraMove(&m_camera_Pos, &m_camera_Fro, &m_camera_Up, 0.5f);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//缓冲帧渲染的内容
	m_DynamicEnvironment->Bind();
	m_DynamicEnvironment->setGLTextureSlot(0);
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_shader_block->bind();
	glm::mat4 test_rota = glm::rotate(glm::mat4(1.0f), glm::radians(m_block_rotation), glm::vec3(1.0f,1.0f,0.0f));
	glm::mat4 test_position = glm::translate(glm::mat4(1.0f), m_block_position * glm::vec3(1.0f,1.0f,1.0f));
	glm::mat4 test_model = test_position * test_rota;
	glm::mat4 camera_martix = glm::lookAt(m_DynamicScreen_position, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 test_MVP = m_project_ortho * camera_martix * test_model;
	//m_shader_block->setuniformVEC3("u_block_color", 1.0f, 0.0f, 0.0f);
	m_shader_block->setuniform1i("u_texture", 1);
	m_shader_block->setuniformMat4f("u_MVP", test_MVP);
	m_block_model->DrawCallTexture(1, 0, 0);

	//恢复到实际输出的渲染内容
	m_DynamicEnvironment->UnBind();
	glViewport(0, 0, 1200, 800);//请务必手动复原！！！否则视口的大小会被修改，导致能看到的范围会有错误
	m_shader_block->bind();
	glm::mat4 test_rota0 = glm::rotate(glm::mat4(1.0f), glm::radians(m_block_rotation), glm::vec3(1.0f, 1.0f, 0.0f));
	glm::mat4 test_position0 = glm::translate(glm::mat4(1.0f), m_block_position * glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 test_model0 = test_position0 * test_rota0;
	glm::mat4 test_MVP0 = m_project * CameraView * test_model0;
	m_shader_block->setuniformMat4f("u_MVP", test_MVP0);
	//m_shader_block->setuniformVEC3("u_block_color", 1.0f, 0.0f, 0.0f);
	m_shader_block->setuniform1i("u_texture", 1);
	m_block_model->DrawCallTexture(1, 0, 0);

	m_shader_blue_block->bind();
	glm::mat4 test_blue_model = glm::translate(glm::mat4(1.0f), m_block_blue_position);
	glm::mat4 test_blue_MVP = m_project * CameraView * test_blue_model;
	m_shader_blue_block->setuniformMat4f("u_MVP", test_blue_MVP);
	m_shader_blue_block->setuniformVEC3("u_block_color", 0.5f, 0.5f, 1.0f);
	m_block_blue->DrawCall();

	m_shader_DynamicTest->bind();
	glm::mat4 test_Dynamic_model = glm::translate(glm::mat4(1.0f), m_DynamicScreen_position);
	glm::mat4 Dynamic_MVP = m_project * CameraView * test_Dynamic_model;
	m_shader_DynamicTest->setuniformMat4f("u_MVP", Dynamic_MVP);
	m_shader_DynamicTest->setuniform1i("u_screenTexture", 0);//把缓冲帧得到的贴图绑定到某个平面上
	m_shader_DynamicTest->setuniform1f("u_alpha", m_alpha);
	m_block_Dynamic->DrawCall();
}

void DynamicTextureBuffer::renderImguiContext()
{
	ImGui::SliderFloat("alpha", &m_alpha, 0.1, 1.0, "%.2f");
	ImGui::SliderFloat3("position", &m_block_position.x, -30.0f, 30.0f);
	if (ImGui::Button("reset position"))
		m_block_position = { 0.0f,0.0f,0.0f };
	ImGui::SliderFloat("rota", &m_block_rotation, -180.0f, 180.0f, "%.2f");
	ImGui::Text("camera position: x:%.2f  y:%.2f  z:%2.f", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z);
	ImGui::Text("fov: %.2f", m_fov + 45.0f);
}
