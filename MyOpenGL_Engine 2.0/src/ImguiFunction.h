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
	/*��ʼ��imgui���ܣ�windows�Ǵ���ָ�룻x��imgui���ڵķ��xȡֵ1~3������, languageΪ��Ҫ���������Ĭ��ΪENGLISH, fontSizeΪ����Ĵ�СĬ��15.5
	ע��:
	������ʼ����language�����ĺ���ʾ���ĵ�ʵ����ImGui::Text(u8"���");
	�����ENGLISH����Ҫ�ӡ�u8��!
	���飺
	�����ѡ����������Ϊ�����ԣ�������������С��Ϊ17.5���ܻ���ã�Ӣ��Ĭ�ϾͿ�����*/
	ImguiFunction(GLFWwindow* windows, int x, FontLanguage language = ENGLISH, float fontSize = 15.5f);
	~ImguiFunction();

	void RunImgui();
	void updateImgui();

private:
	ImFont* m_font;
	FontLanguage m_fontLang;
};