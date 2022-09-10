//
// Created by code4love on 2022/9/10.
//

#ifndef HELLO_RING_H
#define HELLO_RING_H

#include <vector>
#include "Shape.h"
#include "glm/glm.hpp"
#include "VertexBufferLayout.h"

class Ring : public Shape {
public:
    void OnImGuiRender() override;

    glm::mat4 GetModelMatrix() const;

    void SetData(class VertexBuffer &vb, class IndexBuffer &ib);

    unsigned int GetMaxBufferSize() const {
        return (m_MaxRingPointCnt + 1) * (m_MaxCirclePointCnt + 1) * 5 * sizeof(float);
    }

    unsigned int GetMaxIndexCnt() const {
        return m_MaxRingPointCnt * m_MaxCirclePointCnt * 6;
    }

    VertexBufferLayout GetLayout() const {
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        return layout;
    }

private:
    glm::vec3 m_Rotation{};

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
