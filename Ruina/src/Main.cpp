#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <fstream>
#include "Renderer.h"

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

//static const std::string GetSeverity(GLenum severity) {
//	if (severity == GL_DEBUG_SEVERITY_HIGH_AMD) {
//		return "HIGH";
//	}
//	else if (severity == GL_DEBUG_SEVERITY_MEDIUM_AMD) {
//		return "MEDIUM";
//	}
//	else if (severity == GL_DEBUG_SEVERITY_LOW_AMD) {
//		return "LOW";
//	}
//	
//	return "NONE";
//}
//
//static int __stdcall LogErrorInfo(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
//	const std::string severity_name = GetSeverity(severity);
//	if (severity_name != "NONE") {
//		std::cout << "[OpenGL Error] Severity: " << severity_name << std::endl << message << std::endl;
//		__debugbreak();
//	}
//	return 0;
//}

static std::string ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream ss;

	while (getline(stream, line)) {
		ss << line << '\n';
	}

	return ss.str();
}

static unsigned int CompileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));

		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "Vertex Shader " : "Fragment Shader ") << ":(" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();

	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

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

	/*std::array<float, 6> data = {
		-0.5f, -0.5f,
		 0.0f,  0.7f,
		 0.5f, -0.5f
	};*/

	float data[] = {
		-0.5f, -0.5f, // 0
		 0.5f, -0.5f, // 1
		 0.5f,  0.5f, // 2
		-0.5f,  0.5f  // 3
	};

	float data1[] = {
		 0.0f, -0.3f, // 0
		 0.5f, -0.3f, // 1
		 0.5f,  0.5f, // 2
		 0.0f,  0.5f  // 3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/* Vertex buffer setup */
	unsigned int buffer1;
	glGenBuffers(1, &buffer1);
	glBindBuffer(GL_ARRAY_BUFFER, buffer1);
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	/* Index buffer setup */
	unsigned int ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    std::string fragmentShader = ParseShader("Ruina/res/shaders/Fragment.shader");
    std::string vertexShader = ParseShader("Ruina/res/shaders/Vertex.shader");

	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	int location = glGetUniformLocation(shader, "u_Color");
	ASSERT(location != -1);
	glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);


	ColorWheel colorWheel(1.0f, 0.0f, 0.0f, 0.05f);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		colorWheel.Shift();
		glUniform4f(location, colorWheel.r, colorWheel.g, colorWheel.b, 1.0f);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}