#include "IGuiElement.h"

class GuiCheckbox : public IGuiElement {
private:
	const char* m_title;
	bool* m_option;
public:
	GuiCheckbox(const char* title, bool& option)
		: m_title(title), m_option(&option) {};

	void Draw() override {
		ImGui::Checkbox(m_title, m_option);
	}
};