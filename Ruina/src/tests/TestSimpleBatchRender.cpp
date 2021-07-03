#include "TestSimpleBatchRender.h"

namespace test {
	TestSimpleBatchRender::TestSimpleBatchRender() {
		int vertex_offsets[] = {
			0, 0,
			0, 1,
			1, 1,
			1, 0
		};

		int index_offsets[] = {
			0, 1, 2,
			2, 3, 0
		};

//		float data[] = {
//			-65.0f, -30.0f, // 0
//			 -5.0f, -30.0f, // 1
//			 -5.0f,  30.0f, // 2
//			-65.0f,  30.0f,  // 3
//
//			 0.0f,  -30.0f, // 4
//			 60.0f, -30.0f, // 5
//			 60.0f,  30.0f, // 6
//			 0.0f,   30.0f // 7
//		};


		float data[8 * 8 * 8];
		unsigned int indices[8 * 8 * 6];

		int n = 8;
		float length = 960.0f/(float)(9 * n - 1);
		float marginX = -60.0f;
		float marginY = -60.0f;
		int quad_step = 8;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				/* Fill vertex buffer */
				for (int k = 0; k < 4; k++) {

					data[n * quad_step * i + quad_step * j + 2 * k] = marginX + (float)j * 0.125f * length + (float)(j + vertex_offsets[k*2]) * length; // x-coord
					data[n * quad_step * i + quad_step * j + 2 * k + 1] = marginY + (float)i * 0.125f * length + (float)(i + vertex_offsets[k*2 + 1]) * length; // y-coord
				}
				/* Fill index buffer */
				for (int k = 0; k < 6; k++) {
					indices[n * 6 * i + 6 * j + k] = index_offsets[k] + n * 4 * i + 4 * j;
				}
			}
		}

		/* Vertex array setup */
		m_va = std::make_unique<VertexArray>();
		m_vb = std::make_unique<VertexBuffer>(data, n * n * 4 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.PushFloat(2); //Add attribute layouts here.
		m_va->AddBuffer(*m_vb, layout);

		/* Index buffer setup */
		m_ib = std::make_unique<IndexBuffer>(indices, n * n * 6);

		/* Shader setup */
		m_shader = std::make_unique<Shader>("Ruina/res/shaders/Vertex.shader", "Ruina/res/shaders/Fragment.shader");
		m_shader->Bind();
		m_proj = std::make_unique<glm::mat4>(glm::ortho(-100.0f, 100.0f, -75.0f, 75.0f, -1.0f, 1.0f));
		m_view = std::make_unique<glm::mat4>(1.0f);
		m_shader->SetUniformMat4("u_MVP", (*m_proj) * (*m_view));
		m_shader->SetUniform4f("u_color", 1.0f, 1.0f, 1.0f, 1.0f);
	}

	TestSimpleBatchRender::~TestSimpleBatchRender() {

	}

	void TestSimpleBatchRender::OnUpdate(float deltaTime) {

	}

	void TestSimpleBatchRender::OnRender() {
		Renderer renderer;
		renderer.Draw(*m_va, *m_ib, *m_shader);
	}

	void TestSimpleBatchRender::OnImGuiRender() {
		Test::OnImGuiRender();
	}


}