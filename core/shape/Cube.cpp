#include "glm/gtc/matrix_transform.hpp"
#include "Cube.h"

namespace {
    float VertexData[] = {
            //  x           y          z        u        v    normal xyz
            0.5f, 0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f, 0.f,
            -0.5f, 0.5f, 0.5f, 0.f, 0.f, 0.f, 1.f, 0.f,
            0.5f, 0.5f, -0.5f, 1.f, 1.f, 0.f, 1.f, 0.f,
            -0.5f, 0.5f, -0.5f, 0.f, 1.f, 0.f, 1.f, 0.f,
            0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f, -1.f, 0.f,
            -0.5f, -0.5f, 0.5f, 0.f, 0.f, 0.f, -1.f, 0.f,
            0.5f, -0.5f, -0.5f, 1.f, 1.f, 0.f, -1.f, 0.f,
            -0.5f, -0.5f, -0.5f, 0.f, 1.f, 0.f, -1.f, 0.f,
            ////////////////////////////////////////////
            0.5f, 0.5f, 0.5f, 1.f, 0.f, 1.f, 0.f, 0.f,
            0.5f, 0.5f, -0.5f, 0.f, 0.f, 1.f, 0.f, 0.f,
            0.5f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 0.f, 0.f,
            0.5f, -0.5f, -0.5f, 0.f, 1.f, 1.f, 0.f, 0.f,
            -0.5f, 0.5f, 0.5f, 1.f, 0.f, -1.f, 0.f, 0.f,
            -0.5f, 0.5f, -0.5f, 0.f, 0.f, -1.f, 0.f, 0.f,
            -0.5f, -0.5f, 0.5f, 1.f, 1.f, -1.f, 0.f, 0.f,
            -0.5f, -0.5f, -0.5f, 0.f, 1.f, -1.f, 0.f, 0.f,
            ////////////////////////////////////////////
            0.5f, 0.5f, 0.5f, 1.f, 0.f, 0.f, 0.f, 1.f,
            0.5f, -0.5f, 0.5f, 0.f, 0.f, 0.f, 0.f, 1.f,
            -0.5f, 0.5f, 0.5f, 1.f, 1.f, 0.f, 0.f, 1.f,
            -0.5f, -0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 1.f,
            0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f, 0.f, -1.f,
            0.5f, -0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, -1.f,
            -0.5f, 0.5f, -0.5f, 1.f, 1.f, 0.f, 0.f, -1.f,
            -0.5f, -0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, -1.f,
            ////////////////////////////////////////////
    };
    unsigned int Indices[] = {
            0, 1, 2,
            3, 2, 1,
            4, 5, 6,
            7, 6, 5,
            ////////
            8, 9, 10,
            11, 10, 9,
            12, 13, 14,
            15, 14, 13,
            ////////
            16, 17, 18,
            19, 18, 17,
            20, 21, 22,
            23, 22, 21,
            ////////
    };
}

namespace core {

    Cube::Cube() {
        m_MeshData.VertexData = VertexData;
        m_MeshData.IndexData = Indices;
        m_MeshData.VertexDataSize = sizeof(VertexData);
        m_MeshData.IndexCount = sizeof(Indices) / sizeof(Indices[0]);
    }
}
