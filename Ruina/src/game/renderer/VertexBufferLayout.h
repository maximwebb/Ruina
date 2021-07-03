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
//				throw std::exception();
                throw std::exception((const std::exception&) "Invalid VertexBuffer element type.");
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


    void PushFloat(int count) {
        m_elements.push_back({(unsigned int) count, GL_FLOAT, GL_FALSE});
        m_stride += VertexBufferElement::GetTypeSize(GL_FLOAT) * count;
    }

    void PushUInt(int count) {
        m_elements.push_back({(unsigned int) count, GL_UNSIGNED_INT, GL_FALSE});
        m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT) * count;
    }

    void PushUChar(int count) {
        m_elements.push_back({(unsigned int) count, GL_UNSIGNED_BYTE, GL_TRUE});
        m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE) * count;
    }

//    void Push(int count);

    inline const std::vector<VertexBufferElement>& GetElements() const { return m_elements; }

    inline unsigned int GetStride() const { return m_stride; }

private:
    std::vector<VertexBufferElement> m_elements;

    unsigned int m_stride;
};

//template<>
//void VertexBufferLayout::Push<float>(int count) {
//    m_elements.push_back({(unsigned int) count, GL_FLOAT, GL_FALSE});
//    m_stride += VertexBufferElement::GetTypeSize(GL_FLOAT) * count;
//}

//template<>
//void VertexBufferLayout::Push<unsigned int>(int count) {
//    m_elements.push_back({(unsigned int) count, GL_UNSIGNED_INT, GL_FALSE});
//    m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT) * count;
//}
//
//template<>
//void VertexBufferLayout::Push<unsigned char>(int count) {
//    m_elements.push_back({(unsigned int) count, GL_UNSIGNED_BYTE, GL_TRUE});
//    m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE) * count;
//}

