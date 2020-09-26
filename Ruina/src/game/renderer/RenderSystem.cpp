#include "RenderSystem.h"

RenderSystem::RenderSystem(SystemId id) : System(id) {
	m_camera = std::make_shared<Camera>(-1.0f, -1.0f, -10.0f, 0.0f, 1.57f);
	m_shader = std::make_unique<Shader>("Ruina/res/shaders/BatchVertex.shader","Ruina/res/shaders/BatchFragment.shader");
	m_shader->Bind();

	SubscribeToEvent<OnRenderEvent>();
	auto m_loc = m_shader->GetUniformLocation("u_textures");
	glUniform1iv(m_loc, 4, new int[4]{0, 1, 2, 3});

	m_texture_slots = std::make_unique<TextureCache>(3);

	/* Back-face culling */
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	/* Occlusion culling */
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void RenderSystem::Update(const Event& e) {
	glm::mat4 vp_matrix = m_camera->m_proj_matrix * m_camera->m_view_matrix;

	std::unordered_set<Component*> components = ECSEngine::component_manager().GetComponentGroup<MeshComponent>();
	for (Component* component : components) {
		auto* mesh_component = (MeshComponent*)component;
		ComponentId id = component->GetComponentId();
		if (m_vertex_arrays.find(id) == m_vertex_arrays.end() && m_index_buffers.find(id) == m_index_buffers.end()) {
			AddMeshComponent(mesh_component);
		}
		glm::mat4 model = mesh_component->model;
		m_shader->SetUniformMat4("u_MVP", vp_matrix * model);
		m_shader->SetUniformMat4("u_model", model);
		m_shader->SetUniformMat4("u_normal_model", glm::inverse(glm::transpose(model)));
		auto index = m_texture_slots->Bind(mesh_component->texture);
		m_shader->SetUniform1f("u_texture_index", index);
		m_shader->Bind();
		BindMeshComponent(mesh_component->GetComponentId());

		glDrawElements(GL_TRIANGLES, m_index_buffers.find(id)->second.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}

void RenderSystem::AddMeshComponent(MeshComponent* mesh_component) {
	ComponentId id = mesh_component->GetComponentId();
	auto* va = new VertexArray;
	/* TODO: figure out why we need to multiply by 4 */
	auto* vb = new VertexBuffer(mesh_component->vertices.data(), mesh_component->vertices.size() * 4);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	va->AddBuffer(*vb, layout);
	m_vertex_arrays.emplace(id, *va);

	auto* ib = new IndexBuffer(mesh_component->indices.data(), mesh_component->indices.size());
	m_index_buffers.emplace(id, *ib);
}

void RenderSystem::RemoveMeshComponent(ComponentId id) {
	m_vertex_arrays.erase(id);
	m_index_buffers.erase(id);
	ECSEngine::component_manager().DestroyComponent(id);
}

void RenderSystem::BindMeshComponent(ComponentId component) {
	m_vertex_arrays.find(component)->second.Bind();
	m_index_buffers.find(component)->second.Bind();
}