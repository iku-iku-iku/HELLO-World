//
// Created by code4love on 2022/9/10.
//

#include "Plane.h"
#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

void Plane::OnImGuiRender() {
    Shape::OnImGuiRender();
    ImGui::SliderFloat3("Plane Position", &m_Translation.x, -10.f, 10.f);
    ImGui::SliderFloat3("Plane Rotation", &m_Rotation.x, -M_PI, M_PI);

    ImGui::SliderFloat("Scale X", &m_Scale1, 0.f, 10.f);
    ImGui::SliderFloat("Scale Y", &m_Scale2, 0.f, 10.f);
}

glm::mat4 Plane::GetModelMatrix() const {
    glm::mat4 model = glm::mat4(1.f);
    model *= glm::translate(glm::mat4(1.f), m_Translation);
    model *= glm::rotate(glm::mat4(1.f), m_Rotation.z, glm::vec3(0.f, 0.f, 1.f));
    model *= glm::rotate(glm::mat4(1.f), m_Rotation.y, glm::vec3(0.f, 1.f, 0.f));
    model *= glm::rotate(glm::mat4(1.f), m_Rotation.x, glm::vec3(1.f, 0.f, 0.f));
    model *= glm::scale(glm::mat4(1.f), glm::vec3(m_Scale1, 1.f, m_Scale2));
    return model;
}


void Plane::SetData(VertexBuffer &vb, IndexBuffer &ib) {
    vb.SetData(m_PlaneVertexData, sizeof(m_PlaneVertexData));
    ib.SetData(m_PlaneIndices, sizeof(m_PlaneIndices) / sizeof(m_PlaneIndices[0]));
}

Plane::Plane() : m_PlaneVertexData{
        0.5f, 0.f, 0.5f, 1.f, 0.f, 0.f, 1.f, 0.f,
        -0.5f, 0.f, 0.5f, 0.f, 0.f, 0.f, 1.f, 0.f,
        0.5f, 0.f, -0.5f, 1.f, 1.f, 0.f, 1.f, 0.f,
        -0.5f, 0.f, -0.5f, 0.f, 1.f, 0.f, 1.f, 0.f,
}, m_PlaneIndices{
        0, 1, 2,
        3, 2, 1,
} {

}
