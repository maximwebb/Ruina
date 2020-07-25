#include "IGuiElement.h"

class GuiTripleSlider : public IGuiElement {
private:
	const char* m_title;
	float* m_values;
public:
	GuiTripleSlider(const char* title, float* values)
			: m_title(title), m_values(values) {};

	void Draw() override {
		ImGui::SliderFloat3(m_title, m_values, -100.0f, 100.0f);
	}
};