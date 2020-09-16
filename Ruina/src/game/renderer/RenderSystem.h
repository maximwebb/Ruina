#pragma once

#include <ECSEngine.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "System.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include "../../Shader.h"
#include "../../Texture.h"
#include "../../geometry/Cube.h"
#include "../Chunk.h"

class RenderSystem : public System {
public:
	RenderSystem(SystemId id);

	void Update(const Event&) override;

public:
	std::shared_ptr<Camera> m_camera;
	void RemoveMeshComponent(ComponentId id);

private:
	void AddMeshComponent(MeshComponent *mesh_component);
	void BindMeshComponent(ComponentId component);

private:
	std::unique_ptr<Texture> m_texture1;
	std::unique_ptr<Texture> m_texture2;
	std::unique_ptr<Shader> m_shader;
	std::unordered_map<ComponentId, VertexArray> m_vertex_arrays;
	std::unordered_map<ComponentId, IndexBuffer> m_index_buffers;
};
