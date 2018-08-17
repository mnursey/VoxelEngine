#pragma once

#include "Test.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "InputManager.h"
#include "Camera.h"
#include "ChunkManager.h"

namespace test {

	class TestVoxel : public Test
	{
	private:
		Renderer* renderer;

		Shader* chunkShader;

		Shader* lightingShader;
		VertexArray* lightingVA;
		VertexBuffer* lightingVB;
		VertexBufferLayout* lightingLayout;

		IndexBuffer* ib;
		Texture* texture;

		Camera camera;
		bool m_lockMouse = false;
		voxelEngine::ChunkManager* chunkManager;
		GLFWwindow * m_window;

		float lightColor[3] = { 1.0f, 1.0f, 1.0f};
		glm::vec3 lightPosition = glm::vec3(-40.0f, 20.0f, -20.0f);

		InputManager* inputManager;

		glm::mat4 proj;
		glm::mat4 view;

	public:
		TestVoxel();
		~TestVoxel();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		void SetGLWindow(void * window) override;
	};
}