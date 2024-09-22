#pragma once
#include<iostream>
#include <GLFW/glfw3.h>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

class KeyControlFor3D
{
public:
	//初始化3D控件函数，第一个参数是目标窗口，第二个参数是是否开启相机的自由视线,第三个参数为是否开启鼠标滚轮控制视角功能
	KeyControlFor3D(GLFWwindow* window, bool CameraViewSetup, bool MousescrollSetup);
	~KeyControlFor3D();
	//普通相机移动系统函数，以一个参数为相机的初始位置，第二个参数是相机的初始视线朝向，第三个参数是相机上下移动的向量，第四个参数是移动速度
	glm::mat4 CameraMove(glm::vec3* Position, glm::vec3* Front, glm::vec3* Up, float speed);
	float MousescrollFunction();

private:
	GLFWwindow* m_window;
	bool m_CameraViewSetup;
	bool m_MouseScroll;
};