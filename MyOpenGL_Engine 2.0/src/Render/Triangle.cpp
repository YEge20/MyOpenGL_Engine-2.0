#include "Triangle.h"

Triangle::Triangle(GLFWwindow* window)
	:m_window(window)
{
    std::cout << "Running Triangle.cpp" << std::endl;
    m_WindowSizeControl.reset(new ResetWindowsize(m_window, 1200, 800));
    m_shader.reset(new Shader(false, "./shader/BasicShader2.shader"));
#define triangle 28
    float trianglevertex[triangle] =
    {
        //vertex:                //color:           
        -260.0f,-260.0f, 0.0f,  1.0f,0.0f,0.0f,1.0f,//0
         260.0f,-260.0f, 0.0f,  0.0f,1.0f,0.0f,1.0f,//1
        -260.0f, 260.0f, 0.0f,  0.0f,0.0f,1.0f,1.0f,//2
         260.0f, 260.0f, 0.0f,  1.0f,1.0f,0.0f,1.0f //3
    };
#define indexOftriangle 2
    int triangleIndex[indexOftriangle] =
    {//vertex:   //color:
        3,          4
    };
#define triangleLayout1 6
    int TLayout[triangleLayout1] =
    {
        0,1,2,
        1,2,3
    };
    m_vertexbufferlayout.reset(new vertexbufferlayout(trianglevertex, TLayout, triangle, triangleLayout1));
    m_vertexbufferlayout->AttribPointer(indexOftriangle, triangleIndex, 7);
}

void Triangle::renderContext(float timestep, float milltimestep)
{
    m_timestep = timestep;
    m_milltimestep = milltimestep;

    float specific = m_WindowSizeControl->Getspecific(false);
    glm::mat4 project = glm::ortho(-400.0f * specific ,400.0f * specific,-400.0f,400.0f,0.0f,1.0f);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_position);
    m_WindowSizeControl->Resetsize();
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_vertexbufferlayout->bind();
    m_shader->bind();
    m_shader->setuniformMat4f("u_MVP", project * translate);
    glDrawElements(GL_TRIANGLES, triangleLayout1, GL_UNSIGNED_INT, nullptr);

    //设置按下esc键后关闭程序：
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
}

void Triangle::renderImguiContext()
{
    ImGui::Text("receive timestep: %.3f s = %.3f ms", m_timestep, m_milltimestep);
    ImGui::Text("This is a simple way to draw two triangles.\nPress Esc to end the program...");
    ImGui::SliderFloat("x", &m_position[0], -20.0f, 20.0f, "%.3f");
}