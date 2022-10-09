//
// Created by code4love on 2022/9/10.
//

#include "Ring.h"
#include "glm/gtc/matrix_transform.hpp"


namespace {
    using glm::sin, glm::cos;
}

void Ring::UpdateData() {
    m_RingVertexData.resize(0);
    m_RingIndices.resize(0);

    glm::vec3 circleCenter = {0.f, 0.f, 0.f};
    float rInterval = 2.f * (float) M_PI / (float) m_RingPointsCnt;
    float cInterval = 2.f * (float) M_PI / (float) m_CirclePointsCnt;

    for (int ri = 0; ri <= m_RingPointsCnt; ri++) {
        float rTheta = (float) ri * rInterval;
        circleCenter = {cos(rTheta) * m_RingRadius, 0, sin(rTheta) * m_RingRadius};
        for (int ci = 0; ci <= m_CirclePointsCnt; ci++) {
            float cTheta = (float) ci * cInterval;
            glm::vec3 dir = {cos(cTheta) * cos(rTheta), sin(cTheta),cos(cTheta) * sin(rTheta)};
            glm::vec3 point = circleCenter + dir * m_CircleRadius;

            m_RingVertexData.push_back(point.x);
            m_RingVertexData.push_back(point.y);
            m_RingVertexData.push_back(point.z);
            m_RingVertexData.push_back((float) ri / (float) (m_RingPointsCnt));
            m_RingVertexData.push_back((float) ci / (float) (m_CirclePointsCnt));
            glm::vec3 norm = dir;
            m_RingVertexData.push_back(norm.x);
            m_RingVertexData.push_back(norm.y);
            m_RingVertexData.push_back(norm.z);

            if (ci == 0 || ri == 0) continue;

            std::size_t curIndex = ri * (m_CirclePointsCnt + 1) + ci;
            std::size_t curPreIndex = ri * (m_CirclePointsCnt + 1) + ci - 1;
            std::size_t oppoIndex = (ri - 1) * (m_CirclePointsCnt + 1) + ci;
            std::size_t oppoPreIndex = (ri - 1) * (m_CirclePointsCnt + 1) + ci - 1;

            m_RingIndices.push_back(oppoIndex);
            m_RingIndices.push_back(curIndex);
            m_RingIndices.push_back(oppoPreIndex);

            m_RingIndices.push_back(curPreIndex);
            m_RingIndices.push_back(oppoPreIndex);
            m_RingIndices.push_back(curIndex);
        }
    }
    m_Data.IndexCount = m_RingIndices.size();
    m_Data.IndexData = m_RingIndices.data();
    m_Data.VertexData = m_RingVertexData.data();
    m_Data.VertexDataSize = m_RingVertexData.size() * sizeof(m_RingVertexData[0]);
}
