#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "game/renderer/VertexArray.h"
#include "game/renderer/IndexBuffer.h"
#include "Shader.h"

class Renderer {
public:
	void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
	void DrawCube(const glm::mat4& transform, const Shader &shader) const;
	void Clear();
};