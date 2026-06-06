#pragma once
#include <glm/glm.hpp>
#include "../Renderer(V2.0)/RenderFor2D/API/2DCamera.h"
namespace Utils {
	//把鼠标的坐标从glfw窗口坐标转移到opengl的坐标中
	static glm::vec3 WindowPos_to_WorldPos(const glm::vec2& Mouse_WindowPos, int WindowWidth, int WindowHeight, CameraFor2D Camera)
	{
		float Width = (float)WindowWidth;
		float Height = (float)WindowHeight;

		glm::vec2 Zero = glm::vec2(Width / 2.0f, Height / 2.0f);
		glm::vec2 Bias = Mouse_WindowPos - Zero;
		Bias.x = Bias.x / (Width * 0.5f);
		Bias.y = -Bias.y / (Height * 0.5f);

		float aspect = Width / Height;
		float val = Camera.GetCameraScale() * 0.5f;
		Bias *= glm::vec2(aspect * val, val);

		glm::vec3 Result = Camera.GetCameraPosition() + glm::vec3(Bias, 1.0f);
		return Result;
	}

	//检查矩形物体是否被鼠标拾取
	//参数说明:Mouse_WorldPos鼠标的世界坐标;Object_WorldPos物体的世界坐标;Object_Size物体的尺寸;Object_ZRota物体当前的沿Z轴旋转的弧度值,如果物体不会旋转设置为0
	static bool IsSquareObject_Picked(const glm::vec3& Mouse_WorldPos, const glm::vec3& Object_WorldPos, const glm::vec2& Object_Size, float Object_ZRota = 0)
	{
		glm::vec4 Mouse_WorldPos_Relative_to_ObjectPos = glm::vec4(Mouse_WorldPos - Object_WorldPos, 1.0f);
		glm::vec3 Mouse_World_to_ModelLocal = glm::rotate(glm::mat4(1.0f), Object_ZRota, glm::vec3(0.0f, 0.0f, 1.0f)) * Mouse_WorldPos_Relative_to_ObjectPos;
		glm::vec2 Max = 0.5f * Object_Size;
		glm::vec2 Min = -0.5f * Object_Size;
		if ((Mouse_World_to_ModelLocal.x < Max.x && Mouse_World_to_ModelLocal.x > Min.x)
			&& (Mouse_World_to_ModelLocal.y < Max.y && Mouse_World_to_ModelLocal.y > Min.y))
			return true;
		else
			return false;
	}
}