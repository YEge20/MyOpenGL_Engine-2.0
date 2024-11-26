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
	//此函数侦听鼠标滚轮事件后返回fov值，需配合glm中的perspective函数使用：
	float MousescrollFunction();
	//返回该相机的某些参数：
	/*返回坐标*/
	inline glm::vec3 GetCamera_Pos() { return m_position; };
	/*返回相机观察的位置*/
	inline glm::vec3 GetCamera_Fro() { return m_Front; };
	/*返回相机观察的方向向量，注意：该向量的模长为1*/
	inline glm::vec3 GetCamera_Normalize_Fro() { return glm::normalize(m_Front - m_position); };
private:
	GLFWwindow* m_window;
	glm::vec3 m_position = { 0.0f, 0.0f, 0.0f }, m_Front = { 0.0f,0.0f,0.0f };
	bool m_CameraViewSetup;
	bool m_MouseScroll;
};