#pragma once
#include <glm/glm.hpp>
#include "RenderingHeaders.h"

class Cube
{
public:
    Cube(/* args */);
    ~Cube() = default;

    glm::mat4 GetModelMatrix() const;

    void SetData(class VertexBuffer &vb, class IndexBuffer &ib);

    unsigned int GetMaxBufferSize() const {
        return VERT_COUNT * VERTEX_ATTRIBUTE_COUNT * sizeof(float);
    }

    unsigned int GetMaxIndexCnt() const {
        return INDEX_COUNT;
    }

    VertexBufferLayout GetLayout() const {
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        layout.Push<float>(3);
        return layout;
    }

private:
    glm::vec3 m_Rotation{};
    glm::vec3 m_Translation{0.f, 0.f, 0.f};

    float m_Scale = 3.f;

    static constexpr unsigned int VERTEX_ATTRIBUTE_COUNT = 8;
    static constexpr unsigned int VERT_COUNT = 24;
    static constexpr unsigned int INDEX_COUNT = 36;

    float m_VertexData[VERTEX_ATTRIBUTE_COUNT * VERT_COUNT];
    unsigned int m_Indices[INDEX_COUNT];
};