//
// Created by code4love on 2022/9/10.
//

#pragma once

#include "glm/glm.hpp"
#include "ShapeStruct.h"
#include "core/Type.h"
#include "GraphicsAPI.h"

namespace core {

    class Shape {
    public:
        const MeshData &GetData() const { return m_MeshData; }

        glm::mat4 GetModelMatrix() const;

        void SetData(VertexBuffer &vb, IndexBuffer &ib);

        virtual ~Shape() = default;

        virtual void UpdateData() {}

        void GenerateAABB();

        bool IntersectWithRay(glm::vec3 origin, glm::vec3 direction) const;

        const AABB &GetAABB() const { return m_AABB; }

        void AddTranslation(float dx, float dy, float dz);

        Transform &GetTransform() { return m_Transform; }

    protected:
        MeshData m_MeshData;

        AABB m_AABB;

        Transform m_Transform;
    };
}
