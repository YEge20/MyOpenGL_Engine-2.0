#include"light.h"

light::light(GLFWwindow* window)
	:m_window(window),
	m_move(0.0f, 0.0f, 0.0f), m_Plight_dis(1.0f),m_object_dis(1.0f),
	m_location{ {0.0f,0.0f,0.0f},{60.0f,60.0f,60.0f},{-60.0f,60.0f,60.0f},{60.0f,-60.0f,60.0f},{-60.0f,-60.0f,60.0f},{60.0f,60.0f,-60.0f},{-60.0f,60.0f,-60.0f},{60.0f,-60.0f,-60.0f},{-60.0f,-60.0f,-60.0f} },
	m_move1{ {-70.0f,0.0f,0.0f},{70.0f,0.0f,0.0f},{0.0f,-70.0f,0.0f},{0.0f,70.0f,0.0f},{0.0f,0.0f,-70.0f},{0.0f,0.0f,70.0f} },
	m_lightcolor{ 1.0f,1.0f,1.0f }, m_skyboxLight(0.0f),
	m_camera_Pos(0.0f, 41.0f, 25.0f), m_camera_Fro(0.0f, 0.0f, 1.0f), m_camera_Up(0.0f, 1.0f, 0.0f)
{
	std::cout << "Running light.cpp" << std::endl;
	m_shader = std::make_unique<Shader>("./sharder/light/BasicShader3D_object.shader");
	m_shader1 = std::make_unique<Shader1>("./sharder/light/BasicShader3D_light_object.shader");
	m_shaderSkybox = std::make_unique<shader3>("./sharder/light/SkyboxShader.shader");
	//VAO 0的设置：
#define Databuffer3D 192
	float vertexbuffer[Databuffer3D] =
	{
		//      vertex:               texture:          normal:
		-20.5f, -20.5f,  20.5f,      0.0f,0.0f,     0.0f,0.0f, 1.0f,//0
		-20.5f,  20.5f,  20.5f,      0.0f,1.0f,     0.0f,0.0f, 1.0f,//1
		 20.5f, -20.5f,  20.5f,      1.0f,0.0f,     0.0f,0.0f, 1.0f,//2
		 20.5f,  20.5f,  20.5f,      1.0f,1.0f,     0.0f,0.0f, 1.0f,//3

		-20.5f, -20.5f, -20.5f,      0.0f,0.0f,     0.0f,0.0f,-1.0f,//4
		-20.5f,  20.5f, -20.5f,      0.0f,1.0f,     0.0f,0.0f,-1.0f,//5
		 20.5f, -20.5f, -20.5f,      1.0f,0.0f,     0.0f,0.0f,-1.0f,//6
		 20.5f,  20.5f, -20.5f,      1.0f,1.0f,     0.0f,0.0f,-1.0f,//7

		 20.5f, -20.5f,  20.5f,      0.0f,0.0f,     1.0f,0.0f, 0.0f,//8
		 20.5f,  20.5f,  20.5f,      0.0f,1.0f,     1.0f,0.0f, 0.0f,//9
		 20.5f, -20.5f, -20.5f,      1.0f,0.0f,     1.0f,0.0f, 0.0f,//10
		 20.5f,  20.5f, -20.5f,      1.0f,1.0f,     1.0f,0.0f, 0.0f,//11

		-20.5f, -20.5f,  20.5f,      0.0f,0.0f,    -1.0f,0.0f, 0.0f,//12
		-20.5f,  20.5f,  20.5f,      0.0f,1.0f,    -1.0f,0.0f, 0.0f,//13
		-20.5f, -20.5f, -20.5f,      1.0f,0.0f,    -1.0f,0.0f, 0.0f,//14
		-20.5f,  20.5f, -20.5f,      1.0f,1.0f,    -1.0f,0.0f, 0.0f,//15

		-20.5f,  20.5f,  20.5f,      0.0f,0.0f,     0.0f,1.0f, 0.0f,//16
		-20.5f,  20.5f, -20.5f,      0.0f,1.0f,     0.0f,1.0f, 0.0f,//17
		 20.5f,  20.5f,  20.5f,      1.0f,0.0f,     0.0f,1.0f, 0.0f,//18
		 20.5f,  20.5f, -20.5f,      1.0f,1.0f,     0.0f,1.0f, 0.0f,//19

		-20.5f, -20.5f,  20.5f,      0.0f,0.0f,     0.0f,-1.0f,0.0f,//20
		-20.5f, -20.5f, -20.5f,      0.0f,1.0f,     0.0f,-1.0f,0.0f,//21
		 20.5f, -20.5f,  20.5f,      1.0f,0.0f,     0.0f,-1.0f,0.0f,//22
		 20.5f, -20.5f, -20.5f,      1.0f,1.0f,     0.0f,-1.0f,0.0f //23
	};
#define countOfindex 3
	int DatabufferSize[countOfindex] =
	{
		//vertex:        texture:        normal:
		3,                2,              3
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
	m_vertexbufferlayout = std::make_unique<vertexbufferlayout>(vertexbuffer, Layout, Databuffer3D, LayoutNum);
	m_vertexbufferlayout->AttribPointer(countOfindex, DatabufferSize, 8);
	//VAO 1 的设置：
#define Databuffer3D_1 72
	float vertexbuffer1[Databuffer3D_1] =
	{
		//vertex:                
		-4.5f, -4.5f,  4.5f,   //0
		-4.5f,  4.5f,  4.5f,   //1
		 4.5f, -4.5f,  4.5f,   //2
		 4.5f,  4.5f,  4.5f,   //3

		-4.5f, -4.5f, -4.5f,   //4
		-4.5f,  4.5f, -4.5f,   //5
		 4.5f, -4.5f, -4.5f,   //6
		 4.5f,  4.5f, -4.5f,   //7

		 4.5f, -4.5f,  4.5f,   //8
		 4.5f,  4.5f,  4.5f,   //9
		 4.5f, -4.5f, -4.5f,   //10
		 4.5f,  4.5f, -4.5f,   //11

		-4.5f, -4.5f,  4.5f,   //12
		-4.5f,  4.5f,  4.5f,   //13
		-4.5f, -4.5f, -4.5f,   //14
		-4.5f,  4.5f, -4.5f,   //15

		-4.5f,  4.5f,  4.5f,   //16
		-4.5f,  4.5f, -4.5f,   //17
		 4.5f,  4.5f,  4.5f,   //18
		 4.5f,  4.5f, -4.5f,   //19

		-4.5f, -4.5f,  4.5f,   //20
		-4.5f, -4.5f, -4.5f,   //21
		 4.5f, -4.5f,  4.5f,   //22
		 4.5f, -4.5f, -4.5f    //23
	};
#define countOfindex_1 1
	int DatabufferSize1[countOfindex_1] =
	{
		//vertex:
		3
	};
#define LayoutNum_1 36
	unsigned int Layout1[LayoutNum_1] =
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
	m_vertexbufferlayout1 = std::make_unique<vertexbufferLayout1>(vertexbuffer1, Layout1, Databuffer3D_1, LayoutNum_1);
	m_vertexbufferlayout1->AttribPointer(countOfindex_1, DatabufferSize1, 3);
	//VAO 2(天空盒)的设置:
#define Databuffer_3D_2 72
	float skybox[Databuffer_3D_2] =
	{
		//vertex:         
		-20.0f,-20.0f, 20.0f,//0
		-20.0f, 20.0f, 20.0f,//1
		 20.0f,-20.0f, 20.0f,//2
		 20.0f, 20.0f, 20.0f,//3

		-20.0f,-20.0f,-20.0f,//4
		-20.0f, 20.0f,-20.0f,//5
		 20.0f,-20.0f,-20.0f,//6
		 20.0f, 20.0f,-20.0f,//7

		-20.0f,-20.0f,-20.0f,//8
		-20.0f,-20.0f, 20.0f,//9
		 20.0f,-20.0f,-20.0f,//10
		 20.0f,-20.0f, 20.0f,//11

		-20.0f, 20.0f,-20.0f,//12
		-20.0f, 20.0f, 20.0f,//13
		 20.0f, 20.0f,-20.0f,//14
		 20.0f, 20.0f, 20.0f,//15

		20.0f,-20.0f,-20.0f,//16
		20.0f,-20.0f, 20.0f,//17
		20.0f, 20.0f,-20.0f,//18
		20.0f, 20.0f, 20.0f,//19

		-20.0f,-20.0f,-20.0f,//20
		-20.0f,-20.0f, 20.0f,//21
		-20.0f, 20.0f,-20.0f,//22
		-20.0f, 20.0f, 20.0f //23
	};
#define countOfindex_2 1
	int index2[countOfindex_2] =
	{
		3
	};
#define skyboxLayoutNum 36
	unsigned int skyboxLayout[skyboxLayoutNum] =
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
	m_vertexbufferlayout2 = std::make_unique<vertexbufferLayout2>(skybox,skyboxLayout,Databuffer_3D_2,skyboxLayoutNum);
	m_vertexbufferlayout2->AttribPointer(countOfindex_2, index2, 3);
	//材质设定及导入：
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_texture32 = std::make_unique<texture32>(false);
	m_texture32->importTexture("./texture/mental_stone/gold_block.png", 0);
	m_texture32->importTexture("./texture/mental_stone/gold_block_PBR.png", 1);
	m_texture32->importTexture("./texture/mental_stone/cobblestone.png",2);
	m_texture32->importTexture("./texture/mental_stone/cobblestone_PBR.png",3);
	m_texture32->importTexture("./texture/mental_stone/diamond_block.png",4);
	m_texture32->importTexture("./texture/mental_stone/diamond_block_PBR.png",5);
	m_texture32->importTexture("./texture/mental_stone/emerald_block.png",6);
	m_texture32->importTexture("./texture/mental_stone/emerald_block_PBR.png",7);
	m_texture32->importTexture("./texture/mental_stone/iron_block.png",8);
	m_texture32->importTexture("./texture/mental_stone/iron_block_PBR.png",9);
	m_texture32->importTexture("./texture/mental_stone/lapis_block.png", 10);
	m_texture32->importTexture("./texture/mental_stone/lapis_block_PBR.png",11);
	m_texture32->importTexture("./texture/mental_stone/netherite_block.png",12);
	m_texture32->importTexture("./texture/mental_stone/netherite_block_PBR.png",13);
	m_texture32->importTexture("./texture/mental_stone/redstone_block.png",14);
	m_texture32->importTexture("./texture/mental_stone/redstone_block_PBR.png",15);
	m_texture32->importTexture("./texture/mental_stone/sandstone_bottom.png",16);
	m_texture32->importTexture("./texture/mental_stone/sandstone_bottom_PBR.png",17);

	std::vector<std::string> face = 
	{
		"./texture/skybox/right.jpg",
		"./texture/skybox/left.jpg",
		"./texture/skybox/bottom.jpg",
		"./texture/skybox/top.jpg",
		"./texture/skybox/front.jpg",
		"./texture/skybox/back.jpg"
	};
	m_textureblock = std::make_unique<TextureBlock>(face,false,true);
	m_textureblock->bind();
	//3D渲染必须启动深度测试否侧渲染过程不正确：
	glEnable(GL_DEPTH_TEST);

	m_control_Camera = std::make_unique<KeyControlFor3D>(m_window, true, true);
}

void light::renderContext()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_fov = m_control_Camera->MousescrollFunction();
	m_project = glm::perspective(glm::radians(45.0f + m_fov), (float)1200 / (float)800, 0.1f, 800.0f);
	glm::mat4 CameraView = m_control_Camera->CameraMove(&m_camera_Pos, &m_camera_Fro, &m_camera_Up, 1.5f);
//渲染物体：
	m_shader->bind();
	//设置观察者的位置:
	m_shader->setuniformVEC3("u_view_position", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z);
	//材料的属性设定:
	m_shader->setuniform1i("u_material.diffuse", 0);//环境光与漫反射的纹理插槽绑定
	m_shader->setuniform1i("u_material.specular", 1);//镜面反射的纹理插槽绑定
	m_shader->setuniform1f("u_material.shinness", 128.0f);//镜面反射的散射半径
	//点光源的光线距离衰减设定:
	m_shader->setuniform1f("u_PLight_ATT.C", 1.0f);
	m_shader->setuniform1f("u_PLight_ATT.L", 0.01f);
	m_shader->setuniform1f("u_PLight_ATT.Q", 0.00005f);
	//该渲染器文件下的光源0设定:
	m_shader->setuniformVEC3("u_light[0].position", m_move1[0].x * m_Plight_dis, m_move1[0].y, m_move1[0].z);//光源的位置
	m_shader->setuniformVEC3("u_light[0].ambientcolor", 0.15f, 0.15f, 0.15f);//发出环境光的颜色
	m_shader->setuniformVEC3("u_light[0].diffuse", m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);//发出漫反射光的颜色
	m_shader->setuniformVEC3("u_light[0].specular", m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);//发出镜面反射的颜色
	//该渲染器文件下的光源1设定:
	m_shader->setuniformVEC3("u_light[1].position", m_move1[1].x * m_Plight_dis, m_move1[1].y, m_move1[1].z);//光源的位置
	m_shader->setuniformVEC3("u_light[1].ambientcolor", 0.15f, 0.15f, 0.15f);//发出环境光的颜色
	m_shader->setuniformVEC3("u_light[1].diffuse", m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);//发出漫反射光的颜色
	m_shader->setuniformVEC3("u_light[1].specular", m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);//发出镜面反射的颜色
	//该渲染器文件下的光源2设定:
	m_shader->setuniformVEC3("u_light[2].position", m_move1[2].x, m_move1[2].y * m_Plight_dis, m_move1[2].z);//光源的位置
	m_shader->setuniformVEC3("u_light[2].ambientcolor", 0.15f, 0.15f, 0.15f);//发出环境光的颜色
	m_shader->setuniformVEC3("u_light[2].diffuse", m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);//发出漫反射光的颜色
	m_shader->setuniformVEC3("u_light[2].specular", m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);//发出镜面反射的颜色
	//该渲染器文件下的光源3设定:
	m_shader->setuniformVEC3("u_light[3].position", m_move1[3].x, m_move1[3].y * m_Plight_dis, m_move1[3].z);//光源的位置
	m_shader->setuniformVEC3("u_light[3].ambientcolor", 0.15f, 0.15f, 0.15f);//发出环境光的颜色
	m_shader->setuniformVEC3("u_light[3].diffuse", m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);//发出漫反射光的颜色
	m_shader->setuniformVEC3("u_light[3].specular", m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);//发出镜面反射的颜色
	//该渲染器文件下的光源4设定:
	m_shader->setuniformVEC3("u_light[4].position", m_move1[4].x, m_move1[4].y, m_move1[4].z * m_Plight_dis);//光源的位置
	m_shader->setuniformVEC3("u_light[4].ambientcolor", 0.15f, 0.15f, 0.15f);//发出环境光的颜色
	m_shader->setuniformVEC3("u_light[4].diffuse", m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);//发出漫反射光的颜色
	m_shader->setuniformVEC3("u_light[4].specular", m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);//发出镜面反射的颜色
	//该渲染器文件下的光源5设定:
	m_shader->setuniformVEC3("u_light[5].position", m_move1[5].x, m_move1[5].y, m_move1[5].z * m_Plight_dis);//光源的位置
	m_shader->setuniformVEC3("u_light[5].ambientcolor", 0.15f, 0.15f, 0.15f);//发出环境光的颜色
	m_shader->setuniformVEC3("u_light[5].diffuse", m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);//发出漫反射光的颜色
	m_shader->setuniformVEC3("u_light[5].specular", m_lightcolor.x, m_lightcolor.y, m_lightcolor.z);//发出镜面反射的颜色

	//手电筒光的距离衰减:
	m_shader->setuniform1f("u_FLight_ATT.C", 1.0f);
	m_shader->setuniform1f("u_FLight_ATT.L", 0.0005f);
	m_shader->setuniform1f("u_FLight_ATT.Q", 0.000003f);
	//手电筒光的设定：
	m_shader->setuniformVEC3("u_flash.position", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z);
	m_shader->setuniformVEC3("u_flash.diract", m_camera_Fro.x, m_camera_Fro.y, m_camera_Fro.z);
	m_shader->setuniform1f("u_flash.cutoff", glm::cos(glm::radians(9.5f)));
	m_shader->setuniform1f("u_flash.OutCutoff", glm::cos(glm::radians(1.5f)));
	if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
		m_shader->setuniform1i("u_flash.flashSwitch", 1);
	else
		m_shader->setuniform1i("u_flash.flashSwitch", 0);

	glBindVertexArray(m_vertexbufferlayout->VAOid());
	glm::mat4 move = glm::translate(glm::mat4(1.0f), m_move);
	m_shader->setuniformMat4f("u_model", move);//设置传出物体的位置
	for (int i = 0; i < 9; i++)
	{
		m_texture32->bind(0, 2 * i);
		m_texture32->bind(1, 2 * i + 1);
		glm::mat4 location = glm::translate(glm::mat4(1.0f), m_location[i] * m_object_dis);
		m_shader->setuniformMat4f("u_copy",location);
		glm::mat4 MVP1 = m_project * CameraView * move * location;
		m_shader->setuniformMat4f("u_MVP", MVP1);
		glDrawElements(GL_TRIANGLES, LayoutNum, GL_UNSIGNED_INT, nullptr);
	}
	
//渲染光源：
	m_shader1->bind();
	m_texture32->unbind();
	glBindVertexArray(m_vertexbufferlayout1->VAOid());
	m_shader1->setuniformVEC3("u_light_color",m_lightcolor.x,m_lightcolor.y,m_lightcolor.z);
	for (int i = 0; i < 6; i++)
	{
		glm::mat4 move1 = glm::translate(glm::mat4(1.0f), m_move1[i] * m_Plight_dis);
		glm::mat4 MVP2 = m_project * CameraView * move1;
		m_shader1->setuniformMat4f("u_MVP", MVP2);
		glDrawElements(GL_TRIANGLES, LayoutNum_1, GL_UNSIGNED_INT, nullptr);
	}

//渲染天空盒：
	glDepthFunc(GL_LEQUAL);
	m_shaderSkybox->bind();
	m_textureblock->bind();
	glm::mat4 skyboxMVP = m_project * glm::mat4(glm::mat3(CameraView));

	glBindVertexArray(m_vertexbufferlayout2->VAOid());
	m_shaderSkybox->setuniformMat4f("u_MVP", skyboxMVP);
	m_shaderSkybox->setuniformVEC4("u_light",0.3f + m_skyboxLight, 0.3f + m_skyboxLight, 0.3f + m_skyboxLight,1.0f);
	glDrawElements(GL_TRIANGLES, skyboxLayoutNum, GL_UNSIGNED_INT, nullptr);
	glDepthFunc(GL_LESS);
}

void light::renderImguiContext()
{
	ImGui::SliderFloat3("X Y Z", &m_move.x, -300.0f, 300.0f);
	ImGui::SliderFloat("skybox",&m_skyboxLight,0.0f,0.7f);
	ImGui::SliderFloat("PointLight distance", &m_Plight_dis, 1.0f, 2.5f);
	ImGui::SliderFloat("Block distance", &m_object_dis, 1.0f, 1.5f);
	if (ImGui::Button("reset position"))
		m_move = { 0.0f, 0.0f, 0.0f };
	ImGui::ColorEdit3("light color",&m_lightcolor.x);
	ImGui::Text("camera position: x:%.2f  y:%.2f  z:%2.f  fov:%.2f", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z, m_fov + 45.0f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
