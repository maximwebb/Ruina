#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept {
	m_rendererID = other.m_rendererID;

	other.m_rendererID = 0;
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_rendererID);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
