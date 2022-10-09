//
// Created by code4love on 2022/10/9.
//

#include "Bead.h"

namespace {
    float VertexData[] = {
            // x        y
            -0.5f, -0.5f, 0, 0, 0, 0, 0, 0,
            0.5f, -0.5f,0, 0, 0, 0, 0, 0,
            0.5f, 0.5f,0, 0, 0, 0, 0, 0,
            -0.5f, 0.5f,0, 0, 0, 0, 0, 0,
    };
    unsigned int Indices[] = {
            1, 0, 2,
            3, 2, 0,
    };
}

Bead::Bead() {
    m_Data.IndexCount = 6;
    m_Data.IndexData = Indices;
    m_Data.VertexData = VertexData;
    m_Data.VertexDataSize = sizeof(VertexData);

    m_Scale *= 0.15f;
}
