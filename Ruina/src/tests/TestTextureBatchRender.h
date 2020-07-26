#pragma once
#include "Test.h"

namespace test {
	class TestTextureBatchRender : public Test {
	public:
		TestTextureBatchRender();
		~TestTextureBatchRender();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_va;
		std::unique_ptr<VertexBuffer> m_vb;
		std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<Texture> m_texture_1;
		std::unique_ptr<Texture> m_texture_2;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<glm::mat4> m_proj, m_view;
	};
}

