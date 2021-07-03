#include "TestColorQuad.h"

namespace test {

	TestColorQuad::TestColorQuad()
		: m_quad_color{1.0f, 0.0f, 0.0f, 1.0f}
		{
		float data[] = {
			-30.0f, -30.0f,
			-30.0f, 30.0f,
			30.0f, 30.0f,
			30.0f, -30.0f,
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};


		/* Vertex array setup */
		m_va = std::make_unique<VertexArray>();
		m_vb = std::make_unique<VertexBuffer>(data, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.PushFloat(2);
		m_va->AddBuffer(*m_vb, layout);

		/* Index buffer setup */
		m_ib = std::make_unique<IndexBuffer>(indices, 6);

		/* Shader setup */
		m_shader = std::make_unique<Shader>("Ruina/res/shaders/Vertex.shader", "Ruina/res/shaders/Fragment.shader");
		m_shader->Bind();
		m_translation = std::make_unique<glm::vec3>(0.0f, 0.0f, 0.0f);
		m_proj = std::make_unique<glm::mat4>(glm::ortho(-100.0f, 100.0f, -75.0f, 75.0f, -1.0f, 1.0f));
		m_view = std::make_unique<glm::mat4>(1.0f);
		m_shader->SetUniformMat4("u_MVP", (*m_proj) * (*m_view));
		m_shader->SetUniform4f("u_color", m_quad_color[0], m_quad_color[1], m_quad_color[2], m_quad_color[3]);
	};

	TestColorQuad::~TestColorQuad() {

	}

	void TestColorQuad::OnUpdate(float deltaTime) {

	}

	void TestColorQuad::OnRender() {
		Renderer renderer;
		m_shader->Bind();
		glm::mat4 model = glm::translate(glm::mat4(1.0f), *m_translation);
		glm::mat4 mvp = (*m_proj) * (*m_view) * model;

		m_shader->SetUniform4f("u_color", m_quad_color[0], m_quad_color[1], m_quad_color[2], m_quad_color[3]);
		m_shader->SetUniformMat4("u_MVP", mvp);
		m_shader->Unbind();
		renderer.Draw(*m_va, *m_ib, *m_shader);
	}

	void TestColorQuad::OnImGuiRender() {
		GuiColorPicker color_picker("Color", (ImVec4*)m_quad_color);
		GuiTripleSlider slider("Positions", (float*)(&m_translation->x));
		color_picker.Draw();
		slider.Draw();
	}
}