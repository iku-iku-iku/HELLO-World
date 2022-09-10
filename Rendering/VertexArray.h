#pragma once

class VertexArray
{
private:
    unsigned int m_id;
public:
    VertexArray(/* args */);
    ~VertexArray();

    void Bind() const;
    void UnBind();

    void AddBuffer(const class VertexBuffer& vb, const class VertexBufferLayout& layout);
};
