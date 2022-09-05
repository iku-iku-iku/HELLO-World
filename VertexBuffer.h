#ifndef __VERTEXBUFFER__H_
#define __VERTEXBUFFER__H_

class VertexBuffer
{
private:
    unsigned int m_id;

public:
    VertexBuffer(const void *data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void UnBind() const;
};

#endif