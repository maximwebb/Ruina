#pragma once
#include "Test.h"
#include "../geometry/Cube.h"
#include "../game/Chunk.h"
#include "../game/Camera.h"

namespace test {
	class TestChunkRender : public Test {
	public:
		TestChunkRender();
		~TestChunkRender();

		void OnUpdate(float deltaTime) override;

		void OnRender() override;

		void OnImGuiRender() override;

	private:
		std::unique_ptr<Cube> m_cube;
		std::unique_ptr<Chunk> m_chunk;
		std::unique_ptr<VertexArray> m_va;
		std::unique_ptr<VertexBuffer> m_vb;
		std::unique_ptr<IndexBuffer> m_ib;
		std::unique_ptr<Shader> m_shader;
		std::unique_ptr<glm::mat4> m_proj, m_view, m_model;
		std::unique_ptr<Texture> m_texture_1;
		std::unique_ptr<Texture> m_texture_2;
		float angle;
		Camera m_camera;
	};
}
