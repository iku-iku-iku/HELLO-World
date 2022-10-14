//
// Created by iku-iku-iku on 2022/10/2.
//


#pragma once

#include <functional>
#include <unordered_set>
#include "Core/Event.h"

class GLFWwindow;
namespace Editor {
    struct KeyStatus {
        typedef unsigned char uint8;
        uint8 K_W: 1;
        uint8 K_S: 1;
        uint8 K_A: 1;
        uint8 K_D: 1;
        uint8 K_Q: 1;
        uint8 K_E: 1;
        uint8 K_M_L: 1;
        uint8 K_M_R: 1;
        uint8 K_ESCAPE: 1;
        uint8 K_1 : 1;
        uint8 K_2 : 1;
        uint8 K_3 : 1;
    };

    struct Cursor {
        float xPos;
        float yPos;
    };

    typedef struct {
        KeyStatus keyStatus;
        Cursor cursor;
    } InputContext;

    class Input {
    public:
        typedef core::Event<InputContext> InputEvent;

        KeyStatus &GetKeyStatus() { return m_InputContext.keyStatus; }

        Cursor &GetCursor() { return m_InputContext.cursor; }

        static Input &Get() {
            static Input Instance;
            return Instance;
        }

        InputEvent &GetInputEvent() { return m_InputEvent; }

        void BroadcastInput() { m_InputEvent.Broadcast(m_InputContext); }

    private:
        InputContext m_InputContext{};

        InputEvent m_InputEvent;

        Input() = default;
    };
}
namespace Editor {

    void ProcessInput(GLFWwindow *window);

    void GetKey(GLFWwindow *window);

    void GetCursor(GLFWwindow *window);

    Input::InputEvent &OnInput();
}
