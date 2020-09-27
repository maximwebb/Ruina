#pragma once
#include <GL/glew.h>
#include <vector>

struct VertexBufferElement {
	static unsigned int GetTypeSize(unsigned int type) {
		switch (type) {
			case GL_FLOAT:
				return 4;
			case GL_UNSIGNED_INT:
				return 4;
			case GL_UNSIGNED_BYTE:
				return 1;
			default:
				throw std::exception("Invalid VertexBuffer element type.");
		}
	}

	unsigned int count;
	unsigned int type;
	unsigned int normalized;
};


class VertexBufferLayout {
public:
	VertexBufferLayout()
			: m_stride(0) {};

	template<typename T>
	void Push(int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(int count) {
		m_elements.push_back({(unsigned int) count, GL_FLOAT, GL_FALSE});
		m_stride += VertexBufferElement::GetTypeSize(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(int count) {
		m_elements.push_back({(unsigned int) count, GL_UNSIGNED_INT, GL_FALSE});
		m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(int count) {
		m_elements.push_back({(unsigned int) count, GL_UNSIGNED_BYTE, GL_TRUE});
		m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE) * count;
	}

	inline const std::vector<VertexBufferElement> &GetElements() const { return m_elements; }
	inline unsigned int GetStride() const { return m_stride; }

private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_stride;
};