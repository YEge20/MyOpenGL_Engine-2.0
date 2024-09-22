#include"Render/RenderControler.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//必须在渲染窗口弹出之前设置opengl主版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//必须在渲染窗口弹出之前设置opengl次版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//必须在渲染窗口弹出之前设置glfw_opengl_profile的GLFW_OPENGL_CORE(/COMPAT)_PROFILE，即兼容模式还是核心模式
        

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1200, 800, "OpenGL_Engine (StudyVersion_2.5.3)", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "glew_lib error!"<<std::endl;
    else
        std::cout << "glew_lib ok!"<<std::endl;
    std::cout << "OpenGL and GPUDrive version: " << glGetString(GL_VERSION) << " ready\n" << "DebugInformation:" << std::endl;

    RenderControler RenderControler(window, AUTO, 6);

    //初始化imgui功能：
    ImguiFunction ImguiFunction(window,2);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        RenderControler.renderContextControl();

        //imGUI渲染：
        ImguiFunction.RunImgui();
        {
            ImGui::Begin("version 2.0 :");
            RenderControler.renderImguiContextControl();
            ImGui::End();
        }
        ImguiFunction.updateImgui();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}