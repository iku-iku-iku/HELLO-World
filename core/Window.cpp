#include "core/Log.h"
#include <GLFW/glfw3.h>
#include "core/Window.h"

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
        /* Initialize the library */
        const int initRes = glfwInit();
        REQUIRE(initRes != 0)

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        /* Create a windowed mode window and its OpenGL context */

        int w, h;
        GetPrimaryMonitorSize(w, h);
        m_Window = CreateWindow(w / 1, h / 1);
        REQUIRE(m_Window != nullptr)

        InitWindow(m_Window);

        GetFrameBufferSize(w, h);
        SUCCEED("Window Init, Width: %d, Height: %d", w, h)
    }

    void Window::GetFrameBufferSize(int &width, int &height) const {
        glfwGetFramebufferSize(m_Window, &width, &height);
    }

    float Window::GetWidthHeightRatio() const {
        int width, height;
        GetFrameBufferSize(width, height);
        return static_cast<float>(width) / static_cast<float>(height);
    }

    void Window::GetPrimaryMonitorSize(int &width, int &height) {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *monitorMode = glfwGetVideoMode(monitor);
        width = monitorMode->width;
        height = monitorMode->height;
    }

    GLFWwindow *Window::CreateWindow(int width, int height) {
        GLFWwindow* window;
        window = glfwCreateWindow(width, height, "HELLO", nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            return nullptr;
        }
        return window;
    }

    void Window::InitWindow(GLFWwindow *window) {
        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        glfwSwapInterval(1);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    }
} // namespace core
