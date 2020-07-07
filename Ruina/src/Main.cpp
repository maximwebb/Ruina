#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>
#include "Renderer.h"
#include "Debugger.h"
#include "Texture.h"


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
	window = glfwCreateWindow(640, 480, "Triangle Renderer", NULL, NULL);
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


	float data[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, // 0
			0.5f, -0.5f, 1.0f, 0.0f, // 1
			0.5f, 0.5f, 1.0f, 1.0f, // 2
			-0.5f, 0.5f, 0.0f, 1.0f  // 3
	};

	unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
	};

	/* Vertex array setup */
	VertexArray va;
	VertexBuffer vb(data, 4 * 4 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2); //Add attribute layouts here.
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	/* Index buffer setup */
	IndexBuffer ib(indices, 6);

	/* Shader setup */
	Shader shader("Ruina/res/shaders/Vertex.shader", "Ruina/res/shaders/Fragment.shader");
	shader.Bind();
//	shader.SetUniform4f("u_color", 1.0f, 0.0f, 0.0f, 1.0f);

	Texture texture("Ruina/res/textures/texture.png");
	texture.Bind();
	shader.SetUniform1i("u_texture", 0);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	ColorWheel colorWheel(1.0f, 0.0f, 0.0f, 0.05f);
	Renderer renderer;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		renderer.Clear();

		renderer.Draw(va, ib, shader);
		//colorWheel.Shift();
		//shader.SetUniform4f("u_color", colorWheel.r, colorWheel.g, colorWheel.b, 1.0f);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}