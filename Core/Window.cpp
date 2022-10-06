#include "Core/Window.h"
#include <GLFW/glfw3.h>
#include "Core/Log.h"

namespace core
{
    Window::Window()
    {
        Init();
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::Update()
    {
        /* Swap front and back buffers */
        glfwSwapBuffers(m_Window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    void Window::Init()
    {
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

        m_Window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
        if (!m_Window)
        {
            glfwTerminate();
            IsValid = false;
            return;
        }
        /* Make the window's context current */
        glfwMakeContextCurrent(m_Window);

        glfwSwapInterval(1);

        glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        LOG("Init Window")
    }

    void Window::GetFrameBufferSize(int& width, int& height){ 
        glfwGetFramebufferSize(m_Window, &width, &height);
    }
} // namespace core
