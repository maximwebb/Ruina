#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_set>
#include "Camera.h"
#include "ECSEngine.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "System.h"
#include "Texture.h"
#include "TextureCache.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

class RenderSystem : public System {
public:
	RenderSystem(SystemId id);
	void Update(const Event&) override;
	void RemoveMeshComponent(ComponentId id);

public:
	std::shared_ptr<Camera> m_camera;

private:
	void AddMeshComponent(MeshComponent *mesh_component);
	void BindMeshComponent(ComponentId component);

private:
	std::unique_ptr<Shader> m_shader;
	std::unordered_map<ComponentId, VertexArray> m_vertex_arrays;
	std::unordered_map<ComponentId, IndexBuffer> m_index_buffers;
	std::unique_ptr<TextureCache> m_texture_slots;
};
