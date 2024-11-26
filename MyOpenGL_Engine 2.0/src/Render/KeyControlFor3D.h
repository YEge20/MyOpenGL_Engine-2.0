#pragma once
#include<iostream>
#include <GLFW/glfw3.h>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

class KeyControlFor3D
{
public:
	//��ʼ��3D�ؼ���������һ��������Ŀ�괰�ڣ��ڶ����������Ƿ����������������,����������Ϊ�Ƿ��������ֿ����ӽǹ���
	KeyControlFor3D(GLFWwindow* window, bool CameraViewSetup, bool MousescrollSetup);
	~KeyControlFor3D();
	//��ͨ����ƶ�ϵͳ��������һ������Ϊ����ĳ�ʼλ�ã��ڶ�������������ĳ�ʼ���߳��򣬵�������������������ƶ������������ĸ��������ƶ��ٶ�
	glm::mat4 CameraMove(glm::vec3* Position, glm::vec3* Front, glm::vec3* Up, float speed);
	//�˺��������������¼��󷵻�fovֵ�������glm�е�perspective����ʹ�ã�
	float MousescrollFunction();
	//���ظ������ĳЩ������
	/*��������*/
	inline glm::vec3 GetCamera_Pos() { return m_position; };
	/*��������۲��λ��*/
	inline glm::vec3 GetCamera_Fro() { return m_Front; };
	/*��������۲�ķ���������ע�⣺��������ģ��Ϊ1*/
	inline glm::vec3 GetCamera_Normalize_Fro() { return glm::normalize(m_Front - m_position); };
private:
	GLFWwindow* m_window;
	glm::vec3 m_position = { 0.0f, 0.0f, 0.0f }, m_Front = { 0.0f,0.0f,0.0f };
	bool m_CameraViewSetup;
	bool m_MouseScroll;
};