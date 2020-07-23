#include "IGuiElement.h"

class GuiTripleSlider : public IGuiElement {
private:
	const char* m_title;
	ImVec4* m_values;
public:
	GuiTripleSlider(const char* title, ImVec4* values)
			: m_title(title), m_values(values) {};

	void Draw() override {
		ImGui::SliderFloat3(m_title, (float*)m_values, -100.0f, 100.0f);
	}
};