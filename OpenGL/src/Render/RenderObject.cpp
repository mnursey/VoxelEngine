#include "RenderObject.h"

RenderObject::RenderObject(VertexArray*& va, VertexBuffer*& vb, int vC)
{
	vertexArray = va;
	vertexBuffer = vb;
	vertexCount = vC;
}

RenderObject::RenderObject(VertexArray*& va, VertexBuffer*& vb, IndexBuffer*& ib, int vC)
{
	vertexArray = va;
	vertexBuffer = vb;
	indexBuffer = ib;
	vertexCount = vC;
}

RenderObject::~RenderObject()
{
	delete vertexBuffer;
	delete vertexArray;
	delete indexBuffer;
}

void RenderObject::GetRenderObjects(VertexArray*& va, int& vC)
{
	va = vertexArray;
	vC = vertexCount;
}

void RenderObject::GetRenderObjects(VertexArray*& va, VertexBuffer*& vb, IndexBuffer*& ib, int& vC)
{
	va = vertexArray;
	vb = vertexBuffer;
	ib = indexBuffer;
	vC = vertexCount;
}
