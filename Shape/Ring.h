//
// Created by code4love on 2022/9/10.
//

#ifndef HELLO_RING_H
#define HELLO_RING_H

#include "MeshData.h"
#include <vector>
#include "Shape.h"
#include "glm/glm.hpp"
#include "VertexBufferLayout.h"

class Ring : public Shape {
public:
    ~Ring() = default;

    void SetData(class VertexBuffer &vb, class IndexBuffer &ib);

private:
    float m_CircleRadius = .2f;
    float m_RingRadius = .6f;

    int m_RingPointsCnt = 20;
    int m_CirclePointsCnt = 20;

    const int m_MaxRingPointCnt = 100;
    const int m_MaxCirclePointCnt = 100;

    std::vector<float> m_RingVertexData;
    std::vector<unsigned int> m_RingIndices;

    void UpdateData();
};

#endif //HELLO_RING_H
