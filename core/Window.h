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

        void GetFrameBufferSize(int& width, int& height) const;

        static void GetPrimaryMonitorSize(int& width, int& height) ;

        float GetWidthHeightRatio() const;

    private:
        GLFWwindow *m_Window;

        void Init();

        const int Width = 840;
        const int Height = 580;

        static GLFWwindow *CreateWindow(int width, int height);

        static void InitWindow(GLFWwindow* window);
    };
} // namespace core
