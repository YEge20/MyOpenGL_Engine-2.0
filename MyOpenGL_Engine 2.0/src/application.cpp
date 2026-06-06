#include<GL/glew.h>
#include"Render/RenderControler.h"
#include"2DPhysicSimulation/PhysicScene.h"
#include"timestep.h"

enum class RUNMODE
{
    NONE = 0, RENDERER, PHYSICRENDERE
};

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//必须在渲染窗口弹出之前设置opengl主版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);//必须在渲染窗口弹出之前设置opengl次版本
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//必须在渲染窗口弹出之前设置glfw_opengl_profile的GLFW_OPENGL_CORE(/COMPAT)_PROFILE，即兼容模式还是核心模式

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1200, 800, "OpenGL_Engine(StudyVersion_2.7)", NULL, NULL);
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
    int MaxUBOSize = 0;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &MaxUBOSize);
    std::cout << "OpenGL and GPUDrive version: " << glGetString(GL_VERSION) << " ready" << std::endl;
    std::cout << "Max UBO block size : " << MaxUBOSize << std::endl;
    std::cout << "DebugInformation:" << std::endl;
    //启用GLFW自带的默认的MSAA抗锯齿
    glfwWindowHint(GLFW_SAMPLES, 4);
    glEnable(GL_MULTISAMPLE);
    //设置混合：
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // 设置线条的粗细
    glLineWidth(2.0f);

    //运行模式控制
#ifdef YE_RELEASE
    RUNMODE mode = RUNMODE::NONE;
    RenderControler Render;
    PhysicRenderer Physic;
    char Command;
    std::cout << "please enter runmode (r = RENDERER / p = PHYSICRENDERER):";
    scanf_s("%c", &Command);
    if (Command == 'r' || Command == 'R')
        mode = RUNMODE::RENDERER;
    else if (Command == 'p' || Command == 'P')
        mode = RUNMODE::PHYSICRENDERE;
    
    //初始化渲染的内容：
    if (mode == RUNMODE::RENDERER)
        Render = RenderControler(window, MYSELF, 0);
    else if (mode == RUNMODE::PHYSICRENDERE)
        Physic = PhysicRenderer(window, 1);
    else
    {
        std::cout << "Unknow Run mode ?" << std::endl;
        glfwTerminate();
        return 0;
    }
#else
    RUNMODE mode = RUNMODE::RENDERER;
    RenderControler Render;
    PhysicRenderer Physic;
    //初始化渲染的内容：
    if (mode == RUNMODE::RENDERER)
        Render = RenderControler(window, AUTO, 9);
    else
        Physic = PhysicRenderer(window, 1);
#endif // YE_RELEASE


    //初始化imgui功能：
    ImguiFunction ImguiFunction(window, 2, CHINESE, 16.5f);
    float time = 0.0f, lasttime = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        time = (float)glfwGetTime();
        timestep step = time - lasttime;
        lasttime = time;

        if (mode == RUNMODE::RENDERER)
            Render.renderContextControl(step.GetSecond(), step.GetMillSecond());
        else
            Physic.PhysicUpData(step.GetSecond());

        //imGUI渲染：
        ImguiFunction.RunImgui();
        {
            ImGui::Begin("Control Panal:");
            if (mode == RUNMODE::RENDERER)
                Render.renderImguiContextControl();
            else
                Physic.ImguiUpData();
            ImGui::End();

            ImGui::Begin("Application status: ");
            ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
            ImGui::Text("GPU Hardware: %s", glGetString(GL_RENDERER));
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Caculate timestep : %.3f s/frame", step.GetSecond());
            ImGui::End();
        }
        ImguiFunction.updateImgui();
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    if (mode == RUNMODE::PHYSICRENDERE)
        Physic.DeletePhysicScene();

    glfwTerminate();
    return 0;
}