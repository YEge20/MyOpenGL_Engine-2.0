#include "Triangle.h"

Triangle::Triangle(GLFWwindow* window)
	:m_window(window)
{
    std::cout << "Running Triangle.cpp\n" << std::endl;
    m_shader.reset(new Shader("./sharder/BasicShader.shader"));
    m_shader2.reset(new Shader("./sharder/BasicShader2.shader"));
#define triangle 21
    float trianglevertex[triangle] =
    {
        //vertex:                //color:
        -120.0f,-120.0f, 0.0f,  1.0f,0.5f,0.5f,1.0f, //0
        -120.0f, 120.0f, 0.0f,  0.5f,1.0f,0.5f,1.0f, //1
         120.0f,-120.0f, 0.0f,  0.5f,0.5f,1.0f,1.0f  //2
    };
#define indexOftriangle 2
    int triangleIndex[indexOftriangle] =
    {//vertex:   //color:
        3,          4
    };
#define triangleLayout 3
    int TLayout[triangleLayout] =
    {
        0,1,2,
    };
    m_vertexbufferlayout.reset(new vertexbufferlayout(trianglevertex, TLayout, triangle, triangleLayout));
    m_vertexbufferlayout->AttribPointer(indexOftriangle, triangleIndex, 7);

#define triangle2 21
    float trianglevertex2[triangle2] =
    {
        //vertex:                //color:
         120.0f, 120.0f, 0.0f,  1.0f,1.0f,0.5f,1.0f, //0
        -120.0f, 120.0f, 0.0f,  0.5f,1.0f,0.5f,1.0f, //1
         120.0f,-120.0f, 0.0f,  0.5f,0.5f,1.0f,1.0f  //2
    };
#define indexOftriangle2 2
    int triangleIndex2[indexOftriangle2] =
    {//vertex:   //color:
        3,          4
    };
#define triangleLayout2 6
    int TLayout2[triangleLayout2] =
    {
        0,1,2,
    };
    m_vertexbufferlayout2.reset(new vertexbufferlayout(trianglevertex2, TLayout2, triangle2, triangleLayout2));
    m_vertexbufferlayout2->AttribPointer(indexOftriangle2, triangleIndex2, 7);
}

void Triangle::renderContext()
{
    glm::mat4 project = glm::ortho(-600.0f,600.0f,-400.0f,400.0f,0.0f,1.0f);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_vertexbufferlayout->VAOid());
    m_shader->bind();
    m_shader->setuniformMat4f("u_MVP", project);
    glDrawElements(GL_TRIANGLES, triangleLayout, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(m_vertexbufferlayout2->VAOid());
    m_shader2->bind();
    m_shader2->setuniformMat4f("u_MVP", project);
    glDrawElements(GL_TRIANGLES, triangleLayout2, GL_UNSIGNED_INT, nullptr);
}

void Triangle::renderImguiContext()
{
    ImGui::Text("This is a simple way to draw two triangle...");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}