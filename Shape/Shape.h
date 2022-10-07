//
// Created by code4love on 2022/9/10.
//

#pragma once

#include "glm/glm.hpp"
#include "MeshData.h"
#include "RenderingHeaders.h"

class Shape
{
public:
    const MeshData &GetData() const { return m_Data; }
    glm::mat4 GetModelMatrix() const;

    virtual void SetData(class VertexBuffer &vb, class IndexBuffer &ib) = 0;
    virtual ~Shape() = default;

protected:
    MeshData m_Data;

    glm::vec3 m_Rotation{};

    glm::vec3 m_Translation{};

    glm::vec3 m_Scale{1.f, 1.f, 1.f};
};
