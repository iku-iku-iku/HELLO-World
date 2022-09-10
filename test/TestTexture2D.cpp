//
// Created by code4love on 2022/9/6.
//

#include "TestTexture2D.h"
#include "imgui.h"

test::TestTexture2D::~TestTexture2D() {

}

void test::TestTexture2D::OnUpdate(float deltaTime) {
    Test::OnUpdate(deltaTime);
}

void test::TestTexture2D::OnRender(float currentTime) {

    Test::OnRender(0.f);

    {
        m_Shader->Bind();
        m_Texture->Bind();
        glm::mat4 model = glm::translate(glm::mat4(1.f), m_Translation);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
}

void test::TestTexture2D::OnImGuiRender() {
    Test::OnImGuiRender();

    ImGui::SliderFloat3("Translation", &m_Translation.x, 0.f, 1.f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
}

test::TestTexture2D::TestTexture2D() {
    float positions[] = {
            0.5f, 0.5f, 1.f, 1.f,
            -0.5f, 0.5f, 0.f, 1.f,
            -0.5f, -0.5f, 0.f, 0.f,
            0.5f, -0.5f, 1.f, 0.f};

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};

    m_VertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));

    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);

    m_VertexArray = std::make_unique<VertexArray>();
    m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    m_View = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
    m_Proj = glm::ortho(-2.f, 2.f, -1.5f, 1.5f, -1.f, 1.f);

    m_Shader = std::make_unique<Shader>("../shaders/test_texture.shader");

    m_Texture = std::make_unique<Texture>("../texture/flower.png");
    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);

    m_Translation = glm::vec3(0.f, 0.f, 0);

    m_Renderer = std::make_unique<Renderer>();

    m_VertexArray->UnBind();
    m_Shader->UnBind();
    m_IndexBuffer->UnBind();
    m_VertexBuffer->UnBind();
}
