#include <iostream>
#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


const char *GetErrorMsg(GLenum err) {
    switch (err) {
        case 0x0500:
            return "GL_INVALID_ENUM";
        case 0x0501:
            return "GL_INVALID_VALUE";
        case 0x0502:
            return "GL_INVALID_OPERATION";
        case 0x0503:
            return "GL_STACK_OVERFLOW";
        case 0x0504:
            return "GL_STACK_UNDERFLOW";
        case 0x0505:
            return "GL_OUT_OF_MEMORY";

        default:
            return "UNKNOWN ERROR";
    }
}

void GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

void GLCheckError(const char *function, const char *file, int line) {
    while (GLenum err = glGetError()) {
        std::cout << "[OpenGL Error] ("
                  << err << ":" << GetErrorMsg(err) << "): "
                  << function << " " << file << ":" << line
                  << std::endl;
    }
}

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() {
    GLCALL(glClear(GL_COLOR_BUFFER_BIT))
}

void Renderer::ClearColor() {
    GLCALL(glClearColor(0.f, 0.f, 0.f, 1.f))
}
