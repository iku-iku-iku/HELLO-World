#include <iostream>
#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Core/World.h"

namespace {
    float globalAmbient[4] = {0.7f, 0.7f, 0.7f, 1.0f};
    float lightAmbient[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float lightDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightSpecular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float lightPos[3] = {2.f, 2.f, 2.f};
    float goldAmbient[4] = {0.2473f, 0.1995f, 0.0745f, 1};
    float goldDiffuse[4] = {0.7516f, 0.6065f, 0.2265f, 1};
    float goldSpecular[4] = {0.6283f, 0.5559f, 0.3661f, 1};
    float goldShininess = 51.2f;
}

void Renderer::Render(const Shader &shader) const {
    shader.Bind();
    m_VertexArray->Bind();
    m_IndexBuffer->Bind();
    GLCALL(glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() {
    GLCALL(glClear(GL_COLOR_BUFFER_BIT))
}

void Renderer::ClearColor() {
    GLCALL(glClearColor(0.f, 0.f, 0.f, 1.f))
}

Renderer::Renderer() {
    InitOpenGLEnv();
    // Init vertex buffer
    m_VertexBuffer = std::make_unique<VertexBuffer>();
    m_VertexBuffer->Allocate(100000);

    // Init index buffer
    m_IndexBuffer = std::make_unique<IndexBuffer>();
    m_IndexBuffer->Allocate(10000);

    // Init vertex array
    m_VertexArray = std::make_unique<VertexArray>();
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<float>(3);
    m_VertexArray->SetBuffer(*m_VertexBuffer, layout);

    // Init frame buffer
    m_FrameBuffer = std::make_unique<FrameBuffer>();

    // Init depth map
    m_DepthMap = Texture::CreateDepthTexture();

    m_FrameBuffer->Bind();
    m_FrameBuffer->AttachDepth(*m_DepthMap);
    m_FrameBuffer->DisableDraw();
    m_FrameBuffer->DisableRead();
    m_FrameBuffer->UnBind();

    // Init shader used for rendering depth map
    m_DepthRenderingShader = std::make_unique<Shader>("../shaders/test_shadow1.shader");

    SUCCEED("Renderer Init")
}

void Renderer::RenderDepthMap() {
    GLCALL(glClear(GL_DEPTH_BUFFER_BIT))

    m_FrameBuffer->Bind();
    m_FrameBuffer->ClearDepthBuffer();

    glm::mat4 lightProj = world.GetPlayerCamera()->GetPerspectiveProjection();
    glm::mat4 lightView = glm::lookAt(glm::vec3(lightPos[0], lightPos[1], lightPos[2]), glm::vec3(0.f, 0.f, 0.f),
                                      glm::vec3(0.f, 1.f, 0.f));

    // avoid z-fighting when two face are too close
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2.f, 4.f);
    ////
    {
        m_DepthRenderingShader->Bind();
        glm::mat4 view = lightView;
        glm::mat4 proj = lightProj;

        for (const auto &shape: world.GetShapes()) {
            shape->SetData(*m_VertexBuffer, *m_IndexBuffer);
            glm::mat4 mvp = proj * view * shape->GetModelMatrix();
            m_DepthRenderingShader->SetUniformMat4f("u_MVP", mvp);
            Render(*m_DepthRenderingShader);
        }
    }
    m_FrameBuffer->UnBind();
    glDisable(GL_POLYGON_OFFSET_FILL);
}

void Renderer::RenderShape(Shape &shape, const Shader &shader) {
    shape.SetData(*m_VertexBuffer, *m_IndexBuffer);
    Render(shader);
}

void Renderer::InitOpenGLEnv() {
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        ERROR("glew init failed!")
    }

    // gl setting
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    SUCCEED("Init OpenGL Environment")
}

