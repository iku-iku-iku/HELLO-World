#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
    unsigned int m_id;
public:
    VertexArray(/* args */);
    ~VertexArray();

    void Bind() const;
    void UnBind();

    void SetBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);
};
