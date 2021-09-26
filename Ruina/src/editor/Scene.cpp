#include "Scene.h"
#include "imgui/imgui.h"
#include "MeshLoader.h"

Scene::Scene(GLFWwindow* window, const GuiManager& gui_manager)
		: m(), gui_manager(gui_manager), render_system(m), window(window), base_model(1.0f),
		  translation(0.0f), mesh_files() {

	movement_system = std::make_unique<MovementSystem>(m, render_system.camera, window, 0.15f, 0.015f);
	object_selection_system = std::make_unique<ObjectSelectionSystem>(m, render_system.camera, window);
	window_event_system = std::make_unique<WindowEventSystem>(m, window);
	m.RegisterEventListener(typeid(SelectElementEvent), HANDLER(UpdateSelected));

	textures = {{"Test",        "Ruina/res/textures/texture_palette.png"},
				{"Rainbow",     "Ruina/res/textures/rainbow.png"},
				{"Basketball",  "Ruina/res/textures/basketball.png"},
				{"Diamond Ore", "Ruina/res/textures/diamond_ore.png"},
				{"Metal",       "Ruina/res/textures/metal.jpg"}};
	current_texture = "Ruina/res/textures/texture_palette.png";

	for (const auto& file: std::filesystem::directory_iterator("Ruina/res/meshes")) {
		mesh_files.emplace_back(file.path().filename(), file.path());
	}

}

void Scene::OnUpdate(float deltaTime) {
	m.QueueEvent<GameTickEvent>({});
}

void Scene::OnRender() {
	m.QueueEvent<RenderEvent>({});
}

void Scene::OnImGuiRender() {
	gui_manager.Begin("Controls", {50, 250});
	ImGui::BeginGroup();
	if (ImGui::BeginChild("objects", ImVec2(200.0f, 120.0f), true, 0)) {
		for (auto&[_, obj]: scene_objects) {
			if (ImGui::Selectable(obj.name, obj.id == object_selection_system->selected)) {
				if (obj.id == object_selection_system->selected) {
					m.QueueEvent<SelectElementEvent>({obj.id, false});
				} else {
					m.QueueEvent<SelectElementEvent>({obj.id, true});
				}
			}
		}
		ImGui::EndChild();
	}
	ImGui::EndGroup();

	// Used to disable sliders
	if (object_selection_system->selected == -1) {
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}
	ImGui::SliderFloat("x-axis", &translation.x, -5.0f, 5.0f);
	ImGui::SliderFloat("y-axis", &translation.y, -5.0f, 5.0f);
	ImGui::SliderFloat("z-axis", &translation.z, -5.0f, 5.0f);

	if (object_selection_system->selected != -1) {
		ChangePosition(-translation.x, translation.y, translation.z);
	} else {
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}

	if (ImGui::Button("Add Object")) {
		ImGui::OpenPopup("mesh_menu");
	}
	if (ImGui::BeginPopup("mesh_menu")) {
		ImGui::Text("Select Mesh");
		ImGui::Separator();
		int id = -1;
		if (ImGui::MenuItem("Cube")) {
			id = AddCube();
		}
		if (ImGui::MenuItem("Triangle")) {
			id = AddTriangle();
		}
		if (ImGui::BeginMenu("More")) {
			for (const auto& [name, path]: mesh_files) {
				if (ImGui::MenuItem(name.c_str())) {
					id = AddMesh(path);
				}
			}
			ImGui::EndMenu();
		}
		if (id != -1) {
			m.QueueEvent<SelectElementEvent>({id, true});
		}
		ImGui::EndPopup();
	}


	ImGui::SameLine();
	if (ImGui::Button("Texture")) {
		ImGui::OpenPopup("texture_menu");
	}
	ImGui::SameLine();
	if (ImGui::BeginPopup("texture_menu")) {
		ImGui::Text("Select Texture");
		ImGui::Separator();
		for (auto& [name, path]: textures) {
			if (ImGui::Selectable(name.c_str())) {
				current_texture = path;
				if (object_selection_system->selected != -1) {
					auto g = m.CreateGroup<MeshComponent>();
					auto [mesh_new] = g.Get(object_selection_system->selected);
					mesh_new->texture = TextureManager::Get(current_texture);
				}
			}
		}

		ImGui::EndPopup();
	}


	ImGui::SameLine();
	if (ImGui::Button("Delete")) {
		int id = object_selection_system->selected;
		m.Delete(id);
		m.QueueEvent<SelectElementEvent>({id, false});
		scene_objects.erase(scene_objects.find(id));
	}
	gui_manager.End();
}

void Scene::UpdateSelected(const Event& ev) {

	SelectElementEvent e = *(SelectElementEvent*) (&ev);
	if (e.select) {
		auto g = m.CreateGroup<MeshComponent>();
		auto [mesh_new] = g.Get(object_selection_system->selected);
		base_model = mesh_new->model;
	} else {
		base_model = glm::mat4(1.0f);
	}
	translation = glm::vec3(0.0f);
}

int Scene::AddCube() {
	glm::mat4 model1 = glm::translate(
			glm::scale(
					glm::rotate(
							glm::mat4(10.0f),
							0.0f, glm::vec3(1.0f, 1.0f, -1.0f)),
					glm::vec3(5.0f, 5.0f, 5.0f)),
			glm::vec3(-0.5f, -1.5f, 0.0f));


	glm::mat4 model = glm::mat4(1.0f);
	Entity e = m.Create();

	m.Add<MeshComponent>(e, MeshComponentFactory::CubeMesh(), MeshComponentFactory::CubeIndices(),
						 TextureManager::Get(current_texture), model);
	char* buf = new char[20];
	sprintf(buf, "Cube %d", e.id);
	scene_objects.emplace(e.id, SceneObject{e.id, buf});
	return e.id;
}

int Scene::AddTriangle() {
	Entity e = m.Create();
	glm::mat4 model = glm::mat4(1.0f);
	m.Add<MeshComponent>(e, MeshComponentFactory::TriangleMesh(), MeshComponentFactory::TriangleIndices(),
						 TextureManager::Get(current_texture), model);
	char* buf = new char[20];
	sprintf(buf, "Triangle %d", e.id);
	scene_objects.emplace(e.id, SceneObject{e.id, buf});
	return e.id;
}

int Scene::AddMesh(const std::filesystem::path& path) {
	auto vertices = MeshLoader::LoadMesh(path.c_str());
	std::vector<unsigned int> indices(vertices.size());
	std::iota(std::begin(indices), std::end(indices), 0);

	Entity e = m.Create();
//	glm::mat4 model = glm::scale(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(-1, 0, 0)),glm::vec3(0.1f));
	glm::mat4 model = glm::scale(glm::mat4(1.0f),glm::vec3(0.1f));
	m.Add<MeshComponent>(e, vertices, indices, TextureManager::Get(current_texture), model);
	char* buf = new char[20];
	sprintf(buf, "Mesh %d", e.id);
	scene_objects.emplace(e.id, SceneObject{e.id, buf});
	return e.id;
}

void Scene::ChangePosition(float x, float y, float z) {
	if (object_selection_system->selected != -1) {
		auto g = m.CreateGroup<MeshComponent>();
		auto[mesh] = g.Get(object_selection_system->selected);
		mesh->model = glm::translate(base_model, glm::vec3(x, y, z));
	}
}
