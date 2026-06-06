#include"RenderTexture2D.h"

namespace Utils {
    static unsigned int BITCaculate(unsigned int x)
    {
        return 1 << x;
    }
    static unsigned int BITCountCaculate(unsigned int x)
    {
        if (x <= 8)
            return BITCaculate(x) - 1;
    }
}
#define BIT(x) Utils::BITCaculate(x)
#define BIT_COUNT(x) Utils::BITCountCaculate(x)

RenderTexture2D::RenderTexture2D(GLFWwindow* window)
    :m_window(window)
{    
    std::cout << "Running RenderTexture2D.cpp" << std::endl;
    m_Camera.reset(new CameraFor2D(m_window, 1200, 800));
    m_WindowSizeControler.reset(new ResetWindowsize(m_window, 1200, 800));

    m_SquareShader.reset(new Shader(false, "./shader/RenderTexture2D/ComplexShaderFor2D.shader"));
    m_stencilShader.reset(new Shader(false, "./shader/RenderTexture2D/StencilShader.shader"));

    m_FlowerTexture.reset(new Texture_2D("./texture/ground/poppy.png", false));
    m_Texture.reset(new Texture_2D("./texture/crafttable/oak_planks.png",false));

    m_Square1.reset(new DrawSquare2D(10.0f, 10.0f, 0.0f));
    m_Flower.reset(new DrawSquare2D(5.0f, 5.0f, 0.0f));

    m_KeyControlr.reset(new KeyControl(m_window));
    //3D渲染必须启动深度测试否侧渲染过程不正确：
    glEnable(GL_DEPTH_TEST);
    //启用模板测试
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilMask(0xFF);
}

void RenderTexture2D::renderContext(float timestep, float milltimestep)
{
    m_WindowSizeControler->Resetsize();

    m_Camera->Modifile_ortho(m_WindowSizeControler->GetWidth(), m_WindowSizeControler->GetHeight());
    m_Camera->Modifile_Scale(m_scale);
    m_Camera->ControlCamera(timestep * 5.0f);

    m_KeyControlr->ObjectPosChange(&m_FlowerPos, 30.0f * timestep);

    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
    glClearStencil(0);//这里默认清除的模板值设为0
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glStencilFunc(GL_ALWAYS, 1, BIT_COUNT(8));//模板测试总是通过，由于掩码值是0x0f,则0&0x0f = 0,那该模板值填充为0
    m_testSquareTexture(m_Camera->GetCameraMatrix());

    glStencilFunc(GL_ALWAYS, 0, BIT_COUNT(8));//原理同上，但是此处模板值填充1
    m_testFlowerTexture(m_Camera->GetCameraMatrix());

    glStencilFunc(GL_EQUAL, 1, BIT_COUNT(8));//模板测试比较方式设为(0xFF & current_stencil) >= (0xFF & ref(0)),如果通过则填充为0
    //一定要关闭深度测试，因为glStencilOp设置了深度测试失败后不操作模板，这意味着该片段会直接在深度测试中被丢弃，
    //暂时关闭深度测试，那么该片段会完全由模板测试决定
    glDisable(GL_DEPTH_TEST);
    m_testFlowerTextureStencilTest(m_Camera->GetCameraMatrix());
    glEnable(GL_DEPTH_TEST);
}

void RenderTexture2D::renderImguiContext()
{
    ImGui::SliderFloat(u8"相机缩放", &m_scale, 1.0f, 50.0f, "%.2f");
    ImGui::SliderFloat(u8"花的z值", &m_FlowerPos.z, -5.0f, 5.0f, "%.2f");
    ImGui::Text(u8"花朵的坐标(x:%.2f, y:%.2f, z:%.2f)", m_FlowerPos.x, m_FlowerPos.y, m_FlowerPos.z);
    ImGui::Text(u8"相机的坐标(x:%.2f, y:%.2f)", m_Camera->GetCameraPosition().x, m_Camera->GetCameraPosition().y);
}

void RenderTexture2D::m_testSquareTexture(glm::mat4 Cam_proj)
{
    m_SquareShader->bind();
    m_Texture->Bind(0);
    m_SquareShader->setuniform1i("u_texture", 0);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_Square_Pos);
    glm::mat4 MVP = Cam_proj * translate;
    m_SquareShader->setuniformMat4f("u_MVP", MVP);
    m_Square1->DrawCall();
}

void RenderTexture2D::m_testFlowerTexture(glm::mat4 Cam_proj)
{
    m_SquareShader->bind();
    m_FlowerTexture->Bind(0);
    m_SquareShader->setuniform1i("u_texture", 0);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_FlowerPos);
    glm::mat4 MVP = Cam_proj * translate;
    m_SquareShader->setuniformMat4f("u_MVP", MVP);
    m_Flower->DrawCall();
}

void RenderTexture2D::m_testFlowerTextureStencilTest(glm::mat4 Cam_proj)
{
    m_stencilShader->bind();
    m_FlowerTexture->Bind(0);
    m_stencilShader->setuniform1i("u_texture", 0);
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_FlowerPos);
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.1f, 1.1f, 1.0f));
    glm::mat4 MVP = Cam_proj * translate * scale;
    m_stencilShader->setuniformMat4f("u_MVP", MVP);
    m_Flower->DrawCall();
}
