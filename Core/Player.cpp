//
// Created by iku-iku-iku on 2022/10/2.
//

#include <iostream>
#include "Player.h"

core::Player::~Player() {
    if (Editor::OnInput().RemoveListener(InputKey)) {
        std::cout << "Remove Successfully" << std::endl;
    }
}

core::Player::Player() :
        InputKey([this](const Editor::InputContext &inputContext) { this->InputKeyHandler(inputContext); }) {
    Editor::OnInput().AddListener(InputKey);
}

void core::Player::InputKeyHandler(const Editor::InputContext &inputContext) {
    const Editor::KeyStatus &keyStatus = inputContext.keyStatus;
    const Editor::Cursor &cursor = inputContext.cursor;

    float delta = m_CameraTranslateSpeed;
    if (keyStatus.W) {
        glm::vec3 dir = m_CameraTranslateSpeed * m_Camera->GetDirection();
        m_Camera->AddTranslation(dir.x, dir.y, dir.z);
    }
    if (keyStatus.S) {
        glm::vec3 dir = -m_CameraTranslateSpeed * m_Camera->GetDirection();
        m_Camera->AddTranslation(dir.x, dir.y, dir.z);
    }
    if (keyStatus.A) {
        glm::vec3 dir = -m_CameraTranslateSpeed * m_Camera->GetRight();
        m_Camera->AddTranslation(dir.x, dir.y, dir.z);
    }
    if (keyStatus.D) {
        glm::vec3 dir = m_CameraTranslateSpeed * m_Camera->GetRight();
        m_Camera->AddTranslation(dir.x, dir.y, dir.z);
    }
    if (keyStatus.Q) {
        m_Camera->AddTranslation(0, -delta, 0);
    }
    if (keyStatus.E) {
        m_Camera->AddTranslation(0, delta, 0);
    }
    if (keyStatus.M_R) {
        if (!m_IsMLPressing) {
            m_IsMLPressing = true;
            m_MLPressBeginCursorX = cursor.xPos;
            m_MLPressBeginCursorY = cursor.yPos;
            m_MLPressBeginPitch = m_Camera->GetRotation().Pitch;
            m_MLPressBeginYaw = m_Camera->GetRotation().Yaw;
        } else {
            const float Ratio = 0.05f;
            float deltaCursorX = -(cursor.xPos - m_MLPressBeginCursorX) * Ratio;
            float deltaCursorY = -(cursor.yPos - m_MLPressBeginCursorY) * Ratio;
            m_Camera->GetRotation().SetPitch(deltaCursorY * m_CameraRotateSpeed + m_MLPressBeginPitch);
            m_Camera->GetRotation().SetYaw(deltaCursorX * m_CameraRotateSpeed + m_MLPressBeginYaw);
        }
    } else {
        m_IsMLPressing = false;
    }
}
