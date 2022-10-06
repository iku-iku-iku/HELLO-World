//
// Created by code4love on 2022/9/6.
//

#include "TestRing.h"
#include "imgui.h"

test::TestRing::~TestRing() = default;

void test::TestRing::OnUpdate(float deltaTime) {
    Test::OnUpdate(deltaTime);
}

void test::TestRing::OnRender(float currentTime) {

    Test::OnRender(0.f);

    m_Ring.SetData(*m_VertexBuffer, *m_IndexBuffer);

    {
        m_Shader->Bind();
        m_Texture->Bind();
        glm::mat4 mvp = m_Camera.GetProjectionView() * m_Ring.GetModelMatrix();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
}

void test::TestRing::OnImGuiRender() {
    Test::OnImGuiRender();

    m_Camera.OnImGuiRender();
    m_Ring.OnImGuiRender();

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
}

test::TestRing::TestRing() {
    m_VertexBuffer = std::make_unique<VertexBuffer>();
    m_VertexBuffer->Allocate(m_Ring.GetMaxBufferSize());

    m_IndexBuffer = std::make_unique<IndexBuffer>();
    m_IndexBuffer->Allocate(m_Ring.GetMaxIndexCnt());

    m_VertexArray = std::make_unique<VertexArray>();
    m_VertexArray->SetBuffer(*m_VertexBuffer, m_Ring.GetLayout());

    m_Shader = std::make_unique<Shader>("../shaders/test_ring.shader");

    m_Texture = std::make_unique<Texture>("../texture/wall.jpg");
    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);

    m_Renderer = std::make_unique<Renderer>();

    m_VertexArray->UnBind();
    m_Shader->UnBind();
    m_IndexBuffer->UnBind();
    m_VertexBuffer->UnBind();
}
