//
// Created by iku-iku-iku on 2022/10/2.
//

#include <GLFW/glfw3.h>
#include "Input.h"

#define SET_KEY(KEY) \
        Key = glfwGetKey(window, GLFW_KEY_##KEY); \
        switch (Key) {                           \
            case GLFW_PRESS: \
                Input::Get().GetKeyStatus().KEY = 1; \
                break;    \
            case GLFW_RELEASE:                   \
                Input::Get().GetKeyStatus().KEY = 0;  \
                break;    \
            default:  \
                break;    \
       }

namespace Editor {
    void ProcessInput(GLFWwindow *window) {
        GetKey(window);
        GetCursor(window);
        Input::Get().BroadcastInput();
    }

    void GetKey(GLFWwindow *window) {
        int Key;
        SET_KEY(W)
        SET_KEY(A)
        SET_KEY(S)
        SET_KEY(D)
        SET_KEY(Q)
        SET_KEY(E)

        Key = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
        switch (Key) {
            case GLFW_PRESS:
                Input::Get().GetKeyStatus().M_L = 1;
                break;
            case GLFW_RELEASE:
                Input::Get().GetKeyStatus().M_L = 0;
                break;
            default:
                break;
        }

        Key = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
        switch (Key) {
            case GLFW_PRESS:
                Input::Get().GetKeyStatus().M_R = 1;
                break;
            case GLFW_RELEASE:
                Input::Get().GetKeyStatus().M_R = 0;
                break;
            default:
                break;
        }
    }

    Input::InputEvent &OnInput() {
        return Input::Get().GetInputEvent();
    }

    void GetCursor(struct GLFWwindow *window) {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        Input::Get().GetCursor().xPos = (float) xPos;
        Input::Get().GetCursor().yPos = (float) yPos;
    }
}
