#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <editor/Editor.h>
#include "Debugger.h"
#include "TestClearColor.h"
#include "TestColorQuad.h"
#include "TestECS.h"
#include "TestECSRender.h"
#include "TestSimpleBatchRender.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        std::cout << "hi" << std::endl;
}

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
//	GuiManager editor_imgui(window);

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
//	test_menu->RegisterTest<test::TestECSRender>("ECS Render");

	Editor* editor = new Editor(editor_mode, imgui);

    glfwSetKeyCallback(window, key_callback);

	while (!glfwWindowShouldClose(window)) {
		renderer.Clear();
		if (editor_mode) {
			editor->gui_manager.Begin("Editor", {50, 50});
			editor->OnUpdate(0.0f);
			editor->OnRender();
			editor->OnImGuiRender();
			editor->gui_manager.Render();
			editor->gui_manager.Begin("Second", {50, 250});
			if (ImGui::Button("asdf")) {
				std::cout << "asdf" << std::endl;
			}
			editor->gui_manager.Render();
		} else if (current_test) {
			current_test->OnUpdate(0.0f);
			current_test->OnRender();
			test_menu->gui_manager.Begin("Test");
			if (current_test != test_menu && ImGui::Button("<-")) {
				delete current_test;
				current_test = test_menu;
				shader.Bind();
			}
			current_test->OnImGuiRender();

			test_menu->gui_manager.Render();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}

