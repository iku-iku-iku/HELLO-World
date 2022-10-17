//
// Created by code4love on 2022/9/10.
//

#ifndef HELLO_RING_H
#define HELLO_RING_H

#include "ShapeStruct.h"
#include <vector>
#include "Shape.h"
#include "glm/glm.hpp"

namespace core {

    class Ring : public Shape {
    public:
        ~Ring() override = default;

    private:
        float m_CircleRadius = .2f;
        float m_RingRadius = .6f;

        int m_RingPointsCnt = 20;
        int m_CirclePointsCnt = 30;

        std::vector<float> m_RingVertexData;
        std::vector<unsigned int> m_RingIndices;

        void UpdateData() override;
    };

}
#endif //HELLO_RING_H
