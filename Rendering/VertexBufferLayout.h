// #pragma once
#ifndef __VERTEXBUFFERLAYOUR__H_
#define __VERTEXBUFFERLAYOUR__H_

#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    static unsigned int GetTypeSize(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;

        case GL_UNSIGNED_INT:
            return 4;

        case GL_UNSIGNED_BYTE:
            return 1;

        default:
            return 0;
        }
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout() : m_Stride(0) {}

    template <typename T>
    void Push(unsigned int count);

    inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }
};

template <typename T>
void VertexBufferLayout::Push(unsigned int count)
{
}
template <>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back({GL_FLOAT, count, false});
    m_Stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
}

#endif