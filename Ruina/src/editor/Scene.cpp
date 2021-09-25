#include "Scene.h"
#include "imgui/imgui.h"

Scene::Scene(GLFWwindow* window, const GuiManager& gui_manager)
		: m(), gui_manager(gui_manager), render_system(m), window(window), base_model(1.0f),
		  translation(0.0f) {

	movement_system = std::make_unique<MovementSystem>(m, render_system.camera, window, 0.15f, 0.015f);
	object_selection_system = std::make_unique<ObjectSelectionSystem>(m, render_system.camera, window);
	window_event_system = std::make_unique<WindowEventSystem>(m, window);
	m.RegisterEventListener(typeid(SelectElementEvent), HANDLER(UpdateSelected));

	textures = {{"Test", "Ruina/res/textures/texture_palette.png"},
				{"Rainbow", "Ruina/res/textures/rainbow.png"},
				{"Basketball", "Ruina/res/textures/basketball.png"},
				{"Diamond Ore", "Ruina/res/textures/diamond_ore.png"}};
	current_texture = "Ruina/res/textures/texture_palette.png";
	AddCube();
}

void Scene::OnUpdate(float deltaTime) {
	m.QueueEvent<GameTickEvent>({});
}

void Scene::OnRender() {
	m.QueueEvent<RenderEvent>({});
}

void Scene::OnImGuiRender() {
	gui_manager.Begin("Controls", {50, 250});
	if (ImGui::TreeNodeEx("Objects", ImGuiTreeNodeFlags_DefaultOpen)) {
		for (auto&[_, obj]: scene_objects) {
			if (ImGui::Selectable(obj.name, obj.id == object_selection_system->selected)) {
				if (obj.id == object_selection_system->selected) {
					m.QueueEvent<SelectElementEvent>({obj.id, false});
				} else {
					m.QueueEvent<SelectElementEvent>({obj.id, true});
				}
			}
		}
		ImGui::TreePop();
	}
	if (ImGui::Button("+")) {
		AddCube();
	}
	if (object_selection_system->selected != -1) {
		ImGui::SliderFloat("x-axis", &translation.x, -5.0f, 5.0f);
		ImGui::SliderFloat("y-axis", &translation.y, -5.0f, 5.0f);
		ImGui::SliderFloat("z-axis", &translation.z, -5.0f, 5.0f);
		ChangePosition(-translation.x, translation.y, translation.z);
	}
	if (ImGui::Button("Texture"))
            ImGui::OpenPopup("my_select_popup");
        ImGui::SameLine();
	if (ImGui::BeginPopup("my_select_popup")) {
		ImGui::Text("Textures");
		ImGui::Separator();
		for (auto& [name, path]: textures) {
			if (ImGui::Selectable(name.c_str())) {
				current_texture = path;
			}
		}

		ImGui::EndPopup();
	}
	gui_manager.End();
}

void Scene::UpdateSelected(const Event& ev) {

	SelectElementEvent e = *(SelectElementEvent*) (&ev);
	if (e.select) {
		auto g = m.CreateGroup<MeshComponent>();
		auto[mesh_new] = g.Get(object_selection_system->selected);
		base_model = mesh_new->model;
	} else {
		base_model = glm::mat4(1.0f);
	}
	translation = glm::vec3(0.0f);
}

void Scene::AddCube() {
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
	sprintf(buf, "Object %d", e.id);
	scene_objects.emplace(e.id, SceneObject{e.id, buf});
}

void Scene::AddTriangle() {
	Entity e = m.Create();
	glm::mat4 model = glm::mat4(1.0f);
	m.Add<MeshComponent>(e, MeshComponentFactory::TriangleMesh(), MeshComponentFactory::TriangleIndices(),
						 TextureManager::Get(current_texture), model);
	char buf[20];
	sprintf(buf, "Object %d", e.id);
	scene_objects.emplace(e.id, SceneObject{e.id, buf});
}

void Scene::ChangePosition(float x, float y, float z) {
	if (object_selection_system->selected != -1) {
		auto g = m.CreateGroup<MeshComponent>();
		auto[mesh] = g.Get(object_selection_system->selected);
		mesh->model = glm::translate(base_model, glm::vec3(x, y, z));
	}
}
