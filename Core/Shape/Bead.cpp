//
// Created by code4love on 2022/10/9.
//

#include "Bead.h"

namespace {
    float VertexData[] = {
            // x        y
            -0.5f, -0.5f, 0, 0, 0, 0, 0, 0,
            0.5f, -0.5f, 0, 0, 0, 0, 0, 0,
            0.5f, 0.5f, 0, 0, 0, 0, 0, 0,
            -0.5f, 0.5f, 0, 0, 0, 0, 0, 0,
    };
    unsigned int Indices[] = {
            1, 0, 2,
            3, 2, 0,
    };
}

namespace core {

    Bead::Bead() {
        m_MeshData.IndexCount = 6;
        m_MeshData.IndexData = Indices;
        m_MeshData.VertexData = VertexData;
        m_MeshData.VertexDataSize = sizeof(VertexData);

        m_Transform.Scale *= 0.15f;
    }
}
