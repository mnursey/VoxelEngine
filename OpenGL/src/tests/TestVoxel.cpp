#include "TestVoxel.h"

#include "Renderer.h"
#include "CFrustum.h"
#include "imgui/imgui.h"
#include <iostream>

namespace test {

	TestVoxel::TestVoxel()
	{
		m_Running = true;

		// Chunk

		chunkManager = new voxelEngine::ChunkManager();

		chunkShader = new Shader("res/shaders/voxel.shader");
		chunkShader->Bind();

		// Lighting

		lightingVA = new VertexArray();
		lightingVB = new VertexBuffer(voxelEngine::VOXEL_POSITIONS, 6 * 6 * 6 * sizeof(float));

		lightingLayout = new VertexBufferLayout();
		lightingLayout->Push<float>(3);
		lightingLayout->Push<float>(3);
		lightingVA->AddBuffer(*lightingVB, *lightingLayout);

		lightingShader = new Shader("res/shaders/voxellight.shader");
		lightingShader->Bind();

		renderer = new Renderer();

		// World Thread

		//worldThread = CreateUpdateWorldThread();
	}

	TestVoxel::~TestVoxel()
	{
		m_Running = false;

		delete renderer;

		delete chunkShader;

		delete lightingShader;
		delete lightingVA;
		delete lightingVB;
		delete lightingLayout;

		delete ib;
		delete texture;
		delete inputManager;

		delete chunkManager;
	}

	void TestVoxel::UpdateWorld()
	{
		glm::vec3 pP = camera.GetPosition();
		float playerPosition[3] = { pP[0], pP[1], pP[2] };

		chunkManager->Update(playerPosition);
	}

	void TestVoxel::OnUpdate(float deltaTime)
	{
		inputManager->HandleInput();
		bool* inputs = 0;
		inputManager->GetKeyInput(inputs);

		if (*(inputs + 6) == true)
		{
			if (!m_lockMouse)
			{
				glfwSetInputMode((GLFWwindow *)m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				m_lockMouse = true;
			}
			else {
				glfwSetInputMode((GLFWwindow *)m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				m_lockMouse = false;
			}
		}

		if (m_lockMouse)
			camera.MouseInput(MOUSE_X, MOUSE_Y);

		if (*inputs == true)
			camera.ProcessKeyboard(FORWARD, deltaTime);
		if (*(inputs + 1) == true)
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (*(inputs + 2) == true)
			camera.ProcessKeyboard(LEFT, deltaTime);
		if (*(inputs + 3) == true)
			camera.ProcessKeyboard(RIGHT, deltaTime);
		if (*(inputs + 4) == true)
			camera.ProcessKeyboard(UP, deltaTime);
		if (*(inputs + 5) == true)
			camera.ProcessKeyboard(DOWN, deltaTime);

		UpdateWorld();
	}

	void TestVoxel::OnRender()
	{
		proj = glm::perspective(glm::radians(60.0f), 960.0f / 540.0f, 0.1f, 10000.0f);

		view = camera.GetViewMatrix();
		lightPosition.x = 0;
		lightPosition.z = 0;
		lightPosition.y = 400;

		// Create view frustum
		CFrustum frustum = CFrustum(proj * view);

		// Render Chunks
		glm::mat4 modelChunk = glm::mat4(1.0f);
		glm::mat4 mvpChunk = proj * view * modelChunk;
		chunkShader->Bind();
		chunkShader->SetUniformMat4f("u_MVP", mvpChunk);

		glm::vec3 camPos = camera.GetPosition();
		chunkShader->SetUniform3f("u_viewPos", camPos.x, camPos.y, camPos.z);

		chunkShader->SetUniform3f("u_lightColor", lightColor[0], lightColor[1], lightColor[2]);
		chunkShader->SetUniform3f("u_lightPosition", lightPosition.x, lightPosition.y, lightPosition.z);
		chunkShader->SetUniformMat4f("u_model", modelChunk);

		for (unsigned int i = 0; i < chunkManager->activeChunks.size(); i++)
		{
			int pos[3];
			chunkManager->activeChunks[i]->GetPosition(pos);

			if (frustum.FrustumCulling(glm::vec3(pos[0] * voxelEngine::Chunk::s_SIZE, pos[1] * voxelEngine::Chunk::s_SIZE, pos[2] * voxelEngine::Chunk::s_SIZE), voxelEngine::Chunk::s_SIZE * voxelEngine::Voxel::s_VOXEL_SIZE * 1.25))
			{
				VertexArray* chunkVA;
				int c;
				chunkManager->activeChunks[i]->renderObject->GetRenderObjects(chunkVA, c);
				renderer->Draw(*chunkVA, *chunkShader, c);
			}
		}

		// Render Lighting

		glm::mat4 modelLight = glm::mat4(1.0f);
		modelLight = glm::translate(modelLight, lightPosition);
		glm::mat4 mvpLight = proj * view * modelLight;
		lightingShader->Bind();
		lightingShader->SetUniformMat4f("u_MVP", mvpLight);
		renderer->Draw(*lightingVA, *lightingShader, 6 * 6);
	}

	void TestVoxel::OnImGuiRender()
	{
		ImGui::SliderFloat3("Light Color", lightColor, 0.0f, 1.0f);
	}

	void TestVoxel::SetGLWindow(void * window)
	{
		std::cout << "Set GLWWindow" << std::endl;
		inputManager = new InputManager((GLFWwindow *)window);
		m_window = (GLFWwindow *)window;
		//glfwSetInputMode((GLFWwindow *)m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

}