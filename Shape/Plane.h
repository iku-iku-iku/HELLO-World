//
// Created by code4love on 2022/9/10.
//

#ifndef HELLO_PLANE_H
#define HELLO_PLANE_H

#include <vector>
#include "Shape.h"
#include "glm/glm.hpp"
#include "VertexBufferLayout.h"

class Plane : public Shape {
public:
    Plane();

    void OnImGuiRender() override;

    glm::mat4 GetModelMatrix() const;

    void SetData(class VertexBuffer &vb, class IndexBuffer &ib);

    unsigned int GetMaxBufferSize() const {
        return 4 * 8 * sizeof(float);
    }

    unsigned int GetMaxIndexCnt() const {
        return 6;
    }

    VertexBufferLayout GetLayout() const {
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);
        layout.Push<float>(3);
        return layout;
    }

private:
    glm::vec3 m_Rotation{};
    glm::vec3 m_Translation{0.f, -1.f, 0.f};

    float m_Scale1 = 5.f;
    float m_Scale2 = 5.f;

    float m_PlaneVertexData[8 * 4];
    unsigned int m_PlaneIndices[6];
};

#endif //HELLO_PLANE_H
