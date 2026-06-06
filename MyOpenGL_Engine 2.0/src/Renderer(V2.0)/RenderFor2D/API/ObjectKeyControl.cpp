#include "ObjectKeyControl.h"

KeyControl::KeyControl(GLFWwindow* window)
	:m_window(window)
{
}

void KeyControl::ObjectPosChange(glm::vec3* Obj_Pos, float speed, bool enable)
{
	if (enable == true)
	{
		if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
			*Obj_Pos += speed * glm::vec3(0.0f, 1.0f, 0.0f);
		if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
			*Obj_Pos -= speed * glm::vec3(0.0f, 1.0f, 0.0f);
		if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			*Obj_Pos += speed * glm::vec3(1.0f, 0.0f, 0.0f);
		if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
			*Obj_Pos -= speed * glm::vec3(1.0f, 0.0f, 0.0f);
	}
}
