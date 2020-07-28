#pragma once
#include "Test.h"

namespace test {
	class TestColorBatchRender : public Test {
	public:
		TestColorBatchRender();
		~TestColorBatchRender();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_va;
		std::unique_ptr<VertexBuffer> m_vb;
		std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<glm::mat4> m_proj, m_view;
	};
}

