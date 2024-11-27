#include"ImguiFunction.h"

ImguiFunction::ImguiFunction(GLFWwindow* windows, int x ,FontLanguage language, float fontSize)
    :m_font(nullptr),m_fontLang(language)
{
    //imGUI初始化设定：
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(windows, true);
    ImGui_ImplOpenGL3_Init();

    if (m_fontLang == CHINESE)
        m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("./fontTTFfile/STHUPO.TTF", fontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesChineseFull());
    else if (m_fontLang == ENGLISH)
        m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF("./fontTTFfile/arialbd.ttf", fontSize, NULL, ImGui::GetIO().Fonts->GetGlyphRangesDefault());

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