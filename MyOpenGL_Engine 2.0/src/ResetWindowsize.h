#pragma once
#include<GLFW/glfw3.h>
class ResetWindowsize
{
public:
	ResetWindowsize() = default;
	//重设视窗的大小，当窗口大小发生改变时视口根据窗口大小的变化做出调整
	//参数说明：window存的是GLFWwindow的指针，width为初始的窗口宽，height为初始的窗口高（后面这两个值的大小最好与主程序的创建窗口的尺寸一样）
	ResetWindowsize(GLFWwindow* window, int width, int height);
	//自动调整与窗口大小对应的视口
	void Resetsize();
	//获取当前窗口的长/宽的比值，目的用于glm::ortho()，glm::perspective()的参数修正
	//参数说明：args取false时，得出的值为长/宽；取true时，得出的值为宽/长
	float Getspecific(bool args);

	//分别返回窗口的长宽具体数值。
	inline int GetWidth() { return m_lastwidth; }inline int GetHeight() { return m_lastheight; }

	bool m_WindowHide = false;
private:
	GLFWwindow* m_window;
	int m_width, m_height;
	int m_lastwidth = 0, m_lastheight = 0;

	float m_args;
};
