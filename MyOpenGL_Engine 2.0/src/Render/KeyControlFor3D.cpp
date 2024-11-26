#include"Render/KeyControlFor3D.h"
float yaw = -90.0f, pitch = 0.0f;//设置初始的巡航角度和俯视角
float lastX = 480.0f, lasty = 320.0f, fov;
bool checkFirstCursor = false;
glm::vec3 front1;
KeyControlFor3D::KeyControlFor3D(GLFWwindow* window, bool CameraViewSetup, bool MousescrollSetup)
	:m_window(window),m_CameraViewSetup(CameraViewSetup),m_MouseScroll(MousescrollSetup)
{
	void mousecallback(GLFWwindow * window, double xpos, double ypos);
	void mousescroll(GLFWwindow * window, double xoffset, double yoffset);
	if (m_CameraViewSetup == true)
		glfwSetCursorPosCallback(m_window, mousecallback);//光标移动回调函数
	if (m_MouseScroll == true)
		glfwSetScrollCallback(m_window, mousescroll);//鼠标滚轮回调函数
}

KeyControlFor3D::~KeyControlFor3D()
{
}

glm::mat4 KeyControlFor3D::CameraMove(glm::vec3* Position, glm::vec3* Front, glm::vec3* Up, float speed)
{
	if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_window, true);
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
		*Position += speed * *Front;
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
		*Position -= speed * *Front;
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
		*Position += speed * glm::normalize(glm::cross(*Up, *Front));
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
		*Position -= speed * glm::normalize(glm::cross(*Up, *Front));
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		*Position -= speed * *Up;
	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		*Position += speed * *Up;
	if (m_CameraViewSetup == true)//摄像机的自由视线开关设置
	{
		if (glfwGetKey(m_window, GLFW_KEY_F1) == GLFW_PRESS && checkFirstCursor == false)
		{
			std::cout << "[F1 Press]:camera mode free" << std::endl;
			checkFirstCursor = true;
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//设置光标模式隐藏并且让光标始终在窗口中央

		}
		if (glfwGetKey(m_window, GLFW_KEY_F2) == GLFW_PRESS && checkFirstCursor == true)
		{
			std::cout << "[F2 Press]:camera mode static" << std::endl;
			checkFirstCursor = false;
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);//设置光标模式显示并且让光标可以离开窗口
		}
		*Front = front1;
	}
	glm::mat4 camera = glm::lookAt(*Position, *Front + *Position, *Up);
	m_position = *Position;
	m_Front = *Front + *Position;
	return camera;
}
float KeyControlFor3D::MousescrollFunction()
{
	return fov;
}

//鼠标的回调函数，给glfwSetCursorPosCallback()设置功能使用,并实现自由移动视线的功能
void mousecallback(GLFWwindow* window, double xpos,double ypos)
{
	if (!checkFirstCursor)//控制该功能的使用
	{
		lastX = (float)xpos;
		lasty = (float)ypos;
	}
	float Xoffset = (float)xpos - lastX;
	float Yoffset = (float)ypos - lasty;
	lastX = (float)xpos;
	lasty = (float)ypos;
	const float sensitivy = 0.085f;
	Xoffset *= sensitivy;
	Yoffset *= sensitivy;

	yaw += Xoffset;
	pitch += Yoffset;
	if (pitch > 89.9f)
		pitch = 89.9f;
	if (pitch < -89.9f)
		pitch = -89.9f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(-pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front1 = glm::normalize(direction);
}
//滚轮的回调函数：
void mousescroll(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset * 1.25f;
	if (fov < -20.0f)
		fov = -20.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}