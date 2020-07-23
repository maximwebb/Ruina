#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>
#include "Renderer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "gui/Gui.h"
#include "tests/Test.h"
#include "tests/TestClearColor.h"

class ColorWheel {
private:
	const int deltas[18] = {
			0, 1, 0,
			-1, 0, 0,
			0, 0, 1,
			0, -1, 0,
			1, 0, 0,
		 0,  0, -1
	};

	/*
		State: Which colour is currently increasing/decreasing
		Count: Progress through current colour change
		Range: Maximum value of count before it resets
		Step: How much a colour changes each update (=1/range)
	*/
	int state = 0, count = 0, range;
	float step;
public:
	float r, g, b;

	ColorWheel(float r, float g, float b, float step) : 
		r(r), g(g), b(b), step(step), range(1.0f / (float)step) {};

	void Shift() {
		if (count > range) {
			count = 0;
			state = (state + 1) % 6;
		}
		r += deltas[0 + state * 3] * step;
		g += deltas[1 + state * 3] * step;
		b += deltas[2 + state * 3] * step;
		count++;
	}
};

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


	// First two floats are x-y coords, next two are texture coordinates (in range [0, 1]^2).
	float data[] = {
			-30.0f, -30.0f, 0.0f, 0.0f, // 0
			 30.0f, -30.0f, 1.0f, 0.0f, // 1
			 30.0f,  30.0f, 1.0f, 1.0f, // 2
			-30.0f,  30.0f, 0.0f, 1.0f  // 3
	};

	unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Vertex array setup */
	VertexArray va;
	VertexBuffer vb(data, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2); //Add attribute layouts here.
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	/* Index buffer setup */
	IndexBuffer ib(indices, 6);

	/* MVP matrix construction */
	glm::mat4 proj = glm::ortho(-100.0f, 100.0f, -75.0f, 75.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4 (1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	/* Shader setup */
	Shader shader("Ruina/res/shaders/Vertex.shader", "Ruina/res/shaders/Fragment.shader");
	shader.Bind();
	shader.SetUniformMat4("u_MVP", proj * view);
	shader.SetUniform4f("u_color", 1.0f, 0.0f, 0.0f, 1.0f);

	Texture texture("Ruina/res/textures/texture.png");
	texture.Bind();
	shader.SetUniform1i("u_texture", 0);


	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	ColorWheel colorWheel(1.0f, 0.0f, 0.0f, 0.05f);
	Renderer renderer;

	/* ImGui setup */
	GuiManager imgui(window);
	ImVec4* square_color = new ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	ImVec4* pos1 = new ImVec4(0.0f, 0.0f, 0.0f, 0.0f);

	bool is_color = true;

	/* Initialise starting test to the test menu */
	test::Test* current_test;
	test::TestMenu* test_menu = new test::TestMenu(current_test, imgui);
	current_test = test_menu;

	/* Add tests to the test menu */
	test_menu->RegisterTest<test::TestClearColor>("Clear Color");

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		renderer.Clear();
		shader.Bind();


		if (current_test) {
			current_test->OnUpdate(0.0f);
			current_test->OnRender();
			test_menu->gui_manager.Begin("Test");
			if (current_test != test_menu && ImGui::Button("<-")) {
				delete current_test;
				current_test = test_menu;
			}
			current_test->OnImGuiRender();

			test_menu->gui_manager.Render();
		}

		colorWheel.Shift();

		shader.SetUniform1i("u_is_color", is_color);
		shader.SetUniform4f("u_color", square_color->x, square_color->y, square_color->z, square_color->w);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}