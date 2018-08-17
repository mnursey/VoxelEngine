#pragma once
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

class RenderObject {
private:
	IndexBuffer* indexBuffer;
	VertexArray* vertexArray;
	VertexBuffer* vertexBuffer;
	int vertexCount;

public:
	RenderObject(VertexArray*& va, VertexBuffer*& vb, int vC);
	RenderObject(VertexArray*& va, VertexBuffer*& vb, IndexBuffer*& ib, int vC);
	~RenderObject();

	void GetRenderObjects(VertexArray*& va, int& vC);
	void GetRenderObjects(VertexArray*& va, VertexBuffer*& vb, IndexBuffer*& ib, int& vC);
};