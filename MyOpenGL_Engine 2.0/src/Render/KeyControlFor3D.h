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
	float MousescrollFunction();

private:
	GLFWwindow* m_window;
	bool m_CameraViewSetup;
	bool m_MouseScroll;
};