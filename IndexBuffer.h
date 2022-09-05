#ifndef __INDEXBUFFER__H_
#define __INDEXBUFFER__H_

class IndexBuffer
{
private:
    unsigned int m_id;
    unsigned int m_count;

public:
    IndexBuffer(const unsigned int *data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void UnBind() const;

    inline unsigned int GetCount() { return m_count; }
};

#endif