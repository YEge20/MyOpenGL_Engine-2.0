#pragma once
#include"imGUI/imgui.h"
#include"imGUI/imgui_impl_glfw.h"
#include"imGUI/imgui_impl_opengl3.h"
class ImguiFunction
{
public:
	ImguiFunction(GLFWwindow* windows, int x);
	~ImguiFunction();

	void RunImgui();
	void updateImgui();

private:

};