#include "TestColorBatchRender.h"

namespace test {
	TestColorBatchRender::TestColorBatchRender() {
		float data[] = {
			-50.0f, -20.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// 0
			-10.0f, -20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// 1
			-10.0f,  20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// 2
			-50.0f,  20.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // 3

			 10.0f, -20.0f, 0.0f, 0.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, // 4
			 50.0f, -20.0f, 0.0f, 0.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f, // 5
			 50.0f,  20.0f, 1.0f, 0.92f, 0.23f, 1.0f, 0.0f, 0.0f, 0.0f, // 6
			 10.0f,  20.0f, 0.0f, 0.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f  // 7
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

		/* Shader setup */
		m_shader = std::make_unique<Shader>("Ruina/res/shaders/BatchVertex.shader", "Ruina/res/shaders/BatchFragment.shader");
		m_shader->Bind();
		m_proj = std::make_unique<glm::mat4>(glm::ortho(-100.0f, 100.0f, -75.0f, 75.0f, -1.0f, 1.0f));
		m_view = std::make_unique<glm::mat4>(1.0f);
		m_shader->SetUniformMat4("u_MVP", (*m_proj) * (*m_view));
	}

	TestColorBatchRender::~TestColorBatchRender() {

	}

	void TestColorBatchRender::OnUpdate(float deltaTime) {

	}

	void TestColorBatchRender::OnRender() {
		Renderer renderer;
		renderer.Draw(*m_va, *m_ib, *m_shader);
	}

	void TestColorBatchRender::OnImGuiRender() {

	}
}