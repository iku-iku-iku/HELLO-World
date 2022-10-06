//
// Created by iku-iku-iku on 2022/10/2.
//


#pragma once

#include <Editor/Input.h>
#include "Camera.h"

namespace core {

    class Player {
    public:
        Player();;

        ~Player();

        core::Listener<Editor::InputContext> InputKey;

        void InputKeyHandler(const Editor::InputContext &inputContext);

        void SetCamera(Camera *camera) { m_Camera = camera; }

        Camera *GetCamera() { return m_Camera; }

    private:
        Camera *m_Camera;

        float m_CameraTranslateSpeed = 0.1f;
        float m_CameraRotateSpeed = 0.1f;

        bool m_IsMLPressing = false;
        float m_MLPressBeginCursorX;
        float m_MLPressBeginYaw;
        float m_MLPressBeginCursorY;
        float m_MLPressBeginPitch;
    };
}
