#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Rendering/Renderer.h"

VertexArray::VertexArray() {
    GLCALL(glGenVertexArrays(1, &m_id))
}

VertexArray::~VertexArray() {
    GLCALL(glDeleteVertexArrays(1, &m_id))
}

void VertexArray::Bind() const {
    GLCALL(glBindVertexArray(m_id))
}

void VertexArray::UnBind() {
    GLCALL(glBindVertexArray(0))
}

void VertexArray::SetBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    Bind();
    vb.Bind();

    unsigned int offset = 0;
    const auto &Elements = layout.GetElements();
    for (int i = 0; i < Elements.size(); i++) {
        const auto &element = Elements[i];
        GLCALL(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(),
                       reinterpret_cast<const void*>(offset)))
        GLCALL(glEnableVertexAttribArray(i))
        offset += element.count * VertexBufferElement::GetTypeSize(element.type);
    }
}