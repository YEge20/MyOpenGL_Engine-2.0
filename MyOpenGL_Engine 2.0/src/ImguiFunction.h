#pragma once
#include"imGUI/imgui.h"
#include"imGUI/imgui_impl_glfw.h"
#include"imGUI/imgui_impl_opengl3.h"
enum FontLanguage
{
	ENGLISH = 0, CHINESE
};
class ImguiFunction
{
public:
	/*初始化imgui功能，windows是窗口指针；x是imgui窗口的风格x取值1~3的整数, language为主要字体的语言默认为ENGLISH, fontSize为字体的大小默认15.5
	注意:
	如果你初始化后language是中文后显示中文的实例：ImGui::Text(u8"你好");
	如果是ENGLISH则不需要加“u8”!
	建议：
	如果你选择了中文作为主语言，建议你的字体大小设为17.5可能会更好，英语默认就可以了*/
	ImguiFunction(GLFWwindow* windows, int x, FontLanguage language = ENGLISH, float fontSize = 15.5f);
	~ImguiFunction();

	void RunImgui();
	void updateImgui();

private:
	ImFont* m_font;
	FontLanguage m_fontLang;
};