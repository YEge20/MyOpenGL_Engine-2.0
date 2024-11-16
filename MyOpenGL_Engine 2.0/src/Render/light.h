#pragma once
#include<memory>
#include"shader.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"ImguiFunction.h"
#include"vertexbufferLayout.h"
#include"texture32.h"
#include"TextureBlock.h"
#include"Render/KeyControlFor3D.h"

//tets:
#include"DrawBlock.h"

class light
{
public:
	light(GLFWwindow* window);

	void renderContext(float timestep, float milltimestep);
	void renderImguiContext();
private:
	float m_fov;
	float m_skyboxLight;//��պе�����
	float m_Plight_dis;//���Դ֮��ľ������
	float m_object_dis;//����֮��ľ������

	GLFWwindow* m_window;
	glm::mat4 m_project;//����͸��ͶӰ����
	glm::vec3 m_move;//�������λ��
	glm::vec3 m_location[9];//ÿ�������λ��
	glm::vec3 m_move1[6];//��Դ��λ��
	glm::vec3 m_lightcolor;//��Դ����ɫ


	glm::vec3 m_camera_Pos;//�������λ��
	glm::vec3 m_camera_Fro;//������ķ���
	glm::vec3 m_camera_Up;//����������Ϸ���


	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Shader> m_shader1;
	std::shared_ptr<Shader> m_shaderSkybox;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout1;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout2;
	std::unique_ptr<texture32> m_texture32;
	std::unique_ptr<TextureBlock> m_textureblock;
	std::unique_ptr<KeyControlFor3D> m_control_Camera;

	//test:
	std::shared_ptr<Shader> m_test_block;
	std::shared_ptr<DrawBlock> m_test_drawblock;
	glm::vec3 m_test_color[6];
};