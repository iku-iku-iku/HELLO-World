//
// Created by iku-iku-iku on 2022/10/2.
//

#include <iostream>
#include <stdlib.h>
#include "Core/Log.h"
#include "Player.h"
#include "World.h"

core::Player::~Player() {
    if (Editor::OnInput().RemoveListener(InputKey)) {
        SUCCEED("Remove InputKey Listener")
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

    if (keyStatus.K_1) { m_ObjectEditMode = ObjectEditMode::Translate; }
    if (keyStatus.K_2) { m_ObjectEditMode = ObjectEditMode::Rotate; }
    if (keyStatus.K_3) { m_ObjectEditMode = ObjectEditMode::Scale; }

    if (HasChosenShape()) {
        glm::vec3 *pVec;
        auto &transform = m_ChosenShape->GetTransform();
        switch (m_ObjectEditMode) {
            case ObjectEditMode::Translate:
                pVec = &transform.Translation;
                break;
            case ObjectEditMode::Rotate:
                pVec = &transform.Rotation;
                break;
            case ObjectEditMode::Scale:
                pVec = &transform.Scale;
                break;
        }

        glm::vec3 &vec = *pVec;

        if (keyStatus.K_W) {
            vec += glm::vec3(0, 0, -delta);
        }
        if (keyStatus.K_S) {
            vec += glm::vec3(0, 0, delta);
        }
        if (keyStatus.K_A) {
            vec += glm::vec3(-delta, 0, 0);
        }
        if (keyStatus.K_D) {
            vec += glm::vec3(delta, 0, 0);
        }
        if (keyStatus.K_Q) {
            vec += glm::vec3(0, -delta, 0);
        }
        if (keyStatus.K_E) {
            vec += glm::vec3(0, delta, 0);
        }
    } else {
        if (keyStatus.K_W) {
            glm::vec3 dir = m_CameraTranslateSpeed * m_Camera->GetDirection();
            m_Camera->AddTranslation(dir.x, dir.y, dir.z);
        }
        if (keyStatus.K_S) {
            glm::vec3 dir = -m_CameraTranslateSpeed * m_Camera->GetDirection();
            m_Camera->AddTranslation(dir.x, dir.y, dir.z);
        }
        if (keyStatus.K_A) {
            glm::vec3 dir = -m_CameraTranslateSpeed * m_Camera->GetRight();
            m_Camera->AddTranslation(dir.x, dir.y, dir.z);
        }
        if (keyStatus.K_D) {
            glm::vec3 dir = m_CameraTranslateSpeed * m_Camera->GetRight();
            m_Camera->AddTranslation(dir.x, dir.y, dir.z);
        }
        if (keyStatus.K_Q) {
            m_Camera->AddTranslation(0, -delta, 0);
        }
        if (keyStatus.K_E) {
            m_Camera->AddTranslation(0, delta, 0);
        }
    }
    if (keyStatus.K_ESCAPE) {
        exit(0);
    }
    if (keyStatus.K_M_L) {
        RayTrace();
    }
    if (keyStatus.K_M_R && HasChosenShape()) {
        ReleaseChosen();
    }
    if (!m_HasSettleCursor) {
        m_HasSettleCursor = true;
        m_MLPressBeginCursorX = cursor.xPos;
        m_MLPressBeginCursorY = cursor.yPos;
        m_MLPressBeginPitch = m_Camera->GetRotation().Pitch;
        m_MLPressBeginYaw = m_Camera->GetRotation().Yaw;
    } else {
        const float Ratio = 0.05f;
        float deltaCursorX = -(cursor.xPos - m_MLPressBeginCursorX) * Ratio;
        float deltaCursorY = -(cursor.yPos - m_MLPressBeginCursorY) * Ratio;
        if (!HasChosenShape()) {
            m_Camera->GetRotation().SetPitch(deltaCursorY * m_CameraRotateSpeed + m_MLPressBeginPitch);
            m_Camera->GetRotation().SetYaw(deltaCursorX * m_CameraRotateSpeed + m_MLPressBeginYaw);
        } else {
            m_HasSettleCursor = false;
        }
    }
}

void core::Player::RayTrace() {
    const auto &m_ShapeVec = world.GetShapes();
    for (const auto &item: m_ShapeVec) { item->GenerateAABB(); }
    auto Camera = GetCamera();
    for (const auto &item: m_ShapeVec) {
        if (item->IntersectWithRay(Camera->GetTranslation(), Camera->GetDirection())) {
            AABB aabb = item->GetAABB();
            SetChosenShape(item.get());
        }
    }
}
