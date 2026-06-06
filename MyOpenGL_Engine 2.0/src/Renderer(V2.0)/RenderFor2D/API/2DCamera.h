#pragma once
#include <GLFW/glfw3.h>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
class CameraFor2D
{
public:
	CameraFor2D() = default;
	CameraFor2D(GLFWwindow* window, int Window_width, int Window_height, float farPlane = 100.0f, float z_Position = 10.0f);
	//控制相机运动
	void ControlCamera(float speed);
	//更新相机的缩放数值
	void Modifile_Scale(float scale);
	//更新视图矩阵，参数说明：X为窗口的宽度,Y为窗口的高度
	void Modifile_ortho(int X, int Y);
	//返回相机的矩阵
	glm::mat4 GetCameraMatrix()const { return m_Camera_Proj; }
	//返回相机的坐标
	glm::vec3 GetCameraPosition()const { return m_CameraPos; }
	//返回相机的缩放值
	float GetCameraScale()const { return m_scale; }

private:
	void ReCaculateProject();

	GLFWwindow* m_window;
	int m_width, m_height;//记录下的窗口的大小状况
	glm::vec3 m_CameraPos = { 0.0f,0.0f,10.0f };
	glm::mat4 m_Camera_Proj = { 0.0f };
	float m_scale = 10.0f;
	float m_FarPlane;
};