#include "TestTextureBatchRender.h"

namespace test {
	TestTextureBatchRender::TestTextureBatchRender() {
		float data[] = {
				-50.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // 0
				-10.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // 1
				-10.0f,  20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, // 2
				-50.0f,  20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // 3

				10.0f, -20.0f, 0.0f, 0.0f,  1.0f,  1.0f, 0.0f, 0.0f, 2.0f, // 4
				50.0f, -20.0f, 0.0f, 0.0f,  1.0f,  1.0f, 1.0f, 0.0f, 2.0f, // 5
				50.0f,  20.0f, 1.0f, 0.92f, 0.23f, 1.0f, 1.0f, 1.0f, 2.0f, // 6
				10.0f,  20.0f, 0.0f, 0.0f,  1.0f,  1.0f, 0.0f, 1.0f, 2.0f  // 7
		};

		unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0,

				4, 5, 6,
				6, 7, 4
		};


		/* Vertex array setup */
		m_va = std::make_unique<VertexArray>();
		m_vb = std::make_unique<VertexBuffer>(data, 2 * 4 * 9 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2); //Add attribute layouts here.
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);
		m_va->AddBuffer(*m_vb, layout);

		/* Index buffer setup */
		m_ib = std::make_unique<IndexBuffer>(indices, 12);

		/* Texture setup */
		m_texture_1 = std::make_unique<Texture>("Ruina/res/textures/texture.png");
		m_texture_2 = std::make_unique<Texture>("Ruina/res/textures/texture2.png");
		m_texture_1->Bind(0);
		m_texture_2->Bind(1);

		/* Shader setup */
		m_shader = std::make_unique<Shader>("Ruina/res/shaders/BatchVertex.shader", "Ruina/res/shaders/BatchFragment.shader");
		m_shader->Bind();
		m_proj = std::make_unique<glm::mat4>(glm::ortho(-100.0f, 100.0f, -75.0f, 75.0f, -1.0f, 1.0f));
		m_view = std::make_unique<glm::mat4>(1.0f);
		m_shader->SetUniformMat4("u_MVP", (*m_proj) * (*m_view));

		auto m_loc = m_shader->GetUniformLocation("u_textures");
		glUniform1iv(m_loc, 2, new int[2]{0, 1});
	}

	TestTextureBatchRender::~TestTextureBatchRender() {

	}

	void TestTextureBatchRender::OnUpdate(float deltaTime) {

	}

	void TestTextureBatchRender::OnRender() {
		Renderer renderer;
		renderer.Draw(*m_va, *m_ib, *m_shader);
	}

	void TestTextureBatchRender::OnImGuiRender() {
		Test::OnImGuiRender();
	}
}