#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
public:
	VertexArray();
	VertexArray(VertexArray&&) noexcept;
	~VertexArray();
	void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);
	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_rendererID;
};