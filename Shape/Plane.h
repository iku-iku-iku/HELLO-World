//
// Created by code4love on 2022/9/10.
//

#ifndef HELLO_PLANE_H
#define HELLO_PLANE_H

#include <vector>
#include "Shape.h"
#include "glm/glm.hpp"
#include "VertexBufferLayout.h"

class Plane : public Shape
{
public:
    Plane();

    void SetData(class VertexBuffer &vb, class IndexBuffer &ib);

private:
    static constexpr unsigned int VERTEX_ATTRIBUTE_COUNT = 8;
    static constexpr unsigned int VERT_COUNT = 8;
    static constexpr unsigned int INDEX_COUNT = 12;
};

#endif // HELLO_PLANE_H
