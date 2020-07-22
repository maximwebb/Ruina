#include "IGuiElement.h"

class GuiColorPicker : public IGuiElement {
private:
	const char* m_title;
	ImVec4 m_color;
public:
	GuiColorPicker(const char* title, ImVec4& color)
		: m_title(title), m_color(color) {};

	void Draw() override {
		ImGui::ColorEdit3(m_title, (float*)&m_color);
	}
};