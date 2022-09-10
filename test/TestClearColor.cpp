//
// Created by code4love on 2022/9/5.
//

#include "TestClearColor.h"
#include "Rendering/Renderer.h"
#include "imgui.h"

namespace test {

    test::TestClearColor::TestClearColor() : m_ClearColor {1.f, 0.f, 0.f, 1.f} {}

    test::TestClearColor::~TestClearColor() {

    }

    void test::TestClearColor::OnUpdate(float deltaTime) {
        Test::OnUpdate(deltaTime);
    }

    void test::TestClearColor::OnRender(float currentTime) {
        Test::OnRender(0.f);

        GLCALL(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]))
        GLCALL(glClear(GL_COLOR_BUFFER_BIT))
    }

    void test::TestClearColor::OnImGuiRender() {
        Test::OnImGuiRender();

        ImGui::ColorEdit4("Clear Color", m_ClearColor);
    }
}
