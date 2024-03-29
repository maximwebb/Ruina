#pragma once
#include <functional>
#include <vector>
#include <GL/glew.h>
#include "Gui.h"
#include "../game/renderer/VertexArray.h"
#include "../game/renderer/IndexBuffer.h"
#include "../Shader.h"
#include "../Renderer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>

namespace test {
	class Test {
	public:
		Test() {}
		virtual ~Test() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {
			glClearColor(0.11f, 0.11f, 0.11f, 1.0f);
//			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*&, bool&, const GuiManager&);
		~TestMenu() {}
		void OnImGuiRender() override;

		template <typename T>
		void RegisterTest(const std::string& name) {
			m_tests.push_back(std::make_pair(name, [](){return new T(); }));
		}

		void RegisterTest(Test* test, const std::string& name) {
		    m_tests.emplace_back(name, [test](){return test;});
		}
	public:
		GuiManager gui_manager;
	private:
		Test*& m_current_test;
		bool& editor_mode;

		/* Stores a list of names and lambdas that return test pointers.
		 * This allows us to instantiate and destroy tests while using the menu, instead of "activating" them.
		 */
		std::vector<std::pair<std::string, std::function<Test*()>>> m_tests;
	};
}