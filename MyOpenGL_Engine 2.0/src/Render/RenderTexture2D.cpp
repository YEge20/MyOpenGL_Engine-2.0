#include"RenderTexture2D.h"

//对象缓存设定：
#define DataBuffer 80
float vertex[DataBuffer] =
{  //vertext:              texture:       color:                textureindex:
   -60.0f, -60.0f, 0.0f,   0.0f,0.0f,     0.0f,0.0f,0.0f,0.0f,        0.0f,//0
   -60.0f,  60.0f, 0.0f,   0.0f,1.0f,     0.0f,0.0f,0.0f,0.0f,        0.0f,//1
    60.0f, -60.0f, 0.0f,   1.0f,0.0f,     0.0f,0.0f,0.0f,0.0f,        0.0f,//2
    60.0f,  60.0f, 0.0f,   1.0f,1.0f,     0.0f,0.0f,0.0f,0.0f,        0.0f,//3

   -10.0f, -10.0f, 0.0f,   0.0f,0.0f,     0.0f,0.0f,0.0f,0.0f,        1.0f,//4
   -10.0f,  10.0f, 0.0f,   0.0f,1.0f,     0.0f,0.0f,0.0f,0.0f,        1.0f,//5
    10.0f, -10.0f, 0.0f,   1.0f,0.0f,     0.0f,0.0f,0.0f,0.0f,        1.0f,//6
    10.0f,  10.0f, 0.0f,   1.0f,1.0f,     0.0f,0.0f,0.0f,0.0f,        1.0f //7
};
#define CountOfIndex 4
int DataBufferSize[CountOfIndex] =
{  //VertexSize:      TextureSize:        ColorSize:           TextureindexSize:
               3,                2,               4,                          1
};
#define LayoutNumber 12
unsigned int layout[LayoutNumber] =
{
    0,1,2,
    1,2,3,

    4,5,6,
    5,6,7
};
RenderTexture2D::RenderTexture2D(GLFWwindow* window)
    :m_window(window), m_gravity(false),m_quake_switch(true),
    m_project2(glm::ortho(0.0f, 480.0f, 0.0f, 320.0f, 0.0f, 200.0f)),
    m_layoutObject1(240.0f, 160.0f, 0.0f),
    m_camera(glm::vec3(0.0f, 0.0f, 0.0f)),
    m_light{0.0f}, m_rota(0.0f),m_XY{0.0f},m_time(0)
{    
    std::cout << "Running 2D system\n" << std::endl;
    m_shader.reset(new Shader("./shader/RenderTexture2D/ComplexShaderFor2D.shader"));
    m_shader1.reset(new Shader("./shader/RenderTexture2D/BasicShader.shader"));

 //背景缓存设置：
#define background 28
    float backgroundvertex[background] =
    {
        //vertex:                //color:
        -300.0f, -300.0f, 0.0f,  1.0f,0.0f,0.5f,1.0f, //0
        -300.0f,  300.0f, 0.0f,  0.0f,0.3f,0.7f,1.0f, //1
         300.0f, -300.0f, 0.0f,  0.7f,0.0f,0.2f,1.0f, //2
         300.0f,  300.0f, 0.0f,  0.0f,0.5f,1.0f,1.0f, //3
    };
#define indexOfBackground 2
    int backgroundIndex[indexOfBackground] =
    {//vertex:   //color:
        3,          4
    };
#define backgroundLayout 6
    int BLayout[backgroundLayout] =
    {
        0,1,2,
        1,2,3
    };
    m_vertexLayout.reset(new vertexbufferlayout(backgroundvertex, BLayout, background, backgroundLayout));
    m_vertexLayout->AttribPointer(indexOfBackground, backgroundIndex, 7);
 //顶点的设置（使用动态绑定进行初始化）：
    m_dynamicLayout.reset(new DynamicVertexbufferLayout(layout, DataBuffer, LayoutNumber));
    m_dynamicLayout->AttribPointer(CountOfIndex,DataBufferSize,10);    
//材质的设置：
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    m_texture = std::make_unique<texture32>(false);
    m_texture->importTexture("./texture/grass_block_side.png",0);
    m_texture->importTexture("./texture/heart.png", 1);
    m_texture->importTexture("./texture/blueheart.png", 2);
    m_texture->bind(0, 0);
    m_texture->bind(1, 1);

    m_keyboard = std::make_unique<KeyControlFunction>(m_window);
}

void RenderTexture2D::renderContext(float timestep, float milltimestep)
{
    glClear(GL_COLOR_BUFFER_BIT);
//渲染背景：
    m_shader1->bind();
    glBindVertexArray(m_vertexLayout->VAOid());

    glm::mat4 model = glm::translate(glm::mat4(1.0f),m_layoutObject1);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), m_camera);
    glm::mat4 MVP0 = m_project2 * view * model;
    m_shader1->setuniformMat4f("u_MVP", MVP0);
    glDrawElements(GL_TRIANGLES, backgroundLayout, GL_UNSIGNED_INT, nullptr);

//渲染对象
    m_shader->bind();
    glBindVertexArray(m_dynamicLayout->VAOid());
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex), vertex);//采取动态模式进行修改缓冲区
    //键盘按键控制：
    if (glfwGetKey(m_window, GLFW_KEY_G) == GLFW_PRESS && m_gravity == false)
    {
        m_gravity = true;
        std::cout << "[G Press]:change to GL_Texture2" << std::endl;
        m_texture->bind(1, 2);
    }
    if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS && m_gravity == true)
    {
        m_gravity = false;
        std::cout << "[F Press]:change to GL_Texture1" << std::endl;
        m_texture->bind(1, 1);
    }
    m_keyboard->KeyUp_Down_Left_Right(&m_XY[1], &m_XY[0], 0.25f);
    for (int i = 4; i <= 7; i++)
    {
        vertex[10 * i] += m_XY[0];
        vertex[10 * i + 1] += m_XY[1];
    }
    m_XY[0] = m_XY[1] = 0.0f;
    if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS && m_quake_switch == true)
    {
        m_time = 30.0f;
        std::cout << "[Q Press]: Camera quake!" << std::endl;
        m_quake_switch = false;
    }
    m_time--;
    if (m_time <= 0.0f)
    {
        m_time = 0.0f;
        m_quake_switch = true;
    }

    int array[2] = { 0,1 };
    m_shader->setuniform1iv("u_texture2", 2, array);
    glm::mat4 rotaFinal = glm::rotate(glm::mat4(1.0f), glm::radians(m_rota), glm::vec3(0.0f, 0.0f, 1.0f));//旋转功能
    glm::mat4 model1 = glm::translate(glm::mat4(1.0f), m_layoutObject1);
    glm::mat4 view1 = glm::translate(glm::mat4(1.0f), m_camera);
    glm::mat4 CameraQuake = glm::translate(glm::mat4(1.0f),glm::vec3(3.5f * sin(m_time), 3.5f * sin(m_time), 0.0f));
    glm::mat4 MVP1 = m_project2 * view1 * CameraQuake * model1 * rotaFinal;
    m_shader->setuniformMat4f("u_MVP1", MVP1);
    m_shader->setuniformVEC4("u_changecolor", m_light[0], m_light[1], m_light[2], 1.0f);
    glDrawElements(GL_TRIANGLES, LayoutNumber, GL_UNSIGNED_INT, nullptr);

}

void RenderTexture2D::renderImguiContext()
{
    ImGui::SliderFloat2("camera position:", &m_camera.x, -140.0f, 140.0f);
    if (ImGui::Button("reset camera to (0,0)"))
        m_camera = { 0.0f,0.0f,0.0f };
    ImGui::SliderFloat("rotate", &m_rota, -90.0f, 90.0f);
    if (ImGui::Button("reset rotate"))
        m_rota = 0.0f;
    ImGui::ColorEdit3("ObjectColor change:", m_light);
    ImGui::Text("X:%.2f,Y:%.2f",vertex[40]+10,vertex[41]+10);
}
