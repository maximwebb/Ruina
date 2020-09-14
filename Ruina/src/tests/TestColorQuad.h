#pragma once

#include "Test.h"
#include "../game/renderer/VertexArray.h"
#include "../game/renderer/IndexBuffer.h"
#include "../Shader.h"
#include "../Renderer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>

namespace test {
	class TestColorQuad : public Test {
	public:
		TestColorQuad();
		~TestColorQuad();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float m_quad_color[4];
		std::unique_ptr<VertexArray> m_va;
		std::unique_ptr<VertexBuffer> m_vb;
		std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<glm::mat4> m_proj, m_view;
		std::unique_ptr<glm::vec3> m_translation;
	};
}