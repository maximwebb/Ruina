#pragma once
#include <GL/glew.h>

class VertexBuffer {
public:
	VertexBuffer(const void *data, unsigned int size);
	VertexBuffer(VertexBuffer&&) noexcept;
	~VertexBuffer();
	void Bind() const;
	void Unbind();

private:
	unsigned int m_rendererID;
};