#pragma once

class GLFWwindow;
namespace core
{
    class Window
    {
    public:
        Window();
        ~Window();
        GLFWwindow* GetWindow() {return m_Window;}
        bool ShouldClose() const;

        void Update();

        bool IsValid;

        void GetFrameBufferSize(int& width, int& height);
    private:
        GLFWwindow *m_Window;

        void Init();
    };
} // namespace core
