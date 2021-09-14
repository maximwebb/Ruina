#include "RenderSystem.h"

RenderSystem::RenderSystem(Manager& m) : System(m) {
	camera = std::make_shared<Camera>(-1.0f, -1.0f, -10.0f, 0.0f, 1.57f);
	shader = std::make_unique<Shader>("Ruina/res/shaders/BatchVertex.shader","Ruina/res/shaders/BatchFragment.shader");
	shader->Bind();

	Subscribe<RenderEvent>(HANDLER(Update));
	auto loc = shader->GetUniformLocation("u_textures");
	glUniform1iv(loc, 4, new int[4]{0, 1, 2, 3});

	texture_slots = std::make_unique<TextureCache>(3);

	/* Back-face culling */
	glFrontFace(GL_CW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	/* Occlusion culling */
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void RenderSystem::Update(const Event& e) {
	glm::mat4 vp_matrix = camera->proj_matrix * camera->view_matrix;
	auto mesh_components = m.CreateGroup<MeshComponent>();

	for (auto id : mesh_components) {
		auto [mesh_component] = mesh_components.Get(id);
		if (vertex_arrays.find(id) == vertex_arrays.end() && index_buffers.find(id) == index_buffers.end()) {
			AddMeshComponent(mesh_component, id); // Probably gonna throw an error
		}
		glm::mat4 model = mesh_component->model;
		shader->SetUniformMat4("u_MVP", vp_matrix * model);
//		shader->SetUniformMat4("u_model", model);
		shader->SetUniformMat4("u_normal_model", glm::inverse(glm::transpose(model)));
		auto index = texture_slots->Bind(mesh_component->texture);
		shader->SetUniform1f("u_texture_index", index);
		shader->SetUniform4f("camera_position", camera->GetPosition());
		shader->Bind();
		BindMeshComponent(id);

		glDrawElements(GL_TRIANGLES, index_buffers.find(id)->second.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}

void RenderSystem::AddMeshComponent(MeshComponent* mesh_component, Entity id) {
	VertexArray va;
	auto data = mesh_component->vertices.data();
	int size = mesh_component->vertices.size();
	VertexBuffer vb(data, size * 4);

	VertexBufferLayout layout;
	layout.PushFloat(3);
	layout.PushFloat(3);
	layout.PushFloat(2);

	va.AddBuffer(vb, layout);
	IndexBuffer ib(mesh_component->indices.data(), mesh_component->indices.size());
	vertex_arrays.emplace(id, std::move(va));
	index_buffers.emplace(id, std::move(ib));
}

void RenderSystem::RemoveMeshComponent(Entity id) {
	vertex_arrays.erase(id);
	index_buffers.erase(id);
	// TODO: Remove components from manager here.
}

void RenderSystem::BindMeshComponent(Entity id) {
	vertex_arrays.find(id)->second.Bind();
	index_buffers.find(id)->second.Bind();
}