#include"PointLight_ShadowCubemap.h"

Pointlight_ShadowCubemap::Pointlight_ShadowCubemap(GLFWwindow* window)
	:m_window(window)
{
	std::cout << "Running Pointlight_ShadowCubemap.cpp" << std::endl;

	m_sky_shader.reset(new Shader("./shader/Pointlight_ShadowCubemap/Sky.shader"));
	m_sky.reset(new DrawBlock(1.0f, 1.0f, 1.0f));
	std::vector<std::string> face = {
		"./texture/skybox/right.jpg",
		"./texture/skybox/left.jpg",
		"./texture/skybox/top.jpg",
		"./texture/skybox/bottom.jpg",
		"./texture/skybox/front.jpg",
		"./texture/skybox/back.jpg"
	};
	m_SkyTexture.reset(new TextureBlock(face, true));

	m_glass_shader.reset(new Shader("./shader/Pointlight_ShadowCubemap/Reflect.shader"));
	m_glass_block.reset(new DrawBlock(5.0f, 5.0f, 5.0f));

	m_dynamic_cube.reset(new DynamicEnvironmentCube(1024, true, m_dynamic_Pos));
	m_dynamic_cube_model.reset(new DrawBlock(2.0f, 2.0f, 2.0f));

	//材质设定：
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//3D渲染必须启动深度测试否侧渲染过程不正确：
	glEnable(GL_DEPTH_TEST);

	m_camera_controler.reset(new KeyControlFor3D(m_window, true, true));
}

void Pointlight_ShadowCubemap::renderContext(float timestep, float milltimestep)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	m_fov = m_camera_controler->MousescrollFunction();
	m_projeect = glm::perspective(glm::radians(45.0f + m_fov), (float)1200 / (float)800, 0.1f, 800.0f);
	m_Camera = m_camera_controler->CameraMove(&m_camera_Pos, &m_camera_Fro, &m_camera_Up, 4.5f * timestep);

	//动态立方贴图捕获视角的场景
	m_dynamic_cube->Modifie_position(m_dynamic_Pos);
	for (int x = 0; x < 6; x++)
	{
		m_dynamic_cube->bind(x);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 dynamicCube_look = m_dynamic_cube->Dynamic_Cam(x);
		glm::mat4 dynamicCube_project = m_dynamic_cube->Dynamic_Project();
		m_scene_1(dynamicCube_project, dynamicCube_look, m_dynamic_Pos);
	}
	m_dynamic_cube->UnBind();
	glViewport(0, 0, 1200, 800);

	//正常渲染场景：
	m_scene_1(m_projeect, m_Camera, m_camera_Pos);
	m_test_scene(m_projeect, m_Camera, m_camera_Pos);
}

void Pointlight_ShadowCubemap::renderImguiContext()
{
	ImGui::Text("Camera_Pos: x=%.3f y=%.3f z=%.3f", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z);
	ImGui::Text("Camera_fov: %.2f", 45.0f + m_fov);
	ImGui::SliderFloat("rotate", &m_glass_rota, -90.0f, 90.0f, "%.1f");
	ImGui::SliderFloat3("dynamic cube position",&m_dynamic_Pos.x,-8.0f,8.0f,"%.1f");
}

void Pointlight_ShadowCubemap::m_scene_1(glm::mat4 project, glm::mat4 Camera, glm::vec3 Cam_Pos)
{
	for (int x = 0; x < 4; x++)
	{
		m_glass_shader->bind();
		glm::mat4 glass_rotate = glm::rotate(glm::mat4(1.0f), glm::radians(m_glass_rota), m_glass_Pos[x]);
		glm::mat4 glass_Pos = glm::translate(glm::mat4(1.0f), m_glass_Pos[x]);
		glm::mat4 glass_model = glass_Pos * glass_rotate;
		glm::mat4 glass_MVP = project * Camera * glass_model;
		m_SkyTexture->bind();
		m_glass_shader->setuniformMat4f("u_MVP", glass_MVP);
		m_glass_shader->setuniformMat4f("u_model", glass_model);
		m_glass_shader->setuniformMat4f("u_rota", glass_rotate);
		m_glass_shader->setuniformVEC3("u_Cam_Pos", Cam_Pos.x, Cam_Pos.y, Cam_Pos.z);
		m_glass_block->DrawCall();
	}

	glDepthFunc(GL_LEQUAL);
	m_sky_shader->bind();
	glm::mat4 newskyCamera = glm::mat4(glm::mat3(Camera));//移除平移改变
	glm::mat4 sky_MVP = project * newskyCamera;
	m_sky_shader->setuniformMat4f("u_MVP", sky_MVP);
	m_SkyTexture->bind();
	m_sky->DrawCall();
	glDepthFunc(GL_LESS);
}

void Pointlight_ShadowCubemap::m_test_scene(glm::mat4 project, glm::mat4 Camera, glm::vec3 Cam_Pos)
{
	m_glass_shader->bind();
	glm::mat4 dynamic_Pos = glm::translate(glm::mat4(1.0f), m_dynamic_Pos);
	glm::mat4 dynamic_rotate = glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 dynamic_model = dynamic_Pos * dynamic_rotate;
	glm::mat4 dynamic_MVP = project * Camera * dynamic_model;
	m_dynamic_cube->UseDynamicCubeTexture();
	m_glass_shader->setuniformMat4f("u_MVP", dynamic_MVP);
	m_glass_shader->setuniformMat4f("u_model", dynamic_model);
	m_glass_shader->setuniformMat4f("u_rota", dynamic_rotate);
	m_glass_shader->setuniformVEC3("u_Cam_Pos", Cam_Pos.x, Cam_Pos.y, Cam_Pos.z);
	m_dynamic_cube_model->DrawCall();
}
