//
// Created by code4love on 2022/9/10.
//

#include "Plane.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace {
    float VertexData[] = {
            //  x     y    z     u    v    normal xyz
            0.5f, 0.001f, 0.5f, 1.f, 0.f, 0.f, 1.f, 0.f,
            -0.5f, 0.001f, 0.5f, 0.f, 0.f, 0.f, 1.f, 0.f,
            0.5f, 0.001f, -0.5f, 1.f, 1.f, 0.f, 1.f, 0.f,
            -0.5f, 0.001f, -0.5f, 0.f, 1.f, 0.f, 1.f, 0.f,
            0.5f, 0.f, 0.5f, 1.f, 0.f, 0.f, -1.f, 0.f,
            -0.5f, 0.f, 0.5f, 0.f, 0.f, 0.f, -1.f, 0.f,
            0.5f, 0.f, -0.5f, 1.f, 1.f, 0.f, -1.f, 0.f,
            -0.5f, 0.f, -0.5f, 0.f, 1.f, 0.f, -1.f, 0.f,
    };
    unsigned int Indices[] = {
            0, 1, 2,
            3, 2, 1,
            4, 5, 6,
            7, 6, 5,
    };
}

namespace core {

    Plane::Plane() {
        m_MeshData.IndexData = Indices;
        m_MeshData.IndexCount = sizeof(Indices) / sizeof(Indices[0]);
        m_MeshData.VertexData = VertexData;
        m_MeshData.VertexDataSize = sizeof(VertexData);

        m_Transform.SetScale(5.f, 1.f, 5.f);
        m_Transform.AddTranslation(0.f, -2.f, 0.f);
    }
}
