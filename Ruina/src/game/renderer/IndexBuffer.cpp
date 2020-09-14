#include "IndexBuffer.h"
#include <GL/glew.h>
#include <iostream>

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_count(count) {
	glGenBuffers(1, &m_rendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	std::cout << "Destroyed index buffer" << std::endl;
	glDeleteBuffers(1, &m_rendererID);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
