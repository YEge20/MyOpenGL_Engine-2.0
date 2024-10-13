#include "Triangle.h"

Triangle::Triangle(GLFWwindow* window)
	:m_window(window)
{
    std::cout << "Running Triangle.cpp\n" << std::endl;
    m_shader.reset(new Shader("./sharder/BasicShader2.shader"));
#define triangle 28
    float trianglevertex[triangle] =
    {
        //vertex:                //color:           
        -260.0f,-260.0f, 0.0f,  1.0f,0.2f,0.2f,1.0f,//0
         260.0f,-260.0f, 0.0f,  0.2f,1.0f,0.2f,1.0f,//1
        -260.0f, 260.0f, 0.0f,  0.2f,0.2f,1.0f,1.0f,//2
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

void Triangle::renderContext()
{
    glm::mat4 project = glm::ortho(-600.0f,600.0f,-400.0f,400.0f,0.0f,1.0f);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_vertexbufferlayout->VAOid());
    m_shader->bind();
    m_shader->setuniformMat4f("u_MVP", project);
    glDrawElements(GL_TRIANGLES, triangleLayout1, GL_UNSIGNED_INT, nullptr);}

void Triangle::renderImguiContext()
{
    ImGui::Text("This is a simple way to draw two triangle...");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}