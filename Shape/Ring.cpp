//
// Created by code4love on 2022/9/10.
//

#include "Ring.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

namespace {
    using glm::sin, glm::cos;
}

void Ring::OnImGuiRender() {
    Shape::OnImGuiRender();
    ImGui::SliderFloat3("Ring Position", &m_Translation.x, -10.f, 10.f);
    ImGui::SliderFloat3("Ring Rotation", &m_Rotation.x, -M_PI, M_PI);
    ImGui::SliderInt("Ring Points Count", &m_RingPointsCnt, 3, m_MaxRingPointCnt);
    ImGui::SliderInt("Circle Points Count", &m_CirclePointsCnt, 3, m_MaxCirclePointCnt);
    ImGui::SliderFloat("Circle Radius", &m_CircleRadius, 0.f, 1.f);
    ImGui::SliderFloat("Ring Radius", &m_RingRadius, 0.f, 1.f);
}

glm::mat4 Ring::GetModelMatrix() const {
    glm::mat4 model = glm::mat4(1.f);
    model *= glm::translate(glm::mat4(1.f), m_Translation);
    model *= glm::rotate(glm::mat4(1.f), m_Rotation.z, glm::vec3(0.f, 0.f, 1.f));
    model *= glm::rotate(glm::mat4(1.f), m_Rotation.y, glm::vec3(0.f, 1.f, 0.f));
    model *= glm::rotate(glm::mat4(1.f), m_Rotation.x, glm::vec3(1.f, 0.f, 0.f));
    return model;
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
}

void Ring::SetData(VertexBuffer &vb, IndexBuffer &ib) {
    UpdateData();
    vb.SetData(m_RingVertexData.data(), m_RingVertexData.size() * sizeof(m_RingVertexData[0]));
    ib.SetData(m_RingIndices.data(), m_RingIndices.size());
}
