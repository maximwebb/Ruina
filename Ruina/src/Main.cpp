#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class ColorWheel {
private:
	const int deltas[18] = {
		 0,  1,  0,
		-1,  0,  0,
		 0,  0,  1,
		 0, -1,  0,
		 1,  0,  0,
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

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback((GLDEBUGPROC)LogErrorInfo, nullptr);


	float data[] = {
			-0.5f, -0.5f, // 0
			0.5f, -0.5f, // 1
			0.5f, 0.5f, // 2
			-0.5f, 0.5f  // 3
	};

	unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
	};

	/* Vertex array setup */
	VertexArray va;
	VertexBuffer vb(data, 4 * 2 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(2); //Add attribute layouts here.
	va.AddBuffer(vb, layout);

	/* Index buffer setup */
	IndexBuffer ib(indices, 6);

	/* Shader setup */
	Shader shader("Ruina/res/shaders/Vertex.shader", "Ruina/res/shaders/Fragment.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	ColorWheel colorWheel(1.0f, 0.0f, 0.0f, 0.05f);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Bind();
		va.Bind();
		ib.Bind();


		colorWheel.Shift();
		shader.SetUniform4f("u_color", colorWheel.r, colorWheel.g, colorWheel.b, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}