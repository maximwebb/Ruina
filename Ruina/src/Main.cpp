#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Debugger.h"
#include "editor/Editor.h"
#include "TestClearColor.h"
#include "TestColorQuad.h"
#include "TestECS.h"
#include "TestECSRender.h"
#include "TestSimpleBatchRender.h"


int main() {
	GLFWwindow* window;
	if (!glfwInit()) {
		return -1;
	}

	window = glfwCreateWindow(1280, 960, "Ruina", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Error initialising GLEW." << std::endl;
	}

	initDebugger();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader shader("Ruina/res/shaders/Vertex.shader", "Ruina/res/shaders/Fragment.shader");
	Renderer renderer;
	GuiManager imgui(window);

	bool editor_mode = false;

	test::Test* current_test;
	auto* test_menu = new test::TestMenu(current_test, editor_mode, imgui);
	current_test = test_menu;

	test_menu->RegisterTest<test::TestClearColor>("Clear Color");
	test_menu->RegisterTest<test::TestColorQuad>("Colored Square");
	test_menu->RegisterTest<test::TestSimpleBatchRender>("Simple Batch Render");
	test_menu->RegisterTest<test::TestECS>("ECS");
	auto* ecs_render_test = new test::TestECSRender(window);
	test_menu->RegisterTest(ecs_render_test, "ECS Render");

	auto* editor = new Editor(editor_mode, imgui, window);

	while (!glfwWindowShouldClose(window)) {
		renderer.Clear();
		imgui.NewFrame();
		if (editor_mode) {
			editor->OnUpdate(0.0f);
			editor->OnRender();
			ImGui::ShowDemoWindow();
			editor->OnImGuiRender();
		} else if (current_test) {
			current_test->OnUpdate(0.0f);
			current_test->OnRender();
			imgui.Begin("Test");
			if (current_test != test_menu && ImGui::Button("<-")) {
				delete current_test;
				current_test = test_menu;
				shader.Bind();
			}
			current_test->OnImGuiRender();
			imgui.End();
			imgui.Render();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}

