//
// Created by iku-iku-iku on 2022/10/2.
//


#pragma once

#include "Editor/Input.h"
#include "Camera.h"
#include "Shape.h"

namespace core {

    class Player {
    public:
        Player();;

        ~Player();

        core::Listener<Editor::InputContext> InputKey;

        void InputKeyHandler(const Editor::InputContext &inputContext);

        void SetCamera(Camera *camera) { m_Camera = camera; }

        Camera *GetCamera() { return m_Camera; }

        void SetChosenShape(Shape *shape) { m_ChosenShape = shape; }

        void ReleaseChosen() { m_ChosenShape = nullptr; }

        bool HasChosenShape() { return m_ChosenShape != nullptr; }

        void RayTrace();

    private:
        Camera *m_Camera{};

        float m_CameraTranslateSpeed = 0.1f;
        float m_CameraRotateSpeed = 0.1f;

        bool m_HasSettleCursor = false;
        float m_MLPressBeginCursorX{};
        float m_MLPressBeginYaw{};
        float m_MLPressBeginCursorY{};
        float m_MLPressBeginPitch{};

        enum class ObjectEditMode {
            Translate, Rotate, Scale
        } m_ObjectEditMode = ObjectEditMode::Translate;

        Shape *m_ChosenShape = nullptr;
    };
}
