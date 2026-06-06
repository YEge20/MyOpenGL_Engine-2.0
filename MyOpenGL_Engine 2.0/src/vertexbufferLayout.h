#pragma once
//此API用于设置顶点属性
class vertexbufferlayout
{
public:
	//初始化程序,导入相关的数组以及参数
	//参数说明：data为你的顶点数据的数组;layout为顶点放置的序号数组;DataBuffer为顶点数据数组的大小;LayoutNumber为顶点放置的序号数组的大小
	vertexbufferlayout(const void* data, const void* layout, const int DataBuffer, const int LayoutNumber);
	~vertexbufferlayout();

	//绑定该顶点数组
	void bind();
	//解绑该顶点数组
	void unbind();
	//声明顶点的属性
	//参数说明：CountOfIndex是顶点属性数组里面数字的个数，DataBufferSize是顶点属性数组，stride是一个顶点全部的属性(坐标+法线+颜色...)的长度
	void AttribPointer(const unsigned int CountOfIndex, const int* DataBufferSize, const int stride);
	unsigned int VAOid();
private:
	unsigned int m_vao,m_vbo,m_offset;
};
