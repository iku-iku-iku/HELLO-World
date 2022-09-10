#include "VertexBuffer.h"
#include "Rendering/Renderer.h"

VertexBuffer::VertexBuffer() {
    GLCALL(glGenBuffers(1, &m_id))
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id))
}

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    GLCALL(glGenBuffers(1, &m_id));
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id))
    GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW))
}

VertexBuffer::~VertexBuffer() {
    GLCALL(glDeleteBuffers(1, &m_id))
}

void VertexBuffer::Bind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void VertexBuffer::UnBind() const {
    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::SetData(const void *data, unsigned int size) {
    Bind();

    GLCALL(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data))
}

void VertexBuffer::Allocate(const unsigned int MaxBufferSize) {
    Bind();

    m_MaxBufferSize = MaxBufferSize;
    GLCALL(glBufferData(GL_ARRAY_BUFFER, MaxBufferSize, nullptr, GL_DYNAMIC_DRAW))
}
