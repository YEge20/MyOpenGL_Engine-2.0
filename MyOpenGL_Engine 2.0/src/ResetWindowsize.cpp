#include "ResetWindowsize.h"
#include<iostream>

ResetWindowsize::ResetWindowsize(GLFWwindow* window, int width, int height)
	:m_window(window),m_width(width),m_height(height)
{
	m_args = (float)m_width / (float)m_height;
}

void ResetWindowsize::Resetsize()
{
	glfwGetWindowSize(m_window,&m_width,&m_height);
	if (m_lastwidth != m_width || m_lastheight != m_height)
	{
		if (m_width <= 0 || m_height <= 0)
		{
			return;
			m_WindowHide = true;
		}
		m_WindowHide = false;
		m_lastwidth = m_width;
		m_lastheight = m_height;
		glViewport(0, 0, m_lastwidth, m_lastheight);
		std::cout << "[ResetWindowSize]: 窗口大小改为: " << m_width << " x " << m_height << std::endl;
	}
}

float ResetWindowsize::Getspecific(bool args)
{
	glfwGetWindowSize(m_window, &m_width, &m_height);
	m_args = (float)m_width / (float)m_height;
	if (args == false)
		return m_args;
	else
		return 1 / m_args;
}
