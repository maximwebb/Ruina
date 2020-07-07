#include "VertexArray.h"
#include "Debugger.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_rendererID);
	glBindVertexArray(m_rendererID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_rendererID);
}

void VertexArray::AddBuffer(const VertexBuffer &vbo, const VertexBufferLayout &layout) {
	Bind();
	vbo.Bind();
	unsigned int offset = 0;
	const auto &layout_elements = layout.GetElements();
	for (int i = 0; i < layout_elements.size(); i++) {
		const auto &element = layout_elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),
							  (const void *) offset);
		offset += element.count * VertexBufferElement::GetTypeSize(element.type);
	}
	Unbind();
}

void VertexArray::Bind() const {
	glBindVertexArray(m_rendererID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}
