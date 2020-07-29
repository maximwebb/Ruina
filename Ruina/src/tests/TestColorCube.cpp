#include "TestColorCube.h"

namespace test {
	TestColorCube::TestColorCube() {

		m_cube = std::make_unique<Cube>();

		/* Vertex array setup */
		m_va = std::make_unique<VertexArray>();
		m_vb = std::make_unique<VertexBuffer>(m_cube->vertex_data, m_cube->vertex_data_size);
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(2);
		layout.Push<float>(1);
		m_va->AddBuffer(*m_vb, layout);

		/* Index buffer setup */
		m_ib = std::make_unique<IndexBuffer>(m_cube->m_indices, 36);

		m_shader = std::make_unique<Shader>("Ruina/res/shaders/BatchVertex.shader", "Ruina/res/shaders/BatchFragment.shader");
		m_shader->Bind();
		m_proj = std::make_unique<glm::mat4>(glm::perspective(1.0f, GLfloat(4.0f/3.0f), 1.0f, 150.0f));
		m_view = std::make_unique<glm::mat4>(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f)));
		m_model = std::make_unique<glm::mat4>(
				glm::translate(
						glm::scale(
								glm::rotate(
									glm::mat4(1.0f),
									0.0f, glm::vec3(1.0f, 1.0f, -1.0f)),
							glm::vec3(2.0f, 2.0f, 2.0f)),
						glm::vec3(-0.5f, -0.5f, 0.0f)));
		m_texture_1 = std::make_unique<Texture>("Ruina/res/textures/diamond_ore.png");
		m_texture_2 = std::make_unique<Texture>("Ruina/res/textures/diamond_ore.png");
		m_texture_1->Bind(0);
		m_texture_2->Bind(1);
		m_shader->SetUniformMat4("u_MVP", (*m_proj) * (*m_view) * (*m_model));
		m_shader->SetUniformMat4("u_model", *m_model);
		m_shader->SetUniformMat4("u_normal_model", glm::inverse(glm::transpose(*m_model)));
		auto m_loc = m_shader->GetUniformLocation("u_textures");
		glUniform1iv(m_loc, 2, new int[2]{0, 1});

		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		angle = 0.0f;
	}

	TestColorCube::~TestColorCube() {

	}

	void TestColorCube::OnUpdate(float deltaTime) {
		Test::OnUpdate(deltaTime);
	}

	void TestColorCube::OnRender() {
		Renderer renderer;
		if (angle > 3.142f * 2)
			angle = 0.0f;
		angle += 0.01f;
		*m_model = glm::translate(
						glm::scale(
								glm::rotate(
										glm::mat4(1.0f),
										angle, glm::vec3(1.0f, 1.0f, -1.0f)),
								glm::vec3(2.0f, 2.0f, 2.0f)),
						glm::vec3(-0.5f, -0.5f, 0.0f));
		m_shader->SetUniformMat4("u_MVP", (*m_proj) * (*m_view) * (*m_model));
		m_shader->SetUniformMat4("u_model", *m_model);
		m_shader->SetUniformMat4("u_normal_model", glm::inverse(glm::transpose(*m_model)));
		renderer.Draw(*m_va, *m_ib, *m_shader);
	}

	void TestColorCube::OnImGuiRender() {

	}
}
