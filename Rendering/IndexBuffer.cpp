#include "IndexBuffer.h"
#include "Rendering/Renderer.h"

IndexBuffer::IndexBuffer() {
    GLCALL(glGenBuffers(1, &m_id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_Count(count) {
    GLCALL(glGenBuffers(1, &m_id));
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(IndexType), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() {
    GLCALL(glDeleteBuffers(1, &m_id))
}

void IndexBuffer::Bind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void IndexBuffer::UnBind() const {
    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::SetData(const unsigned int *data, unsigned int count) {
    Bind();

    m_Count = count;

    GLCALL(glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, count * sizeof(IndexType), data))
}

void IndexBuffer::Allocate(const unsigned int MaxIndexCnt) {
    Bind();

    m_MaxIndexCnt = MaxIndexCnt;
    GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxIndexCnt * sizeof(IndexType), nullptr, GL_DYNAMIC_DRAW));
}
