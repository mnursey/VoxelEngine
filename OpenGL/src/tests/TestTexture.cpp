#include "TestTexture.h"

#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {

	TestTexture::TestTexture()
	{
		proj = glm::ortho(0.0f, 960.f, 0.0f, 540.0f, -1.0f, 1.0f);
		view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		rotation = 0.0f;

		va = new VertexArray();
		vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));

		layout = new VertexBufferLayout();
		layout->Push<float>(2);
		layout->Push<float>(2);
		va->AddBuffer(*vb, *layout);


		ib = new IndexBuffer(indices, 6);

		shader = new Shader("res/shaders/basic.shader");
		shader->Bind();
		shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		texture = new Texture("res/textures/porsche.png");
		texture->Bind();

		renderer = new Renderer();
	}

	TestTexture::~TestTexture()
	{
		delete renderer;
		delete shader;
		delete va;
		delete vb;
		delete layout;
		delete ib;
		delete texture;
	}

	void TestTexture::OnUpdate(float deltaTime)
	{

	}

	void TestTexture::OnRender()
	{
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 trans = glm::translate(glm::mat4(1.0f), translation);
		trans = glm::rotate(trans, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = trans * model;
		glm::mat4 mvp = proj * view * model;

		shader->Bind();
		shader->SetUniformMat4f("u_MVP", mvp);
		renderer->Draw(*va, *ib, *shader);
	}

	void TestTexture::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);
		ImGui::SliderFloat("Rotation", &rotation, 0.0f, 960.0f);
	}

}