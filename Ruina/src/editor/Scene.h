#pragma once

#include <filesystem>
#include <utility>
#include "GuiManager.h"
#include "Manager.h"
#include "MeshComponentFactory.h"
#include "MovementSystem.h"
#include "ObjectSelectionSystem.h"
#include "RenderSystem.h"
#include "WindowEventSystem.h"

class SceneObject {
public:
	SceneObject(int id, const char* name) : id(id), name(name) {};
	int32_t id;
	const char* name;
};

class Scene {
public:
	Scene(GLFWwindow*, const GuiManager&);

	void OnUpdate(float deltaTime);
	void OnRender();
	void OnImGuiRender();
	void UpdateSelected(const Event& ev);
	int AddCube();
	int AddTriangle();
	int AddMesh(const std::filesystem::path& path);
	void ChangePosition(float x, float y, float z);

private:
	Manager m;
	RenderSystem render_system;
	std::unique_ptr<MovementSystem> movement_system;
	std::unique_ptr<ObjectSelectionSystem> object_selection_system;
	std::unique_ptr<WindowEventSystem> window_event_system;
	GLFWwindow* window;
	GuiManager gui_manager;
	std::unordered_map<int32_t, SceneObject> scene_objects;
	glm::mat4 base_model;
	glm::vec3 translation;
	std::unordered_map<std::string, std::string> textures;
	std::string current_texture;
	std::vector<std::pair<std::string, std::string>> mesh_files;

};