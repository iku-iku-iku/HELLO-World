#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include ""

int main() {
    GLFWwindow *window;

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


    float positions[] = {
            0.5f, 0.5f, 1.f, 1.f,
            -0.5f, 0.5f, 0.f, 1.f,
            -0.5f, -0.5f, 0.f, 0.f,
            0.5f, -0.5f, 1.f, 0.f};

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};

    GLCALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
    GLCALL(glEnable(GL_BLEND))


    {
        VertexBuffer vb(positions, sizeof(positions));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        VertexArray va;
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader shader("../shaders/basic.shader");

        float r = 0.f;
        float increment = 0.01f;

        Texture texture("../texture/OK.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.UnBind();
        shader.UnBind();
        ib.UnBind();
        vb.UnBind();

        Renderer renderer;

        //  Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.Clear();

            if (r > 1.f && increment > 0 || r < 0.f && increment < 0) {
                increment = -increment;
            }
            r += increment;

            shader.Bind();
//            shader.SetUniform4f("u_Color", r, 0.f, 1.f, 1.f);

            /* draw call */
            renderer.Draw(va, ib, shader);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }


    glfwTerminate();

    return 0;
}