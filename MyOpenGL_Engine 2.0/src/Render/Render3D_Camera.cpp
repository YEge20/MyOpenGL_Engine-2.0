#include"Render3D_Camera.h"

Render3D_Camera::Render3D_Camera(GLFWwindow* window)
	:m_window(window),m_key_check(true),m_rotadegree(0),
	m_move(0.0f, 0.0f, 0.0f),m_light_diraction{0.0f,1.0f,0.0f},m_light_color{1.0f,1.0f,1.0f},
	m_camera_Pos(0.0f, 0.0f, 30.0f), m_camera_Fro(0.0f,0.0f,-1.0f),m_camera_Up(0.0f,1.0f,0.0f),
	moreObject{ 
		{ 1.0f,0.0f,0.0f }, { 40.0f,25.0f,40.8f }, {-33.8f,10.0f,14.4f},{45.0f,-75.0f,-18.0f},{ -57.5f,-34.0f,40.0f},
		{30.0f,-12.0f,-75.0f},{ -21.0f,-27.0f,30.0f},{46.7f,-30.0f,35.0f}
		},
	m_fire_light(0.15f)
{
	std::cout << "Runnig Render3D_Camera.cpp" << std::endl;
	m_shader = std::make_unique<Shader>("./sharder/BasicShader3D(Light_version).shader");
	m_shader->bind();
#define Databuffer3D 144
	float vertexbuffer[Databuffer3D] =
	{
		//vertex:                 normalize:
		-10.5f, -10.5f,  10.5f,      0.0f,0.0f, 1.0f,//0
		-10.5f,  10.5f,  10.5f,      0.0f,0.0f, 1.0f,//1
		 10.5f, -10.5f,  10.5f,      0.0f,0.0f, 1.0f,//2
		 10.5f,  10.5f,  10.5f,      0.0f,0.0f, 1.0f,//3

		-10.5f, -10.5f, -10.5f,      0.0f,0.0f,-1.0f,//4
		-10.5f,  10.5f, -10.5f,      0.0f,0.0f,-1.0f,//5
		 10.5f, -10.5f, -10.5f,      0.0f,0.0f,-1.0f,//6
		 10.5f,  10.5f, -10.5f,      0.0f,0.0f,-1.0f,//7

		 10.5f, -10.5f,  10.5f,      1.0f,0.0f,0.0f,//8
		 10.5f,  10.5f,  10.5f,      1.0f,0.0f,0.0f,//9
		 10.5f, -10.5f, -10.5f,      1.0f,0.0f,0.0f,//10
		 10.5f,  10.5f, -10.5f,      1.0f,0.0f,0.0f,//11

		-10.5f, -10.5f,  10.5f,     -1.0f,0.0f,0.0f,//12
		-10.5f,  10.5f,  10.5f,     -1.0f,0.0f,0.0f,//13
		-10.5f, -10.5f, -10.5f,     -1.0f,0.0f,0.0f,//14
		-10.5f,  10.5f, -10.5f,     -1.0f,0.0f,0.0f,//15

		-10.5f,  10.5f,  10.5f,      0.0f,1.0f,0.0f,//16
		-10.5f,  10.5f, -10.5f,      0.0f,1.0f,0.0f,//17
		 10.5f,  10.5f,  10.5f,      0.0f,1.0f,0.0f,//18
		 10.5f,  10.5f, -10.5f,      0.0f,1.0f,0.0f,//19

		-10.5f, -10.5f,  10.5f,      0.0f,-1.0f,0.0f,//20
		-10.5f, -10.5f, -10.5f,      0.0f,-1.0f,0.0f,//21
		 10.5f, -10.5f,  10.5f,      0.0f,-1.0f,0.0f,//22
		 10.5f, -10.5f, -10.5f,      0.0f,-1.0f,0.0f //23
	};
#define countOfindex 2
	int DatabufferSize[countOfindex] =
	{
		//vertex:    normalize:
		3,                  3
	};
#define LayoutNum 36
	unsigned int Layout[LayoutNum] =
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
	m_vertexbufferlayout = std::make_unique<vertexbufferlayout>(vertexbuffer,Layout,Databuffer3D,LayoutNum);
	m_vertexbufferlayout->AttribPointer(countOfindex,DatabufferSize,6);
	//材质设定：
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	std::vector<std::string> face =
	{
		"./texture/furnace/furnace_side.png",
		"./texture/furnace/furnace_side.png",
		"./texture/furnace/furnace_top.png",
		"./texture/furnace/furnace_top.png",
		"./texture/furnace/furnace_front.png",
		"./texture/furnace/furnace_side.png"
	};
	std::vector<std::string> face2 =
	{
		"./texture/furnace/furnace_side.png",
		"./texture/furnace/furnace_side.png",
		"./texture/furnace/furnace_top.png",
		"./texture/furnace/furnace_top.png",
		"./texture/furnace/furnace_front_on.png",
		"./texture/furnace/furnace_side.png"
	};

	m_textureblock = std::make_unique<TextureBlock8>(true, false);
	m_textureblock->importtexture(face,0);
	m_textureblock->importtexture(face2,1);
	m_textureblock->bind(0);


	//3D渲染必须启动深度测试否侧渲染过程不正确：
	glEnable(GL_DEPTH_TEST);

	m_control_Camera = std::make_unique<KeyControlFor3D>(m_window,true,true);
}

void Render3D_Camera::renderContext()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (glfwGetKey(m_window, GLFW_KEY_C) == GLFW_PRESS && m_key_check == true)
	{
		std::cout << "[C Press]:fire on" << std::endl;
		m_textureblock->bind(1);
		m_key_check = false;
	}
	if (m_key_check == true && m_fire_light > 0.15f)//降温
		m_fire_light -= 0.002f;
	if (glfwGetKey(m_window, GLFW_KEY_X) == GLFW_PRESS && m_key_check == false)
	{
		std::cout << "[X Press]:fire off" << std::endl;
		m_textureblock->bind(0);
		m_key_check = true;
	}
	if (m_key_check == false)//升温
	{
		if (m_fire_light < 1.2f)
			m_fire_light += 0.002f;
		else
			m_fire_light += 0.002f * sin(4.0f * glfwGetTime());
	}

	m_fov = m_control_Camera->MousescrollFunction();
	m_project = glm::perspective(glm::radians(45.0f + m_fov), (float)960 / (float)640, 0.1f, 450.0f);
	glm::mat4 CameraView = m_control_Camera->CameraMove(&m_camera_Pos, &m_camera_Fro, &m_camera_Up, 1.5f);
	m_shader->setuniformVEC3("u_light.color", m_light_color.x, m_light_color.y, m_light_color.z);
	m_shader->setuniformVEC3("u_fire", m_fire_light, m_fire_light, m_fire_light);
	m_shader->setuniformVEC3("u_view_position", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z);
	m_shader->setuniformVEC3("u_light.diraction", m_light_diraction.x, m_light_diraction.y, m_light_diraction.z);
	glm::mat4 move = glm::translate(glm::mat4(1.0f), m_move);
	for (int x = 0; x < 8; x++)
	{
		glm::mat4 moreObjectCopy = glm::translate(glm::mat4(1.0f), moreObject[x]);
		glm::mat4 rota = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotadegree * (float)glfwGetTime()), moreObject[x]);
		glm::mat4 model = move * moreObjectCopy * rota;
		glm::mat4 MVP1 = m_project * CameraView * model;
		m_shader->setuniformMat4f("u_MVP", MVP1);
		m_shader->setuniformMat4f("u_model", model);
		m_shader->setuniformMat4f("u_rota",rota);
		glDrawElements(GL_TRIANGLES, LayoutNum, GL_UNSIGNED_INT, nullptr);
	}
}

void Render3D_Camera::renderImguiContext()
{
	ImGui::SliderFloat3("X Y Z", &m_move.x, -20.0f, 20.0f);
	if (ImGui::Button("reset position"))
		m_move = { 0.0f, 0.0f, 0.0f };
	ImGui::SliderFloat("degree", &m_rotadegree, -90.0f, 90.0f);
	ImGui::Text("camera position: x:%.2f  y:%.2f  z:%2.f", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("fov: %.2f,    light: %.4f", m_fov + 45.0f,m_fire_light * 100);
}
