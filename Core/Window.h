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

        void GetFrameBufferSize(int& width, int& height) const;

        void GetPrimaryMonitorSize(int& width, int& height) const;

        float GetWidthHeightRatio() const;
    private:
        GLFWwindow *m_Window;

        void Init();

        const int Width = 840;
        const int Height = 580;
    };
} // namespace core
