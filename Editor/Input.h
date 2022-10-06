//
// Created by iku-iku-iku on 2022/10/2.
//


#pragma once

#include <functional>
#include <unordered_set>
#include <Core/Event.h>


namespace Editor {
    struct KeyStatus {
        typedef unsigned char uint8;
        uint8 W: 1;
        uint8 S: 1;
        uint8 A: 1;
        uint8 D: 1;
        uint8 Q: 1;
        uint8 E: 1;
        uint8 M_L: 1;
        uint8 M_R: 1;
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

    void ProcessInput(class GLFWwindow *window);

    void GetKey(class GLFWwindow *window);

    void GetCursor(class GLFWwindow *window);

    Input::InputEvent &OnInput();
}
