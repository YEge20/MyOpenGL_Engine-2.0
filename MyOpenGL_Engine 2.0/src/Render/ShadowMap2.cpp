#include "ShadowMap2.h"

ShadowMap2::ShadowMap2(GLFWwindow* window)
	:m_window(window), m_rotaspeed(0.1f),
	m_move(0.0f, -10.0f, 0.0f), m_light_color{ 1.0f,1.0f,1.0f },
	m_camera_Pos(0.0f, -30.0f, 250.0f), m_camera_Fro(0.0f, 0.0f, -1.0f), m_camera_Up(0.0f, 1.0f, 0.0f),
	m_moreObject{
		{ 1.0f,0.0f,0.0f }, { 40.0f,25.0f,40.8f }, {-33.8f,10.0f,14.4f},{45.0f,-75.0f,-18.0f},{ -57.5f,-34.0f,40.0f},
		{30.0f,-12.0f,-75.0f},{ -21.0f,-27.0f,30.0f},{46.7f,-30.0f,35.0f},{-80.0f,20.5f,68.0f},{-90.0f,-40.0f,-36.5f},{-88.0f,29.4f,-48.0f},{-87.2f,-64.4f,57.7f},
		{80.0f,20.5f,58.0f},{90.0f,-40.0f,-36.5f},{88.0f,29.4f,-48.0f},{87.2f,-44.4f,57.7f}
	},
	m_moreObject_2{
		{-42.7f,0.0f,-33.0f},{55.2f,0.0f,57.2f},{35.8f,0.0f,-34.1f},{-55.2f,0.0f,50.0f},{-60.5f,0.0f,-66.6f},
		{71.8f,0.0f,1.4f},{-48.8f,0.0f,15.7f},{3.3f,0.0f,-50.3f},{-6.7f,0.0f,60.8f},{32.2f,0.0f,30.6f}
	},
	m_moreObject_3{
		{24.5f,0.0f,33.8f},{-18.8f,0.0f,-16.7f},{15.6f,0.0f,-18.5f},{-17.2f,0.0f,14.7f},{2.8f,0.0f,-15.7f},
		{-7.7f,0.0f,-16.7f},{14.0f,0.0f,2.6f},{-19.5f,0.0f,1.6f},{24.5f,0.0f,7.1f},{3.3f,0.0f,17.7f}
	},
	m_grass_move(0.0f, -120.0f, 0.0f), m_grass_2_move(0.0f, -109.5f, 0.0f), m_flower_move(0.0f, -112.0f, 0.0f), m_france_position(-40.0f, 0.6f, 55.4f),
	m_day(true)

{
	std::cout << "Running ShadowMap2.cpp" << std::endl;
	m_shader.reset(new Shader("./sharder/depth2/BasicShader3D(Light_version)3.shader"));
	m_shader_1.reset(new Shader("./sharder/depth2/GrassGround.shader"));
	m_shader_2.reset(new Shader("./sharder/depth2/Grass.shader"));
	m_shader_depth.reset(new Shader("./sharder/depth2/depthMap.shader"));
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
		//vertex:         normalize:        texcoord:
		3,                3,                2
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
	//m_vertexbufferlayout = std::make_unique<vertexbufferlayout>(vertexbuffer, Layout, Databuffer3D, LayoutNum0);
	m_vertexbufferlayout.reset(new vertexbufferlayout(vertexbuffer, Layout, Databuffer3D, LayoutNum0));
	m_vertexbufferlayout->AttribPointer(countOfindex, DatabufferSize, 8);

#define grassgroundBuffer 288
	float grassground[grassgroundBuffer] =
	{   //vertex                   texcoord       color                      normalize:
		-80.0f, -5.5f,  80.0f,     0.0f,0.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,0.0f,1.0f,//0
		-80.0f,  5.5f,  80.0f,     0.0f,1.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,0.0f,1.0f,//1
		 80.0f, -5.5f,  80.0f,     1.0f,0.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,0.0f,1.0f,//2
		 80.0f,  5.5f,  80.0f,     1.0f,1.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,0.0f,1.0f,//3

		-80.0f, -5.5f, -80.0f,     0.0f,0.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,0.0f,-1.0f,//4
		-80.0f,  5.5f, -80.0f,     0.0f,1.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,0.0f,-1.0f,//5
		 80.0f, -5.5f, -80.0f,     1.0f,0.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,0.0f,-1.0f,//6
		 80.0f,  5.5f, -80.0f,     1.0f,1.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,0.0f,-1.0f,//7

		 80.0f, -5.5f,  80.0f,     0.0f,0.0f,     0.08f,0.0f,0.0f,1.0f,     1.0f,0.0f,0.0f,//8
		 80.0f,  5.5f,  80.0f,     0.0f,1.0f,     0.08f,0.0f,0.0f,1.0f,     1.0f,0.0f,0.0f,//9
		 80.0f, -5.5f, -80.0f,     1.0f,0.0f,     0.08f,0.0f,0.0f,1.0f,     1.0f,0.0f,0.0f,//10
		 80.0f,  5.5f, -80.0f,     1.0f,1.0f,     0.08f,0.0f,0.0f,1.0f,     1.0f,0.0f,0.0f,//11

		-80.0f, -5.5f,  80.0f,     0.0f,0.0f,     0.08f,0.0f,0.0f,1.0f,     -1.0f,0.0f,0.0f,//12
		-80.0f,  5.5f,  80.0f,     0.0f,1.0f,     0.08f,0.0f,0.0f,1.0f,     -1.0f,0.0f,0.0f,//13
		-80.0f, -5.5f, -80.0f,     1.0f,0.0f,     0.08f,0.0f,0.0f,1.0f,     -1.0f,0.0f,0.0f,//14
		-80.0f,  5.5f, -80.0f,     1.0f,1.0f,     0.08f,0.0f,0.0f,1.0f,     -1.0f,0.0f,0.0f,//15

		-80.0f,  5.5f,  80.0f,     0.0f,0.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,1.0f,0.0f,//16
		-80.0f,  5.5f, -80.0f,     0.0f,1.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,1.0f,0.0f,//17
		 80.0f,  5.5f,  80.0f,     1.0f,0.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,1.0f,0.0f,//18
		 80.0f,  5.5f, -80.0f,     1.0f,1.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,1.0f,0.0f,//19

		-80.0f, -5.5f,  80.0f,     0.0f,0.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,-1.0f,0.0f,//20
		-80.0f, -5.5f, -80.0f,     0.0f,1.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,-1.0f,0.0f,//21
		 80.0f, -5.5f,  80.0f,     1.0f,0.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,-1.0f,0.0f,//22
		 80.0f, -5.5f, -80.0f,     1.0f,1.0f,     0.08f,0.0f,0.0f,1.0f,     0.0f,-1.0f,0.0f //23
	};
#define grassgroundCountIndex 4
	int grassgroundIndex[grassgroundCountIndex] =
	{
		3,2,4,3
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
	//m_vertexbufferlayout_1 = std::make_unique<vertexbufferLayout1>(grassground, grassgroundLyaout, grassgroundBuffer, grassgroundLayoutNum);
	m_vertexbufferlayout_1.reset(new vertexbufferlayout(grassground, grassgroundLyaout, grassgroundBuffer, grassgroundLayoutNum));
	m_vertexbufferlayout_1->AttribPointer(grassgroundCountIndex, grassgroundIndex, 12);

#define grassBuffer 208
	float grass[grassBuffer] =
	{
		//vertex              texcoord      color                     top_button       normal:
		 5.0f, 5.0f, 5.0f,    1.0f,1.0f,    0.25f,0.5f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//0
		-5.0f, 5.0f,-5.0f,    0.0f,1.0f,    0.25f,0.5f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//1
		 5.0f,-5.0f, 5.0f,    1.0f,0.0f,    0.20f,0.5f,0.05f,1.0f,     0.0f,           0.0f,1.0f,0.0f,//2
		-5.0f,-5.0f,-5.0f,    0.0f,0.0f,    0.20f,0.5f,0.05f,1.0f,     0.0f,           0.0f,1.0f,0.0f,//3

		-5.0f, 5.0f, 5.0f,    0.0f,1.0f,    0.25f,0.5f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//4
		 5.0f, 5.0f,-5.0f,    1.0f,1.0f,    0.25f,0.5f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//5
		-5.0f,-5.0f, 5.0f,    0.0f,0.0f,    0.20f,0.5f,0.05f,1.0f,     0.0f,           0.0f,1.0f,0.0f,//6
		 5.0f,-5.0f,-5.0f,    1.0f,0.0f,    0.20f,0.5f,0.05f,1.0f,     0.0f,           0.0f,1.0f,0.0f,//7

		 5.01f, 5.0f, 4.99f,    1.0f,1.0f,    0.25f,0.5f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//8
		-4.99f, 5.0f,-5.01f,    0.0f,1.0f,    0.25f,0.5f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//9
		 5.01f,-5.0f, 4.99f,    1.0f,0.0f,    0.20f,0.5f,0.05f,1.0f,     0.0f,           0.0f,1.0f,0.0f,//10
		-4.99f,-5.0f,-5.01f,    0.0f,0.0f,    0.20f,0.5f,0.05f,1.0f,     0.0f,           0.0f,1.0f,0.0f,//11

		-4.99f, 5.0f, 5.01f,    0.0f,1.0f,    0.25f,0.5f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//12
		 5.01f, 5.0f,-4.99f,    1.0f,1.0f,    0.25f,0.5f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//13
		-4.99f,-5.0f, 5.01f,    0.0f,0.0f,    0.20f,0.5f,0.05f,1.0f,     0.0f,           0.0f,1.0f,0.0f,//14
		 5.01f,-5.0f,-4.99f,    1.0f,0.0f,    0.20f,0.5f,0.05f,1.0f,     0.0f,           0.0f,1.0f,0.0f,//15
	};
#define grassCountIndex 5
	int grassIndex[grassCountIndex] =
	{
		3,2,4,1,3
	};
#define grassLayoutNum 24
	unsigned int grassLayout[grassLayoutNum] =
	{
		0,1,2,
		1,2,3,

		4,5,6,
		5,6,7,

		8,9,10,
		9,10,11,

		12,13,14,
		13,14,15

	};

#define flowerBuffer 208
	float flower[flowerBuffer] =
	{
		//vertex              texcoord      color                     top_button       normal:
		 2.5f, 2.5f, 2.5f,    1.0f,1.0f,    0.0f,0.0f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//0
		-2.5f, 2.5f,-2.5f,    0.0f,1.0f,    0.0f,0.0f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//1
		 2.5f,-2.5f, 2.5f,    1.0f,0.0f,    0.0f,0.0f,0.0f,1.0f,      0.0f,           0.0f,1.0f,0.0f,//2
		-2.5f,-2.5f,-2.5f,    0.0f,0.0f,    0.0f,0.0f,0.0f,1.0f,      0.0f,           0.0f,1.0f,0.0f,//3

		-2.5f, 2.5f, 2.5f,    0.0f,1.0f,    0.0f,0.0f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//4
		 2.5f, 2.5f,-2.5f,    1.0f,1.0f,    0.0f,0.0f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//5
		-2.5f,-2.5f, 2.5f,    0.0f,0.0f,    0.0f,0.0f,0.0f,1.0f,      0.0f,           0.0f,1.0f,0.0f,//6
		 2.5f,-2.5f,-2.5f,    1.0f,0.0f,    0.0f,0.0f,0.0f,1.0f,      0.0f,           0.0f,1.0f,0.0f,//7

		 2.51f, 2.5f, 2.49f,    1.0f,1.0f,    0.0f,0.0f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//8
		-2.49f, 2.5f,-2.51f,    0.0f,1.0f,    0.0f,0.0f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//9
		 2.51f,-2.5f, 2.49f,    1.0f,0.0f,    0.0f,0.0f,0.0f,1.0f,      0.0f,           0.0f,1.0f,0.0f,//10
		-2.49f,-2.5f,-2.51f,    0.0f,0.0f,    0.0f,0.0f,0.0f,1.0f,      0.0f,           0.0f,1.0f,0.0f,//11

		-2.51f, 2.5f, 2.51f,    0.0f,1.0f,    0.0f,0.0f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//12
		 2.51f, 2.5f,-2.49f,    1.0f,1.0f,    0.0f,0.0f,0.0f,1.0f,      1.0f,           0.0f,1.0f,0.0f,//13
		-2.49f,-2.5f, 2.51f,    0.0f,0.0f,    0.0f,0.0f,0.0f,1.0f,      0.0f,           0.0f,1.0f,0.0f,//14
		 2.51f,-2.5f,-2.49f,    1.0f,0.0f,    0.0f,0.0f,0.0f,1.0f,      0.0f,           0.0f,1.0f,0.0f,//15

	};
#define flowerCountIndex 5
	int flowerIndex[flowerCountIndex] =
	{
		3,2,4,1,3
	};
#define flowerLayoutNum 24 
	unsigned int flowerLayout[flowerLayoutNum] =
	{
		0,1,2,
		1,2,3,

		4,5,6,
		5,6,7,

		8,9,10,
		9,10,11,

		12,13,14,
		13,14,15
	};
#define tiny_stoneBuffer 
	m_vertexbufferlayout_2 = std::make_unique<vertexbufferLayout_vao_Group>();

	m_vertexbufferlayout_2->importVertex(grass, grassLayout, grassBuffer, grassLayoutNum, 0);
	m_vertexbufferlayout_2->AttribPointer(grassCountIndex, grassIndex, 13, 0);

	m_vertexbufferlayout_2->importVertex(flower, flowerLayout, flowerBuffer, flowerLayoutNum, 1);
	m_vertexbufferlayout_2->AttribPointer(flowerCountIndex, flowerIndex, 13, 1);


	//材质设定：
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_texture32.reset(new texture32(false));
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

	std::vector<std::string> smoker =
	{
		"./texture/smoker/smoker_side.png",
		"./texture/smoker/smoker_side.png",
		"./texture/smoker/smoker_top.png",
		"./texture/smoker/smoker_top.png",
		"./texture/smoker/smoker_front.png",
		"./texture/smoker/smoker_side.png"
	};
	std::vector<std::string> furance =
	{
		"./texture/furnace/furnace_side.png",
		"./texture/furnace/furnace_side.png",
		"./texture/furnace/furnace_top.png",
		"./texture/furnace/furnace_top.png",
		"./texture/furnace/furnace_front.png",
		"./texture/furnace/furnace_side.png"
	};
	m_textureblock1 = std::make_unique<TextureBlock8>(true, false);
	m_textureblock1->importtexture(furance, 0);
	m_textureblock1->importtexture(smoker, 1);
	m_textureblock1->bind(0);

	//3D渲染必须启动深度测试否则渲染过程不正确：
	glEnable(GL_DEPTH_TEST);

	m_control_Camera = std::make_unique<KeyControlFor3D>(m_window, true, true);

	//初始化深度图：
	m_depth_texture = std::make_unique<DepthMapBuffer>(1024);

}

void ShadowMap2::renderContext()
{

//平行光的位置、亮度的计算
	if (m_degreeOflight > 90.0f && m_day == true)//白天过渡到夜晚
	{
		m_degreeOflight = -90.0f;
		m_strength_light = 0.25f;
		m_day = false;
	}
	if (m_degreeOflight > 90.0f && m_day == false)//夜晚过渡到白天
	{
		m_degreeOflight = -90.0f;
		m_strength_light = 1.2f;
		m_day = true;
		m_count_day++;
	}
	if (m_degreeOflight_speed_current < m_degreeOflight_speed)
		m_degreeOflight_speed_current += 0.001f;
	else if (m_degreeOflight_speed_current > m_degreeOflight_speed)
		m_degreeOflight_speed_current -= 0.001f;
	m_degreeOflight += m_degreeOflight_speed_current;
	m_light_position = { 165.0f * sin(glm::radians(m_degreeOflight)),165.0f * cos(glm::radians(m_degreeOflight)) - 120.0f , 0.0f };
//温度的计算：
	if (m_temperature > sin(glm::radians(10.0f * m_count_day)))
		m_temperature -= 0.001f;
	else if (m_temperature < sin(glm::radians(10.0f * m_count_day)))
		m_temperature += 0.001f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//深度贴图计算
	
	glViewport(0, 0, 1024, 1024);
	m_depth_texture->bind();
	glClear(GL_DEPTH_BUFFER_BIT);

	//计算建模时所用到的投影和视图矩阵
	glm::mat4 Lightproject = glm::ortho(-120.0f, 120.0f, -120.0f, 120.0f, 0.0f, 500.0f);
	glm::mat4 LightView = glm::lookAt(m_light_position, glm::vec3(0.0f, -120.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	//矿石建模
	m_shader_depth->bind();
	m_shader_depth->setuniform1f("u_wave_option", 0.0f);//花草模型摇晃标识
	glBindVertexArray(m_vertexbufferlayout->VAOid());
	//矿石的旋转计算
	if (m_temperature > 0.6f)
		m_rotaspeed = 1.0f;
	else if (m_temperature > -0.75f && m_temperature < -0.5f)
		m_rotaspeed = 1.7f;
	else if (m_temperature < -0.75f)
		m_rotaspeed = 2.0f;
	else
		m_rotaspeed = 0.18f;
	if (m_speed_add < m_rotaspeed - 0.01f)
		m_speed_add += 0.002f;
	else if (m_speed_add > m_rotaspeed + 0.01f)
		m_speed_add -= 0.002f;
	m_rad += m_speed_add;
	if (m_rad > 360.0f)
		m_rad = 0.0f;
	//矿石的漂浮计算
	m_float_time += 1.5f;
	if (m_float_time > 360.0f)
		m_float_time = 0.0f;
	glm::mat4 move_depth = glm::translate(glm::mat4(1.0f), m_move);
	for (int x = 0; x < 16; x++)
	{
		glm::mat4 moreObjectCopy = glm::translate(glm::mat4(1.0f), m_moreObject[x]);
		glm::mat4 rota = glm::rotate(glm::mat4(1.0f), glm::radians(m_rad), m_moreObject[x]);
		glm::mat4 floating = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.5 * sin(glm::radians(m_float_time + m_moreObject[x].x * m_moreObject[x].y)), 0.0f));
		glm::mat4 model = move_depth * moreObjectCopy * floating * rota;
		glm::mat4 MVP1 = Lightproject * LightView * model;
		m_shader_depth->setuniformMat4f("u_MVP", MVP1);
		glDrawElements(GL_TRIANGLES, LayoutNum0, GL_UNSIGNED_INT, nullptr);
	}
	//草地建模：
	glBindVertexArray(m_vertexbufferlayout_1->VAOid());
	glm::mat4 grassMove_depth = glm::translate(glm::mat4(1.0f), m_grass_move);
	glm::mat4 MVP2_depth = Lightproject * LightView * grassMove_depth;
	m_shader_depth->setuniform1f("u_wave_option", 0.0f);//花草模型摇晃标识
	m_shader_depth->setuniformMat4f("u_MVP", MVP2_depth);
	glDrawElements(GL_TRIANGLES, grassgroundLayoutNum, GL_UNSIGNED_INT, nullptr);

	//花草的摇摆幅度增加计算
	if (m_temperature > 0.6f)
		m_GrassFlower_wave = 1.2f;
	else if (m_temperature > -0.75f && m_temperature < -0.5f)
		m_GrassFlower_wave = 2.2f;
	else if (m_temperature < -0.75f)
		m_GrassFlower_wave = 1.7f;
	else
		m_GrassFlower_wave = 0.0f;
	if (m_GrassFlower_wave_current > m_GrassFlower_wave + 0.01f)
		m_GrassFlower_wave_current -= 0.01f;
	else if (m_GrassFlower_wave_current < m_GrassFlower_wave - 0.01f)
		m_GrassFlower_wave_current += 0.01f;

	//花草的摇摆频率计算
	if (m_temperature > 0.6f)
		m_GrassFlower_Frequency = 0.25f;
	else if (m_temperature > -0.75f && m_temperature < -0.5f)
		m_GrassFlower_Frequency = 0.75f;
	else if (m_temperature < -0.75f)
		m_GrassFlower_Frequency = 1.0f;
	else
		m_GrassFlower_Frequency = 0.5f;
	if (m_GrassFlower_Frequency_current > m_GrassFlower_Frequency + 0.01f)
		m_GrassFlower_Frequency_current -= 0.01f;
	else if (m_GrassFlower_Frequency_current < m_GrassFlower_Frequency - 0.01f)
		m_GrassFlower_Frequency_current += 0.01f;
	if (m_GrassFlower_shake_degree > 360.0f)
		m_GrassFlower_shake_degree = 0.0f;
	m_GrassFlower_shake_degree += m_GrassFlower_Frequency_current;

	//草建模：
	m_vertexbufferlayout_2->bind(0);
	glm::mat4 grass_position_depth = glm::translate(glm::mat4(1.0f), m_grass_2_move);
	m_shader_depth->setuniform1f("u_wave_option", 1.0f);//花草模型摇晃标识
	for (int i = 0; i < 10; i++)
	{
		glm::mat4 moregrass = glm::translate(glm::mat4(1.0f), m_moreObject_2[i]);
		glm::mat4 model_grass = grass_position_depth * moregrass;
		glm::mat4 wave0 = glm::translate(glm::mat4(1.0f), glm::vec3((1.0f + m_GrassFlower_wave_current) * sin(glm::radians(m_GrassFlower_shake_degree) + m_moreObject_2[i].x * m_moreObject_2[i].z), 0.0f, (1.0f + m_GrassFlower_wave_current) * cos(glm::radians(m_GrassFlower_shake_degree) + m_moreObject_2[i].x * m_moreObject_2[i].z)));
		m_shader_depth->setuniformMat4f("u_wave", wave0);
		glm::mat4 MVP3 = Lightproject * LightView * model_grass;
		m_shader_depth->setuniformMat4f("u_MVP", MVP3);
		m_texture32->bind(6, 2);
		m_shader_depth->setuniform1i("u_texture_test", 6);
		glDrawElements(GL_TRIANGLES, grassLayoutNum, GL_UNSIGNED_INT, nullptr);
	};
	//花建模：
	m_vertexbufferlayout_2->bind(1);
	m_shader_depth->setuniform1f("u_wave_option", 1.0f);//花草模型摇晃标识
	glm::mat4 flower_position_depth = glm::translate(glm::mat4(1.0f), m_flower_move);
	for (int i = 0; i < 10; i++)
	{
		glm::mat4 moreflower = glm::translate(glm::mat4(1.0f), m_moreObject_3[i]);
		glm::mat4 model_flower = flower_position_depth * moreflower;
		glm::mat4 wave1 = glm::translate(glm::mat4(1.0f), glm::vec3((1.0f + m_GrassFlower_wave_current) * sin(glm::radians(m_GrassFlower_shake_degree) + m_moreObject_3[i].x * m_moreObject_3[i].z), 0.0f, (1.0f + m_GrassFlower_wave_current) * cos(glm::radians(m_GrassFlower_shake_degree) + m_moreObject_3[i].x * m_moreObject_3[i].z)));
		m_shader_depth->setuniformMat4f("u_wave", wave1);
		glm::mat4 MVP4 = Lightproject * LightView * model_flower;
		m_shader_depth->setuniformMat4f("u_MVP", MVP4);
		m_texture32->bind(6, 3 + i % 5);
		m_shader_depth->setuniform1i("u_texture_test", 6);
		glDrawElements(GL_TRIANGLES, grassLayoutNum, GL_UNSIGNED_INT, nullptr);
	}
	//熔炉建模：
	glBindVertexArray(m_vertexbufferlayout->VAOid());
	glm::mat4 france_position_1_depth = glm::translate(glm::mat4(1.0f), m_france_position);
	glm::mat4 france_rota_depth = glm::rotate(glm::mat4(1.0f), glm::radians(-135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 france_model = france_position_1_depth * grass_position_depth * france_rota_depth;
	glm::mat4 MVP5_depth = Lightproject * LightView * france_model;
	m_shader_depth->setuniform1f("u_wave_option", 0.0f);//花草模型摇晃标识
	m_shader_depth->setuniformMat4f("u_MVP", MVP5_depth);
	glDrawElements(GL_TRIANGLES, LayoutNum0, GL_UNSIGNED_INT, nullptr);
	m_depth_texture->unbind();
	glViewport(0, 0, 1200, 800);
	
//渲染物体
	//计算渲染的矩阵类型和摄像机裁剪空间
	m_project = glm::perspective(glm::radians(45.0f + m_fov), (float)960 / (float)640, 0.1f, 450.0f);
	glm::mat4 CameraView = m_control_Camera->CameraMove(&m_camera_Pos, &m_camera_Fro, &m_camera_Up, 0.8f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//渲染矿石:
	m_shader->bind();
	glBindVertexArray(m_vertexbufferlayout->VAOid());
	m_fov = m_control_Camera->MousescrollFunction();
	m_shader->setuniformVEC3("u_light.color", m_light_color.x, m_light_color.y, m_light_color.z);
	m_shader->setuniformVEC3("u_view_position", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z);
	m_shader->setuniformVEC3("u_light.position", m_light_position.x, m_light_position.y, m_light_position.z);
	m_shader->setuniform1f("u_render_type", 0.0);
	m_shader->setuniform1f("u_strength_light", m_strength_light);
	glm::mat4 LightSpaceMartix_block = Lightproject * LightView;
	m_shader->setuniformMat4f("u_LightMartix", LightSpaceMartix_block);
	m_shader->setuniform1i("u_depth_texture", 2);//深度图
	m_depth_texture->use(2);
	glm::mat4 move = glm::translate(glm::mat4(1.0f), m_move);
	for (int x = 0; x < 16; x++)
	{
		glm::mat4 moreObjectCopy = glm::translate(glm::mat4(1.0f), m_moreObject[x]);
		glm::mat4 rota = glm::rotate(glm::mat4(1.0f), glm::radians(m_rad), m_moreObject[x]);
		glm::mat4 floating = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 1.5 * sin(glm::radians(m_float_time + m_moreObject[x].x * m_moreObject[x].y)), 0.0f));
		glm::mat4 model = move * moreObjectCopy * floating * rota;
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
		//根据设定的温度计算草和草地的颜色：
	if (m_temperature >= 0.0f)
	{
		m_red_factor = m_temperature;
		m_white_factor = 0.0f;
	}
	else if (m_temperature <= 0.0f)
	{
		m_white_factor = -m_temperature;
		m_red_factor = 0.0f;
	}

	m_shader_1->bind();
	glBindVertexArray(m_vertexbufferlayout_1->VAOid());
	glm::mat4 grassMove = glm::translate(glm::mat4(1.0f), m_grass_move);
	glm::mat4 MVP2 = m_project * CameraView * grassMove;
	glm::mat4 LightSpaceMartix_ground = Lightproject * LightView;
	m_shader_1->setuniformMat4f("u_model", grassMove);
	m_shader_1->setuniformVEC3("u_light.color", m_light_color.x, m_light_color.y, m_light_color.z);
	m_shader_1->setuniformVEC3("u_light.position", m_light_position.x, m_light_position.y, m_light_position.z);
	m_shader_1->setuniformVEC3("u_view_position", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z);
	m_shader_1->setuniform1f("u_strength_light", m_strength_light);
	m_shader_1->setuniformMat4f("u_LightMartix", LightSpaceMartix_ground);
	m_texture32->bind(0, 0);
	m_texture32->bind(1, 1);
	m_depth_texture->use(2);
	m_shader_1->setuniformMat4f("u_MVP", MVP2);
	m_shader_1->setuniform1i("u_texture0", 0);
	m_shader_1->setuniform1i("u_texture1", 1);
	m_shader_1->setuniform1i("u_texture2", 2);//深度图
	m_shader_1->setuniform1f("u_red", m_red_factor);
	m_shader_1->setuniform1f("u_white", m_white_factor);
	glDrawElements(GL_TRIANGLES, grassgroundLayoutNum, GL_UNSIGNED_INT, nullptr);
	//渲染花草:
		//渲染草：
	m_shader_2->bind();
	m_vertexbufferlayout_2->bind(0);
	glm::mat4 grass_position_rend = glm::translate(glm::mat4(1.0f), m_grass_2_move);
	glm::mat4 LightSpaceMartix_grass_flower = Lightproject * LightView;
	m_shader_2->setuniformMat4f("u_LightMartix", LightSpaceMartix_grass_flower);
	for (int i = 0; i < 10; i++)
	{
		glm::mat4 moregrass = glm::translate(glm::mat4(1.0f), m_moreObject_2[i]);
		glm::mat4 model_grass = grass_position_rend * moregrass;
		glm::mat4 MVP3 = m_project * CameraView * model_grass;
		glm::mat4 wave0 = glm::translate(glm::mat4(1.0f), glm::vec3((1.0f + m_GrassFlower_wave_current) * sin(glm::radians(m_GrassFlower_shake_degree) + m_moreObject_2[i].x * m_moreObject_2[i].z), 0.0f, (1.0f + m_GrassFlower_wave_current) * cos(glm::radians(m_GrassFlower_shake_degree) + m_moreObject_2[i].x * m_moreObject_2[i].z)));
		m_shader_2->setuniformMat4f("u_MVP", MVP3);
		m_shader_2->setuniformMat4f("u_wave", wave0);
		m_shader_2->setuniformMat4f("u_model", model_grass);
		m_shader_2->setuniform1f("u_red", m_red_factor);
		m_shader_2->setuniform1f("u_white", m_white_factor);
		m_shader_2->setuniform1f("u_grass_flower", 1.0f);
		m_shader_2->setuniformVEC3("u_light.position", m_light_position.x, m_light_position.y, m_light_position.z);
		m_shader_2->setuniformVEC3("u_light.color", m_light_color.x, m_light_color.y, m_light_color.z);
		m_shader_2->setuniform1f("u_strength_light", m_strength_light);
		m_texture32->bind(6, 2);
		m_shader_2->setuniform1i("u_texture0", 6);
		m_depth_texture->use(2);
		m_shader_2->setuniform1i("u_texture1", 2);//深度图
		glDrawElements(GL_TRIANGLES, grassLayoutNum, GL_UNSIGNED_INT, nullptr);
	}
	//渲染花：
	m_vertexbufferlayout_2->bind(0);
	glm::mat4 flower_position_rend = glm::translate(glm::mat4(1.0f), m_grass_2_move);
	for (int i = 0; i < 10; i++)
	{
		glm::mat4 moreflower = glm::translate(glm::mat4(1.0f), m_moreObject_3[i]);
		glm::mat4 model_flower = flower_position_rend * moreflower;
		glm::mat4 MVP4 = m_project * CameraView * model_flower;
		glm::mat4 wave1 = glm::translate(glm::mat4(1.0f), glm::vec3((1.0f + m_GrassFlower_wave_current) * sin(glm::radians(m_GrassFlower_shake_degree) + m_moreObject_3[i].x * m_moreObject_3[i].z), 0.0f, (1.0f + m_GrassFlower_wave_current) * cos(glm::radians(m_GrassFlower_shake_degree) + m_moreObject_3[i].x * m_moreObject_3[i].z)));
		m_shader_2->setuniformMat4f("u_MVP", MVP4);
		m_shader_2->setuniformMat4f("u_wave", wave1);
		m_shader_2->setuniformMat4f("u_model", model_flower);
		m_shader_2->setuniform1f("u_grass_flower", 0.0f);
		m_shader_2->setuniformVEC3("u_light.position", m_light_position.x, m_light_position.y, m_light_position.z);
		m_shader_2->setuniformVEC3("u_light.color", m_light_color.x, m_light_color.y, m_light_color.z);
		m_shader_2->setuniform1f("u_strength_light", m_strength_light);
		m_texture32->bind(6, 3 + i % 5);
		m_shader_2->setuniform1i("u_texture0", 6);
		m_depth_texture->use(2);
		m_shader_2->setuniform1i("u_texture1", 2);//深度图
		glDrawElements(GL_TRIANGLES, grassLayoutNum, GL_UNSIGNED_INT, nullptr);
	}

	//渲染熔炉：
	m_shader->bind();
	glBindVertexArray(m_vertexbufferlayout->VAOid());
	glm::mat4 MVP5 = m_project * CameraView * france_model;
	m_shader->setuniformMat4f("u_MVP", MVP5);
	m_shader->setuniformVEC3("u_light.color", m_light_color.x, m_light_color.y, m_light_color.z);
	m_shader->setuniformVEC3("u_view_position", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z);
	m_shader->setuniformVEC3("u_light.position", m_light_position.x, m_light_position.y, m_light_position.z);
	m_shader->setuniform1f("u_strength_light", m_strength_light);
	m_shader->setuniform1f("u_render_type", 1.0);
	m_shader->setuniformMat4f("u_model", france_model);
	m_shader->setuniformMat4f("u_rota", france_rota_depth);
	glDrawElements(GL_TRIANGLES, LayoutNum0, GL_UNSIGNED_INT, nullptr);
}

void ShadowMap2::renderImguiContext()
{
	ImGui::SliderFloat("X", &m_move.x, -30.0f, 30.0f);
	ImGui::SliderFloat("Z", &m_move.z, -30.0f, 30.0f);
	if (ImGui::Button("reset position"))
		m_move = { 0.0f, -10.0f, 0.0f };
	if (ImGui::Button("reset time speed"))
		m_degreeOflight_speed = 0.05f;
	ImGui::SliderFloat("time speed", &m_degreeOflight_speed, 0.0f, 0.25f);
	if (ImGui::Button("reset all"))
	{
		m_day = true;
		m_strength_light = 1.2f;
		m_degreeOflight = 0.0f;
		m_degreeOflight_speed = 0.05f;
		m_degreeOflight_speed_current = 0.05f;
		m_temperature = 0.0f;
		m_count_day = 0.0f;
	}
	ImGui::Text("camera position: x:%.2f  y:%.2f  z:%2.f   fov:%.2f", m_camera_Pos.x, m_camera_Pos.y, m_camera_Pos.z, 45.0f + m_fov);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::Text("day: %1.f    tempreature: %.2f    u_white: %.2f    u_red: %.2f", m_count_day, m_temperature, m_white_factor, m_red_factor);
	ImGui::Text("rota speed: %.2f , block rota degree:%.2f", m_speed_add, m_rad);
	ImGui::Text("wind strength: %.2f      wave degree: %.2f     wave frequence: %.2f", 1.0f + m_GrassFlower_wave, m_GrassFlower_shake_degree, m_GrassFlower_Frequency_current);
	ImGui::Text("light position: x:%.2f,y:%.2f,z:%.2f", m_light_position.x, m_light_position.y, m_light_position.z);
}
