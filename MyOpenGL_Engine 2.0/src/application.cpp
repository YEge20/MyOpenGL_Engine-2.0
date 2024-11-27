#include"Render/RenderControler.h"
#include"timestep.h"
int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//��������Ⱦ���ڵ���֮ǰ����opengl���汾
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);//��������Ⱦ���ڵ���֮ǰ����opengl�ΰ汾
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//��������Ⱦ���ڵ���֮ǰ����glfw_opengl_profile��GLFW_OPENGL_CORE(/COMPAT)_PROFILE��������ģʽ���Ǻ���ģʽ

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1200, 800, "OpenGL_Engine (StudyVersion_2.5.98)", NULL, NULL);
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
    std::cout << "OpenGL and GPUDrive version: " << glGetString(GL_VERSION) << " ready" << std::endl;
    std::cout << "DebugInformation:" << std::endl;
    //����OpenGL�Դ���Ĭ�ϵ�MSAA�����
    glfwInitHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);

    //��ʼ����Ⱦ�����ݣ�
    RenderControler RenderControler(window, AUTO, 9);

    //��ʼ��imgui���ܣ�
    ImguiFunction ImguiFunction(window, 2, CHINESE, 16.5f);

    float time = 0.0f, lasttime = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        time = (float)glfwGetTime();
        timestep timestep = time - lasttime;
        lasttime = time;
        RenderControler.renderContextControl(timestep.GetSecond(), timestep.GetMillSecond());

        //imGUI��Ⱦ��
        ImguiFunction.RunImgui();
        {
            ImGui::Begin("Control Panal:");
            RenderControler.renderImguiContextControl();
            ImGui::End();

            ImGui::Begin("Application status: ");
            ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
            ImGui::Text("GPU Hardware: %s", glGetString(GL_RENDERER));
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Caculate timestep : %.3f s/frame", timestep.GetSecond());
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