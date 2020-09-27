#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Debugger.h"
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

	test::Test* current_test;
	auto* test_menu = new test::TestMenu(current_test, imgui);
	current_test = test_menu;

	test_menu->RegisterTest<test::TestClearColor>("Clear Color");
	test_menu->RegisterTest<test::TestColorQuad>("Colored Square");
	test_menu->RegisterTest<test::TestSimpleBatchRender>("Simple Batch Render");
	test_menu->RegisterTest<test::TestECS>("ECS");
	test_menu->RegisterTest<test::TestECSRender>("ECS Render");

	while (!glfwWindowShouldClose(window)) {
		renderer.Clear();
		if (current_test) {
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