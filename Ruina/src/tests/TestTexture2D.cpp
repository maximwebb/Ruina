#include "TestTexture2D.h"


namespace test {
	TestTexture2D::TestTexture2D() {
		float data[] = {
				-30.0f, -30.0f, 0.0f, 0.0f, // 0
				30.0f, -30.0f, 1.0f, 0.0f, // 1
				30.0f,  30.0f, 1.0f, 1.0f, // 2
				-30.0f,  30.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indices[] = {
				0, 1, 2,
				2, 3, 0
		};


		/* Vertex array setup */
		m_va = std::make_unique<VertexArray>();
		m_vb = std::make_unique<VertexBuffer>(data, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2); //Add attribute layouts here.
		layout.Push<float>(2);
		m_va->AddBuffer(*m_vb, layout);

		/* Index buffer setup */
		m_ib = std::make_unique<IndexBuffer>(indices, 6);

		/* Texture setup */
		m_texture = std::make_unique<Texture>("Ruina/res/textures/texture.png");
		m_texture->Bind();

		/* Shader setup */
		m_shader = std::make_unique<Shader>("Ruina/res/shaders/Vertex.shader", "Ruina/res/shaders/Fragment.shader");
		m_shader->Bind();
		m_proj = std::make_unique<glm::mat4>(glm::ortho(-100.0f, 100.0f, -75.0f, 75.0f, -1.0f, 1.0f));
		m_view = std::make_unique<glm::mat4>(1.0f);
		m_shader->SetUniformMat4("u_MVP", (*m_proj) * (*m_view));
		m_shader->SetUniform4f("u_color", m_quad_color[0], m_quad_color[1], m_quad_color[2], m_quad_color[3]);
		m_shader->SetUniform1i("u_is_color", 0);
		m_shader->SetUniform1i("u_texture", 0);
	}

	TestTexture2D::~TestTexture2D() {

	}

	void TestTexture2D::OnUpdate(float deltaTime) {

	}

	void TestTexture2D::OnRender() {
		Renderer renderer;
		renderer.Draw(*m_va, *m_ib, *m_shader);
	}

	void TestTexture2D::OnImGuiRender() {
		Test::OnImGuiRender();
	}

}
