//
// Created by code4love on 2022/9/5.
//

#ifndef HELLO_TESTCLEARCOLOR_H
#define HELLO_TESTCLEARCOLOR_H

#include "Test.h"

namespace test {
    class TestClearColor : public Test {
    public:
        TestClearColor();

        ~TestClearColor() override;

        void OnUpdate(float deltaTime) override;

        void OnRender(float currentTime) override;

        void OnImGuiRender() override;
    private:
        float  m_ClearColor[4];
    };
}

#endif //HELLO_TESTCLEARCOLOR_H
