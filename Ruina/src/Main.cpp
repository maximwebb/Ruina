#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>
#include <TestColorQuad.h>
#include <TestTexture2D.h>
#include <TestSimpleBatchRender.h>
#include <TestColorBatchRender.h>
#include <TestTextureBatchRender.h>
#include "Renderer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gui/Gui.h"
#include "tests/Test.h"
#include "tests/TestClearColor.h"

int main()
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 960, "Triangle Renderer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
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

	/* Initialise starting test to the test menu */
	test::Test* current_test;
	auto* test_menu = new test::TestMenu(current_test, imgui);
	current_test = test_menu;

	/* Add tests to the test menu */
	test_menu->RegisterTest<test::TestClearColor>("Clear Color");
	test_menu->RegisterTest<test::TestColorQuad>("Colored Square");
	test_menu->RegisterTest<test::TestTexture2D>("2D Textured Square");
	test_menu->RegisterTest<test::TestSimpleBatchRender>("Simple Batch Render");
	test_menu->RegisterTest<test::TestColorBatchRender>("Color Batch Render");
	test_menu->RegisterTest<test::TestTextureBatchRender>("Texture Batch Render");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
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