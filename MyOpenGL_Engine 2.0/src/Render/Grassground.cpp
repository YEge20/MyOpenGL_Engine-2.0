#include"Grassground.h"

GrassGround::GrassGround(GLFWwindow* window)
	:m_window(window),m_rotaspeed(0.0f),
	m_move(0.0f, 0.0f, 0.0f), m_light_diraction{ 0.0f,1.0f,0.0f }, m_light_color{ 1.0f,1.0f,1.0f },
	m_camera_Pos(0.0f, -30.0f, 250.0f), m_camera_Fro(0.0f, 0.0f, -1.0f), m_camera_Up(0.0f, 1.0f, 0.0f),
	m_moreObject{
		{ 1.0f,0.0f,0.0f }, { 40.0f,25.0f,40.8f }, {-33.8f,10.0f,14.4f},{45.0f,-75.0f,-18.0f},{ -57.5f,-34.0f,40.0f},
		{30.0f,-12.0f,-75.0f},{ -21.0f,-27.0f,30.0f},{46.7f,-30.0f,35.0f},{-80.0f,20.5f,68.0f},{-90.0f,-40.0f,-36.5f},{-88.0f,29.4f,-48.0f},{-87.2f,-64.4f,57.7f},
		{80.0f,20.5f,58.0f},{90.0f,-40.0f,-36.5f},{88.0f,29.4f,-48.0f},{87.2f,-44.4f,57.7f}
	},
	m_moreObject_2{
		{0.0f,0.0f,0.0f},{10.2f,0.0f,10.2f},{15.8f,0.0f,-24.1f},{-20.1f,0.0f,21.5f},{-17.8f,0.0f,-10.9f},
		{21.8f,0.0f,1.4f},{1.6f,0.0f,15.7f},{-24.4f,0.0f,-2.3f},{-6.7f,0.0f,-28.8f},{32.2f,0.0f,36.6f}
	},
	m_moreObject_3{
		{4.5f,0.0f,-3.8f},{-8.8f,0.0f,-6.7f},{5.6f,0.0f,10.5f},{-22.2f,0.0f,24.7f},{18.8f,0.0f,-15.7f},
		{7.7f,0.0f,-6.7f},{14.0f,0.0f,26.6f},{19.5f,0.0f,30.6f},{34.5f,0.0f,20.1f},{-33.3f,0.0f,-17.7f}
	},
	m_grass_move(0.0f,-120.0f,0.0f),m_red(0),m_grass_2_move(0.0f,-112.0f,0.0f)
{
	std::cout << "Running Grassground.cpp" << std::endl;
	m_shader = std::make_unique<Shader>("./sharder/mix/BasicShader3D(Light_version)2.shader");
	m_shader_1 = std::make_unique<Shader1>("./sharder/mix/GrassGround.shader");
	m_shader_2 = std::make_unique<shader3>("./sharder/mix/Grass.shader");
#define Databuffer3D 192
	float vertexbuffer[Databuffer3D] =
	{
		//vertex:                 normalize:            texcoord:
		-5.5f, -5.5f,  5.5f,      0.0f,0.0f, 1.0f,      0.0f,0.0f,//0
		-5.5f,  5.5f,  5.5f,      0.0f,0.0f, 1.0f,      0.0f,1.0f,//1
		 5.5f, -5.5f,  5.5f,      0.0f,0.0f, 1.0f,      1.0f,0.0f,//2
		 5.5f,  5.5f,  5.5f,      0.0f,0.0f, 1.0f,      1.0f,1.0f,//3

		-5.5f, -5.5f, -5.5f,      0.0f,0.0f,-1.0f,      0.0f,0.0f,//4
		-5.5f,  5.5f, -5.5f,      0.0f,0.0f,-1.0f,      0.0f,1.0f,//5
		 5.5f, -5.5f, -5.5f,      0.0f,0.0f,-1.0f,      1.0f,0.0f,//6
		 5.5f,  5.5f, -5.5f,      0.0f,0.0f,-1.0f,      1.0f,1.0f,//7

		 5.5f, -5.5f,  5.5f,      1.0f,0.0f,0.0f,       0.0f,0.0f,//8
		 5.5f,  5.5f,  5.5f,      1.0f,0.0f,0.0f,       0.0f,1.0f,//9
		 5.5f, -5.5f, -5.5f,      1.0f,0.0f,0.0f,       1.0f,0.0f,//10
		 5.5f,  5.5f, -5.5f,      1.0f,0.0f,0.0f,       1.0f,1.0f,//11

		-5.5f, -5.5f,  5.5f,     -1.0f,0.0f,0.0f,       0.0f,0.0f,//12
		-5.5f,  5.5f,  5.5f,     -1.0f,0.0f,0.0f,       0.0f,1.0f,//13
		-5.5f, -5.5f, -5.5f,     -1.0f,0.0f,0.0f,       1.0f,0.0f,//14
		-5.5f,  5.5f, -5.5f,     -1.0f,0.0f,0.0f,       1.0f,1.0f,//15

		-5.5f,  5.5f,  5.5f,      0.0f,1.0f,0.0f,       0.0f,1.0f,//16
		-5.5f,  5.5f, -5.5f,      0.0f,1.0f,0.0f,       0.0f,0.0f,//17
		 5.5f,  5.5f,  5.5f,      0.0f,1.0f,0.0f,       1.0f,1.0f,//18
		 5.5f,  5.5f, -5.5f,      0.0f,1.0f,0.0f,       1.0f,0.0f,//19

		-5.5f, -5.5f,  5.5f,      0.0f,-1.0f,0.0f,      0.0f,1.0f,//20
		-5.5f, -5.5f, -5.5f,      0.0f,-1.0f,0.0f,      0.0f,0.0f,//21
		 5.5f, -5.5f,  5.5f,      0.0f,-1.0f,0.0f,      1.0f,1.0f,//22
		 5.5f, -5.5f, -5.5f,      0.0f,-1.0f,0.0f,      1.0f,0.0f //23
	};
#define countOfindex 3
	int DatabufferSize[countOfindex] =
	{
		//vertex:    normalize:        texcoord:
		3,                  3,          2
	};
#define LayoutNum0 36
	unsigned int Layout[LayoutNum0] =
	{
		0,1,2,
		2,3,1,

		4,5,6,
		5,6,7,

		8,9,10,
		9,10,11,

		12,13,14,
		13,14,15,

		16,17,18,
		17,18,19,

		20,21,22,
		21,22,23
	};
	//顶点的设置：
	m_vertexbufferlayout = std::make_unique<vertexbufferlayout>(vertexbuffer, Layout, Databuffer3D, LayoutNum0);
	m_vertexbufferlayout->AttribPointer(countOfindex, DatabufferSize, 8);

#define grassgroundBuffer 216
	float grassground[grassgroundBuffer] =
	{   //vertex                   texcoord       color
		-40.0f, -5.5f,  40.0f,     0.0f,0.0f,     0.07f,0.0f,0.01f,1.0f,//0
		-40.0f,  5.5f,  40.0f,     0.0f,1.0f,     0.07f,0.0f,0.01f,1.0f,//1
		 40.0f, -5.5f,  40.0f,     1.0f,0.0f,     0.07f,0.0f,0.01f,1.0f,//2
		 40.0f,  5.5f,  40.0f,     1.0f,1.0f,     0.07f,0.0f,0.01f,1.0f,//3

		-40.0f, -5.5f, -40.0f,     0.0f,0.0f,     0.07f,0.0f,0.01f,1.0f,//4
		-40.0f,  5.5f, -40.0f,     0.0f,1.0f,     0.07f,0.0f,0.01f,1.0f,//5
		 40.0f, -5.5f, -40.0f,     1.0f,0.0f,     0.07f,0.0f,0.01f,1.0f,//6
		 40.0f,  5.5f, -40.0f,     1.0f,1.0f,     0.07f,0.0f,0.01f,1.0f,//7

		 40.0f, -5.5f,  40.0f,     0.0f,0.0f,     0.07f,0.0f,0.01f,1.0f,//8
		 40.0f,  5.5f,  40.0f,     0.0f,1.0f,     0.07f,0.0f,0.01f,1.0f,//9
		 40.0f, -5.5f, -40.0f,     1.0f,0.0f,     0.07f,0.0f,0.01f,1.0f,//10
		 40.0f,  5.5f, -40.0f,     1.0f,1.0f,     0.07f,0.0f,0.01f,1.0f,//11

		-40.0f, -5.5f,  40.0f,     0.0f,0.0f,     0.07f,0.0f,0.01f,1.0f,//12
		-40.0f,  5.5f,  40.0f,     0.0f,1.0f,     0.07f,0.0f,0.01f,1.0f,//13
		-40.0f, -5.5f, -40.0f,     1.0f,0.0f,     0.07f,0.0f,0.01f,1.0f,//14
		-40.0f,  5.5f, -40.0f,     1.0f,1.0f,     0.07f,0.0f,0.01f,1.0f,//15

		-40.0f,  5.5f,  40.0f,     0.0f,0.0f,     0.07f,0.0f,0.01f,1.0f,//16
		-40.0f,  5.5f, -40.0f,     0.0f,1.0f,     0.07f,0.0f,0.01f,1.0f,//17
		 40.0f,  5.5f,  40.0f,     1.0f,0.0f,     0.07f,0.0f,0.01f,1.0f,//18
		 40.0f,  5.5f, -40.0f,     1.0f,1.0f,     0.07f,0.0f,0.01f,1.0f,//19
		
		-40.0f, -5.5f,  40.0f,     0.0f,0.0f,     0.07f,0.0f,0.01f,1.0f,//20
		-40.0f, -5.5f, -40.0f,     0.0f,1.0f,     0.07f,0.0f,0.01f,1.0f,//21
		 40.0f, -5.5f,  40.0f,     1.0f,0.0f,     0.07f,0.0f,0.01f,1.0f,//22
		 40.0f, -5.5f, -40.0f,     1.0f,1.0f,     0.07f,0.0f,0.01f,1.0f //23
	};
#define grassgroundCountIndex 3
	int grassgroundIndex[grassgroundCountIndex] =
	{
		3,2,4
	};
#define grassgroundLayoutNum 36
	unsigned int grassgroundLyaout[grassgroundLayoutNum] =
	{
		0,1,2,
		1,2,3,

		4,5,6,
		5,6,7,

		8,9,10,
		9,10,11,

		12,13,14,
		13,14,15,

		16,17,18,
		17,18,19,

		20,21,22,
		21,22,23
	};
	m_vertexbufferlayout_1 = std::make_unique<vertexbufferLayout1>(grassground, grassgroundLyaout, grassgroundBuffer, grassgroundLayoutNum);
	m_vertexbufferlayout_1->AttribPointer(grassgroundCountIndex, grassgroundIndex, 9);

#define grassBuffer 80
	float grass[grassBuffer] =
	{
		//vertex              texcoord      color                     top_button
		 2.5f, 2.5f, 2.5f,    1.0f,1.0f,    0.25f,0.5f,0.0f,1.0f,      1.0f,//0
		-2.5f, 2.5f,-2.5f,    0.0f,1.0f,    0.25f,0.5f,0.0f,1.0f,      1.0f,//1
		 2.5f,-2.5f, 2.5f,    1.0f,0.0f,    0.20f,0.5f,0.05f,1.0f,     0.0f,//2
		-2.5f,-2.5f,-2.5f,    0.0f,0.0f,    0.20f,0.5f,0.05f,1.0f,     0.0f,//3

		-2.5f, 2.5f, 2.5f,    0.0f,1.0f,    0.25f,0.5f,0.0f,1.0f,      1.0f,//4
		 2.5f, 2.5f,-2.5f,    1.0f,1.0f,    0.25f,0.5f,0.0f,1.0f,      1.0f,//5
		-2.5f,-2.5f, 2.5f,    0.0f,0.0f,    0.20f,0.5f,0.05f,1.0f,     0.0f,//6
		 2.5f,-2.5f,-2.5f,    1.0f,0.0f,    0.20f,0.5f,0.05f,1.0f,     0.0f//7
	};
#define grassCountIndex 4
	int grassIndex[grassCountIndex] =
	{
		3,2,4,1
	};
#define grassLayoutNum 12
	unsigned int grassLayout[grassLayoutNum] =
	{
		0,1,2,
		1,2,3,

		4,5,6,
		5,6,7
	};
	m_vertexbufferlayout_2 = std::make_unique<vertexbufferLayout2>(grass, grassLayout, grassBuffer, grassLayoutNum);
	m_vertexbufferlayout_2->AttribPointer(grassCountIndex, grassIndex, 10);

	//材质设定：
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_texture32 = std::make_unique<texture32>(false);
	m_texture32->importTexture("./texture/ground/grass001.png", 0);

	m_texture32->importTexture("./texture/ground/dirt.png", 1);
	m_texture32->importTexture("./texture/ground/grass.png", 2);

	m_texture32->importTexture("./texture/ground/dandelion.png", 3);
	m_texture32->importTexture("./texture/ground/lily_of_the_valley.png", 4);
	m_texture32->importTexture("./texture/ground/pitcher_crop_top_stage_4.png", 5);
	m_texture32->importTexture("./texture/ground/poppy.png", 6);
	m_texture32->importTexture("./texture/ground/torchflower.png", 7);

	m_texture32->importTexture("./texture/mental_stone/iron_ore_NEW.png", 8);
	m_texture32->importTexture("./texture/mental_stone/diamond_ore_NEW.png", 9);
	m_texture32->importTexture("./texture/mental_stone/emerald_ore_NEW.png", 10);
	m_texture32->importTexture("./texture/mental_stone/gold_ore_NEW.png", 11);
	m_texture32->importTexture("./texture/mental_stone/lapis_ore_NEW.png", 12);
	m_texture32->importTexture("./texture/mental_stone/redstone_ore_NEW.png", 13);

	m_texture32->importTexture("./texture/mental_stone/iron_ore_PBR_NEW.png", 14);
	m_texture32->importTexture("./texture/mental_stone/diamond_ore_PBR_NEW.png", 15);
	m_texture32->importTexture("./texture/mental_stone/emerald_ore_PBR_NEW.png", 16);
	m_texture32->importTexture("./texture/mental_stone/gold_ore_PBR_NEW.png", 17);
	m_texture32->importTexture("./texture/mental_stone/lapis_ore_PBR_NEW.png", 18);
	m_texture32->importTexture("./texture/mental_stone/redstone_ore_PBR_NEW.png", 19);

	m_texture32->importTexture("./texture/mental_stone/iron_ore_NEW_REFLECT_PBR.png", 20);
	m_texture32->importTexture("./texture/mental_stone/diamond_ore_NEW_REFLECT_PBR.png", 21);
	m_texture32->importTexture("./texture/mental_stone/emerald_ore_NEW_REFLECT_PBR.png", 22);
	m_texture32->importTexture("./texture/mental_stone/gold_ore_NEW_REFLECT_PBR.png", 23);
	m_texture32->importTexture("./texture/mental_stone/lapis_ore_NEW_REFLECT_PBR.png", 24);
	m_texture32->importTexture("./texture/mental_stone/redstone_ore_NEW_REFLECT_PBR.png", 25);

	m_texture32->bind(0, 0);
	m_texture32->bind(1, 1);
	//3D渲染必须启动深度测试否侧渲染过程不正确：
	glEnable(GL_DEPTH_TEST);

	m_control_Camera = std::make_unique<KeyControlFor3D>(m_window, true, true);
}

void GrassGround::renderContext()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader->bind();
	glBindVertexArray(m_vertexbufferlayout->VAOid());
	m_fov = m_control_Camera->MousescrollFunction();
	m_project = glm::perspective(glm::radians(45.0f + m_fov), (float)960 / (float)640, 0.1f, 450.0f);
	glm::mat4 CameraView = m_control_Camera->CameraMove(&m_camera_Pos, &m_camera_Fro, &m_camera_Up, 0.8f);
	m_shader->setuniformVEC3("u_light.color", m_light_color.x, m_light_color.y, m_light_color.z);
	m_shader->setuniformVEC3("u_view_position", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z);
	m_shader->setuniformVEC3("u_light.diraction", m_light_diraction.x, m_light_diraction.y, m_light_diraction.z);
	glm::mat4 move = glm::translate(glm::mat4(1.0f), m_move);
	if (m_speed_add < m_rotaspeed)
		m_speed_add += 0.01f;
	if (m_speed_add > m_rotaspeed)
		m_speed_add -= 0.01f;
	if (m_speed_add == m_rotaspeed)
		m_speed_add = 0.01f + m_rotaspeed;
	m_rad += m_speed_add;
	if (m_rad > 360.0f)
		m_rad = 0.0f;
	for (int x = 0; x < 16; x++)
	{
		glm::mat4 moreObjectCopy = glm::translate(glm::mat4(1.0f), m_moreObject[x]);
		glm::mat4 rota = glm::rotate(glm::mat4(1.0f), glm::radians(m_rad), m_moreObject[x]);
		glm::mat4 model = move * moreObjectCopy * rota;
		glm::mat4 MVP1 = m_project * CameraView * model;
		m_shader->setuniformMat4f("u_MVP", MVP1);
		m_shader->setuniform1i("u_sampler", 3);
		m_shader->setuniform1i("u_sampler_light_ore_pbr", 4);
		m_shader->setuniform1i("u_sampler_reflect_pbr", 5);
		m_texture32->bind(3, 8 + x % 6);
		m_texture32->bind(4, 14 + x % 6);
		m_texture32->bind(5, 20 + x % 6);
		m_shader->setuniformMat4f("u_model", model);
		m_shader->setuniformMat4f("u_rota", rota);
		glDrawElements(GL_TRIANGLES, LayoutNum0, GL_UNSIGNED_INT, nullptr);
	}
//渲染草地：
	m_shader_1->bind();
	glBindVertexArray(m_vertexbufferlayout_1->VAOid());
	glm::mat4 grassMove = glm::translate(glm::mat4(1.0f), m_grass_move);
	glm::mat4 MVP2 = m_project * CameraView * grassMove;
	m_shader_1->setuniformMat4f("u_MVP", MVP2);
	m_shader_1->setuniform1i("u_texture0", 0);
	m_shader_1->setuniform1i("u_texture1", 1);
	m_shader_1->setuniform1f("u_red", m_red);
	glDrawElements(GL_TRIANGLES, grassgroundLayoutNum, GL_UNSIGNED_INT, nullptr);
//渲染花草：
	m_shader_2->bind();
	glBindVertexArray(m_vertexbufferlayout_2->VAOid());
	glm::mat4 grass_2Move = glm::translate(glm::mat4(1.0f),m_grass_2_move);
	//渲染草：
	for (int i = 0; i < 10; i++)
	{
		glm::mat4 moregrass = glm::translate(glm::mat4(1.0f), m_moreObject_2[i]);
		glm::mat4 model2 = moregrass * grass_2Move;
		glm::mat4 MVP3 = m_project * CameraView * model2;
		glm::mat4 wave0 = glm::translate(glm::mat4(1.0f), glm::vec3(sin(glfwGetTime() + m_moreObject_2[i].x * m_moreObject_2[i].z), 0.0f, cos(glfwGetTime() + m_moreObject_2[i].x * m_moreObject_2[i].z)));
		m_shader_2->setuniformMat4f("u_MVP", MVP3);
		m_shader_2->setuniformMat4f("u_wave", wave0);
		m_shader_2->setuniform1f("u_red", m_red);
		m_shader_2->setuniform1f("u_grass_flower", 1.0f);
		m_texture32->bind(2, 2);
		m_shader_2->setuniform1i("u_texture0", 2);
		glDrawElements(GL_TRIANGLES, grassLayoutNum, GL_UNSIGNED_INT, nullptr);
	}
	//渲染花：
	for (int i = 0; i < 10; i++)
	{
		glm::mat4 moreflower = glm::translate(glm::mat4(1.0f),m_moreObject_3[i]);
		glm::mat4 model3 = moreflower * grass_2Move;
		glm::mat4 MVP4 = m_project * CameraView * model3;
		glm::mat4 wave1 = glm::translate(glm::mat4(1.0f), glm::vec3(sin(glfwGetTime() + m_moreObject_3[i].x * m_moreObject_3[i].z), 0.0f, cos(glfwGetTime() + m_moreObject_3[i].x * m_moreObject_3[i].z)));
		m_shader_2->setuniformMat4f("u_MVP", MVP4);
		m_shader_2->setuniformMat4f("u_wave",wave1);
		m_shader_2->setuniform1f("u_grass_flower", 0.0f);
		m_texture32->bind(2, 3 + i % 5);
		glDrawElements(GL_TRIANGLES, grassLayoutNum, GL_UNSIGNED_INT, nullptr);
	}
}

void GrassGround::renderImguiContext()
{
	ImGui::SliderFloat3("X Y Z", &m_move.x, -20.0f, 20.0f);
	if (ImGui::Button("reset position"))
		m_move = { 0.0f, 0.0f, 0.0f };
	ImGui::SliderFloat("red", &m_red, 0.0f, 1.0f);
	ImGui::SliderFloat("speed+", &m_rotaspeed, 0.0f, 5.0f);
	ImGui::Text("camera position: x:%.2f  y:%.2f  z:%2.f   fov:%.2f", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z, 45.0f + m_fov);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("rota speed: %.2f , rad:%.2f", m_speed_add, m_rad);
}
