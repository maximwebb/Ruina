#include "Test.h"

namespace test {
	TestMenu::TestMenu(Test*& current_test_ptr, bool& editor_mode, const GuiManager& gui_manager)
		: m_current_test(current_test_ptr), editor_mode(editor_mode), gui_manager(gui_manager) {};

	void TestMenu::OnImGuiRender() {
		for (auto& test : m_tests) {
			if (ImGui::Button(test.first.c_str())) {
				m_current_test = test.second();
			}
		}
		ImGui::PushStyleColor(ImGuiCol_Button, {0.298, 0.686, 0.314, 1.0});
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, {0.298, 0.75, 0.314, 1.0});
		if (ImGui::Button("Editor Mode", {100, 50})) {
			editor_mode = true;
		}
		ImGui::PopStyleColor(2);
	}
}