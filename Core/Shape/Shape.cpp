//
// Created by code4love on 2022/9/10.
//

#include "Shape.h"
#include "OpenGLAPI.h"

namespace core {
    glm::mat4 Shape::GetModelMatrix() const {
        return m_Transform.GetModelMatrix();
    }

    void Shape::SetData(rhi::VertexBuffer &vb, rhi::IndexBuffer &ib) {
        UpdateData();
        vb.SetData(m_MeshData.VertexData, m_MeshData.VertexDataSize);
        ib.SetData(m_MeshData.IndexData, m_MeshData.IndexCount);
    }

    void Shape::GenerateAABB() {
        unsigned int vertexCount = m_MeshData.VertexDataSize / sizeof(m_MeshData.VertexData[0]);
        m_AABB.XMin = m_AABB.YMin = m_AABB.ZMin = 1e9;
        m_AABB.XMax = m_AABB.YMax = m_AABB.ZMax = -1e9;
        for (int i = 0; i < vertexCount / 8; i++) {
            float x = m_MeshData.VertexData[i * 8];
            float y = m_MeshData.VertexData[i * 8 + 1];
            float z = m_MeshData.VertexData[i * 8 + 2];

            auto XYZ = m_Transform.GetModelMatrix() * glm::vec4(x, y, z, 1.f);
            x = XYZ.x;
            y = XYZ.y;
            z = XYZ.z;

            if (x < m_AABB.XMin) { m_AABB.XMin = x; }
            if (y < m_AABB.YMin) { m_AABB.YMin = y; }
            if (z < m_AABB.ZMin) { m_AABB.ZMin = z; }

            if (x > m_AABB.XMax) { m_AABB.XMax = x; }
            if (y > m_AABB.YMax) { m_AABB.YMax = y; }
            if (z > m_AABB.ZMax) { m_AABB.ZMax = z; }
        }
    }

    bool Shape::IntersectWithRay(glm::vec3 origin, glm::vec3 direction) const {
        float tMinX = (m_AABB.XMin - origin.x) / direction.x;
        float tMinY = (m_AABB.YMin - origin.y) / direction.y;
        float tMinZ = (m_AABB.ZMin - origin.z) / direction.z;

        float tMaxX = (m_AABB.XMax - origin.x) / direction.x;
        float tMaxY = (m_AABB.YMax - origin.y) / direction.y;
        float tMaxZ = (m_AABB.ZMax - origin.z) / direction.z;

        if (tMinX > tMaxX) { std::swap(tMinX, tMaxX); }
        if (tMinY > tMaxY) { std::swap(tMinY, tMaxY); }
        if (tMinZ > tMaxZ) { std::swap(tMinZ, tMaxZ); }

        float tMin = std::max(tMinX, std::max(tMinY, tMinZ));
        float tMax = std::min(tMaxX, std::min(tMaxY, tMaxZ));

        return tMin < tMax && tMax >= 0;
    }

    void Shape::AddTranslation(float dx, float dy, float dz) {
        m_Transform.AddTranslation(dx, dy, dz);
    }
}
