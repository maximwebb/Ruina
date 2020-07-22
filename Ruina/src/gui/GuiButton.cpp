#include "IGuiElement.h"
#include <functional>

class GuiButton : public IGuiElement {
private:
	const char* m_text;
	const std::function<void()> m_action;
public:
	GuiButton(const char* text, const std::function<void()>& action)
		: m_text(text), m_action(action) {};

	void Draw() override {
		if (ImGui::Button(m_text)) {
			m_action();
		}
	}
};