#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_set>
#include <memory>
#include "Camera.h"
#include "Event.h"
#include "IndexBuffer.h"
#include "Manager.h"
#include "MassComponent.h"
#include "MeshComponent.h"
#include "Shader.h"
#include "System.h"
#include "Texture.h"
#include "TextureCache.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

class RenderSystem : public System {
public:
    explicit RenderSystem(Manager&);
    void Update(const Event&);
    void UpdateSelected(const Event&);
    void UpdateHovered(const Event&);
    void RemoveMeshComponent(Entity);
    std::shared_ptr<Camera> camera;

private:
    void AddMeshComponent(MeshComponent* mesh_component, Entity id);
    void BindMeshComponent(Entity);

    std::unique_ptr<Shader> shader;
    std::unordered_map<Entity, VertexArray> vertex_arrays;
    std::unordered_map<Entity, IndexBuffer> index_buffers;
    std::unique_ptr<TextureCache> texture_slots;

	int selected;
	bool clicked;
};