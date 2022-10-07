#include "Shape/Cube.h"
#include "glm/gtc/matrix_transform.hpp"

Cube::Cube() :
m_VertexData {
    //  x     y    z     u    v    normal xyz
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
}, m_Indices{
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
}
{}

glm::mat4 Cube::GetModelMatrix() const
{
    glm::mat4 model = glm::mat4(1.f);
    model *= glm::translate(glm::mat4(1.f), m_Translation);
    model *= glm::rotate(glm::mat4(1.f), m_Rotation.z, glm::vec3(0.f, 0.f, 1.f));
    model *= glm::rotate(glm::mat4(1.f), m_Rotation.y, glm::vec3(0.f, 1.f, 0.f));
    model *= glm::rotate(glm::mat4(1.f), m_Rotation.x, glm::vec3(1.f, 0.f, 0.f));
    model *= glm::scale(glm::mat4(1.f), glm::vec3(1.f, 1.f, 1.f) * m_Scale);
    return model;
}

void Cube::SetData(VertexBuffer &vb, IndexBuffer &ib) {
    vb.SetData(m_VertexData, sizeof(m_VertexData));
    ib.SetData(m_Indices, sizeof(m_Indices) / sizeof(m_Indices[0]));
}
