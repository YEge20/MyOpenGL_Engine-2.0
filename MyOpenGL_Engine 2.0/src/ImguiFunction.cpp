#include"ImguiFunction.h"

ImguiFunction::ImguiFunction(GLFWwindow* windows, int x)
{

    //imGUI初始化设定：
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(windows, true);
    ImGui_ImplOpenGL3_Init();
    switch (x)
    {
    case 1: ImGui::StyleColorsDark(); break;
    case 2: ImGui::StyleColorsClassic(); break;
    case 3: ImGui::StyleColorsLight(); break;
    default:
        ImGui::StyleColorsDark();
        break;
    }
}

ImguiFunction::~ImguiFunction()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImguiFunction::RunImgui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

void ImguiFunction::updateImgui()
{
    //imGUI更新帧:
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}