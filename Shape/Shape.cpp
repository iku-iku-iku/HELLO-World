//
// Created by code4love on 2022/9/10.
//

#include "Shape.h"
#include "glm/gtc/matrix_transform.hpp"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

glm::mat4 Shape::GetModelMatrix() const {
    glm::mat4 model = glm::mat4(1.f);
    model *= glm::translate(glm::mat4(1.f), m_Translation);
    model *= glm::rotate(glm::mat4(1.f), m_Rotation.z, glm::vec3(0.f, 0.f, 1.f));
    model *= glm::rotate(glm::mat4(1.f), m_Rotation.y, glm::vec3(0.f, 1.f, 0.f));
    model *= glm::rotate(glm::mat4(1.f), m_Rotation.x, glm::vec3(1.f, 0.f, 0.f));
    model *= glm::scale(glm::mat4(1.f), m_Scale);
    return model;
}

void Shape::SetData(VertexBuffer &vb, IndexBuffer &ib) {
    UpdateData();
    vb.SetData(m_Data.VertexData, m_Data.VertexDataSize);
    ib.SetData(m_Data.IndexData, m_Data.IndexCount);
}
