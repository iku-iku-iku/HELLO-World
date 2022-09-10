//
// Created by code4love on 2022/9/5.
//

#ifndef HELLO_TEST_H
#define HELLO_TEST_H

#include "Rendering/Renderer.h"

namespace test {
    class Test {
    public:
        Test() {}

        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}

        virtual void OnRender(float currentTime) {
            GLCALL(glClear(GL_COLOR_BUFFER_BIT))
            GLCALL(glClearColor(0.f, 0.f, 0.f, 1.f))
            GLCALL(glClear(GL_DEPTH_BUFFER_BIT))
        }

        virtual void OnImGuiRender() {}
    };
}

#endif //HELLO_TEST_H
