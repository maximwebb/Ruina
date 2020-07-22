#pragma once

#include <iostream>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class IGuiElement {
public:
	virtual void Draw() {
		std::cout << "Drawing lol" << std::endl;
	}
};

