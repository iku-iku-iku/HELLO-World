#pragma once

class VertexBuffer {
private:
    unsigned int m_id;

public:
    VertexBuffer(const void *data, unsigned int size);

    VertexBuffer();

    ~VertexBuffer();

    void Allocate(const unsigned int MaxBufferSize);

    void SetData(const void *data, unsigned int size);

    void Bind() const;

    void UnBind() const;

private:
    unsigned int m_MaxBufferSize;
};