#include"Render/RenderControler.h"

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//��������Ⱦ���ڵ���֮ǰ����opengl���汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//��������Ⱦ���ڵ���֮ǰ����opengl�ΰ汾
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//��������Ⱦ���ڵ���֮ǰ����glfw_opengl_profile��GLFW_OPENGL_CORE(/COMPAT)_PROFILE��������ģʽ���Ǻ���ģʽ
        

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

    //��ʼ��imgui���ܣ�
    ImguiFunction ImguiFunction(window,2);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        RenderControler.renderContextControl();

        //imGUI��Ⱦ��
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