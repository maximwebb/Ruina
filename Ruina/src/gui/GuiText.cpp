#include "IGuiElement.h"

class GuiText : public IGuiElement {
	char* m_text;
public:
	explicit GuiText(char* text) : m_text(text) {};

	void Draw() override {
		ImGui::Text("%s", m_text);
	}
};