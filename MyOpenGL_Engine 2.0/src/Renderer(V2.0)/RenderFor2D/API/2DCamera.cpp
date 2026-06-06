#include"2DCamera.h"

CameraFor2D::CameraFor2D(GLFWwindow* window, int Window_width, int Window_height, float far_plaen, float z_Position)
	:m_width(Window_width),m_height(Window_height),m_window(window),m_FarPlane(far_plaen)
{
	m_CameraPos.z = z_Position;
}

void CameraFor2D::ControlCamera(float speed)
{
	glm::vec3 result = m_CameraPos;
	float scale_speed = 0.5f * m_scale;
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		result += speed * scale_speed * glm::vec3(0.0f, 1.0f, 0.0f);
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		result -= speed * scale_speed * glm::vec3(0.0f, 1.0f, 0.0f);
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		result -= speed * scale_speed * glm::vec3(1.0f, 0.0f, 0.0f);
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		result += speed * scale_speed * glm::vec3(1.0f, 0.0f, 0.0f);
	
	if (result != m_CameraPos)
	{
		m_CameraPos = result;
		ReCaculateProject();
	}
}

void CameraFor2D::Modifile_Scale(float scale)
{
	if (scale <= -1.0f)
		m_scale = 0.01f;
	else
		m_scale = 1.0 + scale;
	ReCaculateProject();
}

void CameraFor2D::Modifile_ortho(int X, int Y)
{
	if(m_width != X || m_height != Y)
	{
		m_width = X;
		m_height = Y;
		ReCaculateProject();
	}
}

void CameraFor2D::ReCaculateProject()
{
	float aspect = (float)m_width / (float)m_height;
	float height_size = m_scale * 0.5f;
	glm::mat4 Camera_Proj = glm::ortho(-height_size * aspect, height_size * aspect, -height_size, height_size, 0.1f, m_FarPlane);
	glm::mat4 Camera_Translae = glm::inverse(glm::translate(glm::mat4(1.0f), m_CameraPos));
	m_Camera_Proj = Camera_Proj * Camera_Translae;
}
