#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Rendering/Renderer.h"
#include "imgui.h"
#include "imgui_impl_glfw_gl3.h"
#include "test/TestClearColor.h"
#include "TestMenu.h"
#include "TestTexture2D.h"
#include "TestPlanet.h"
#include "TestRing.h"
#include "TestLight.h"

GLFWwindow *window;
int main() {
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        std::cout << "glew init failed!" << std::endl;
    }

    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
    GLCALL(glEnable(GL_BLEND))
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    {
        ImGui::CreateContext();
        ImGui_ImplGlfwGL3_Init(window, true);
        ImGui::StyleColorsDark();

        test::TestMenu test;
        test.RegisterTest<test::TestClearColor>("Test Clear Color");
        test.RegisterTest<test::TestTexture2D>("Test Texture 2D");
        test.RegisterTest<test::TestPlanet>("Test Planet");
        test.RegisterTest<test::TestRing>("Test Ring");
        test.RegisterTest<test::TestLight>("Test Light");

        float time = 0.f;
        while (!glfwWindowShouldClose(window)) {
            time += 0.01f;
            glfwPollEvents();

            test.OnUpdate(0.f);
            test.OnRender(time);

            ImGui_ImplGlfwGL3_NewFrame();
            test.OnImGuiRender();
            ImGui::Render();
            ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    // Cleanup
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}