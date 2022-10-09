#include "Core/Log.h"
#include <GLFW/glfw3.h>
#include "Core/Window.h"

namespace core {
    Window::Window() {
        Init();
    }

    Window::~Window() {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::Update() {
        /* Swap front and back buffers */
        glfwSwapBuffers(m_Window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    void Window::Init() {
        IsValid = true;

        /* Initialize the library */
        if (!glfwInit()) {
            IsValid = false;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        /* Create a windowed mode window and its OpenGL context */

        m_Window = glfwCreateWindow(Width, Height, "HELLO", nullptr, nullptr);
        if (!m_Window) {
            glfwTerminate();
            IsValid = false;
            return;
        }
        /* Make the window's context current */
        glfwMakeContextCurrent(m_Window);

        glfwSwapInterval(1);

        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        int w, h; GetFrameBufferSize(w, h);
        SUCCEED("Init Window, Width: %d, Height: %d", w, h)
    }

    void Window::GetFrameBufferSize(int &width, int &height) const {
        glfwGetFramebufferSize(m_Window, &width, &height);
    }

    float Window::GetWidthHeightRatio() const {
        int width, height;
        GetFrameBufferSize(width, height);
        return static_cast<float>(width) / static_cast<float>(height);
    }

    void Window::GetPrimaryMonitorSize(int &width, int &height) const {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *monitorMode = glfwGetVideoMode(monitor);
        width = monitorMode->width;
        height = monitorMode->height;
    }
} // namespace core
