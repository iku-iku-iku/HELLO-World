//
// Created by code4love on 2022/9/5.
//
#include "imgui.h"
#include "TestMenu.h"

test::TestMenu::~TestMenu() {
}

void test::TestMenu::OnUpdate(float deltaTime) {
    Test::OnUpdate(deltaTime);

    if (currentTest != nullptr) {
        currentTest->OnUpdate(deltaTime);
    }
}

void test::TestMenu::OnRender(float currentTime) {
    Test::OnRender(currentTime);

    if (currentTest != nullptr) {
        currentTest->OnRender(currentTime);
    }
}

void test::TestMenu::OnImGuiRender() {
    Test::OnImGuiRender();

    ImGui::Begin("Test");

    ImGui::SetWindowSize({400, 300});
    if (currentTest != nullptr) {
        if (ImGui::Button("back")) {
            currentTest = nullptr;
        } else {
            currentTest->OnImGuiRender();
        }
    } else {
        for (const auto &option: testOptions) {
            if (ImGui::Button(option.first)) {
                currentTest = option.second();
            }
        }
    }
    ImGui::End();
}
