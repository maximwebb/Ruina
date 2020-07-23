#include "TestClearColor.h"

namespace test {
	TestClearColor::TestClearColor()
		: m_clear_color{1.0f, 0.0f, 0.0f, 1.0f} {};

	TestClearColor::~TestClearColor() {

	}

	void TestClearColor::OnUpdate(float deltaTime) {

	}

	void TestClearColor::OnRender() {
		glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestClearColor::OnImGuiRender() {
		GuiColorPicker color_picker("Clear Color", (ImVec4*)m_clear_color);
		color_picker.Draw();
	}
}
