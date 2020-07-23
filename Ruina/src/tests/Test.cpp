#include "Test.h"

namespace test {
	TestMenu::TestMenu(Test*& current_test_ptr, const GuiManager& gui_manager)
		: m_current_test(current_test_ptr), gui_manager(gui_manager) {};

	void TestMenu::OnImGuiRender() {
		for (auto& test : m_tests) {
			/* TODO: Figure out how to use the GuiButton class to achieve this - maybe by passing m_current_test into
			 * 	     the lambda?
			 */
			if (ImGui::Button(test.first.c_str())) {
				m_current_test = test.second();
			}
		}
	}
}