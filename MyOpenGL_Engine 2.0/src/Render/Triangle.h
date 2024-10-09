#pragma once
#include<memory>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#include"shader.h"
#include"ImguiFunction.h"
#include"vertexbufferLayout.h"
class Triangle
{
public:
	Triangle(GLFWwindow* window);

	void renderContext();
	void renderImguiContext();
private:
	GLFWwindow* m_window;
	std::shared_ptr<Shader> m_shader;
	std::shared_ptr<Shader> m_shader2;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout;
	std::shared_ptr<vertexbufferlayout> m_vertexbufferlayout2;
};

/*注意:这个简单的三角形使用的智能指针方式与其他的项目不相同
* 例子：m_vertexbufferlayout.reset(new vertexbufferlayout(trianglevertex, TLayout, triangle, triangleLayout));
* 用了 .reset(new <类名>(函数变量1，函数变量2，...))的方式初始化，这样做的好处是不需要再次复制添加一个新的cpp类文件，
*/