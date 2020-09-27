#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_count(count) {
	glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept {
	m_rendererID = other.m_rendererID;
	m_count = other.m_count;

	other.m_rendererID = 0;
	other.m_count = 0;
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
