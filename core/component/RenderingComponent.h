//
// Created by iku-iku-iku on 2022/10/17.
//


#pragma once

#include "world/World.h"
#include "Component.h"

namespace core {

    class RenderingComponent : public Component {

        void Prepare() override {

        }

        std::unique_ptr<Shape> m_Shape{};
    public:
        template<typename ShapeType>
        void SetShape() {
            world->RemoveShape(m_Shape.get());
            m_Shape = std::make_unique<ShapeType>();
            world->AddShape(m_Shape.get());
        }
    };
}
