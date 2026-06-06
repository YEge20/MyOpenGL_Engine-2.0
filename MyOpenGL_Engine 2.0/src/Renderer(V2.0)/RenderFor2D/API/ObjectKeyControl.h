#pragma once
#include<GLFW/glfw3.h>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

class KeyControl
{
public:
	KeyControl(GLFWwindow* window);

	//方向键控制二维坐标函数，参数说明：Obj_Pos为你想要修改的对象坐标，speed时移动速度，enable是控制使能端默认为true
	virtual void ObjectPosChange(glm::vec3* Obj_Pos, float speed, bool enable = true);
private:
	GLFWwindow* m_window;
};