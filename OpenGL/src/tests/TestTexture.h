#pragma once

#include <algorithm>
#include "Test.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	class TestTexture : public Test
	{
	private:
		Renderer * renderer;
		Shader* shader;
		VertexArray* va;
		VertexBuffer* vb;
		IndexBuffer* ib;
		Texture* texture;
		VertexBufferLayout* layout;

		glm::mat4 proj;
		glm::mat4 view;
		glm::vec3 translation;
		float rotation;


		unsigned int indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		float positions[16] = {
			-50.0f,	-50.0f, 0.0f, 0.0f, // 0
			50.0f,	-50.0f, 1.0f, 0.0f, // 1
			50.0f,	50.0f,	1.0f, 1.0f, // 2
			-50.0f,	50.0f,	0.0f, 1.0f  // 3
		};

	public:
		TestTexture();
		~TestTexture();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}