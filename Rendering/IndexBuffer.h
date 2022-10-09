#pragma once

class IndexBuffer {
    typedef unsigned int IndexType;
private:
    unsigned int m_id;
    unsigned int m_Count;

public:
    IndexBuffer(const unsigned int *data, unsigned int count);

    IndexBuffer();

    ~IndexBuffer();

    void Bind() const;

    void UnBind() const;

    void Allocate(const unsigned int MaxIndexCnt);

    void SetData(const unsigned int *data, unsigned int count);

    inline unsigned int GetCount() const { return m_Count; }

private:
    unsigned int m_MaxIndexCnt;
};
