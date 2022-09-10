//
// Created by code4love on 2022/9/6.
//

#include "TestLight.h"
#include "imgui.h"

namespace {
    float globalAmbient[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
    float lightAmbient[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float lightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float lightSpecular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float lightPos[3] = {2.f, 2.f, 2.f};
    float goldAmbient[4] ={ 0.2473f, 0.1995f, 0.0745f, 1 };
    float goldDiffuse[4] ={ 0.7516f, 0.6065f, 0.2265f, 1 };
    float goldSpecular[4] = { 0.6283f, 0.5559f, 0.3661f, 1 };
    float goldShininess = 51.2f;
}

test::TestLight::~TestLight() = default;

void test::TestLight::OnUpdate(float deltaTime) {
    Test::OnUpdate(deltaTime);
}

void test::TestLight::OnRender(float currentTime) {
    Test::OnRender(0.f);

    m_Ring.SetData(*m_VertexBuffer, *m_IndexBuffer);

    {
        m_Shader->Bind();
        m_Texture->Bind();
        glm::mat4 mv = m_Camera.GetView() * m_Ring.GetModelMatrix();
        glm::mat4 mvp = m_Camera.GetProjection() * mv;
        m_Shader->SetUniformMat4f("u_V", m_Camera.GetView());
        m_Shader->SetUniformMat4f("u_MV", mv);
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
}

void test::TestLight::OnImGuiRender() {
    Test::OnImGuiRender();

    m_Camera.OnImGuiRender();
    m_Ring.OnImGuiRender();

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
}

test::TestLight::TestLight() {
    m_VertexBuffer = std::make_unique<VertexBuffer>();
    m_VertexBuffer->Allocate(m_Ring.GetMaxBufferSize());

    m_IndexBuffer = std::make_unique<IndexBuffer>();
    m_IndexBuffer->Allocate(m_Ring.GetMaxIndexCnt());

    m_VertexArray = std::make_unique<VertexArray>();
    m_VertexArray->AddBuffer(*m_VertexBuffer, m_Ring.GetLayout());

    m_Shader = std::make_unique<Shader>("../shaders/test_light.shader");

    m_Texture = std::make_unique<Texture>("../texture/wall.jpg");
    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);
    m_Shader->SetUniform4fv("u_Light.ambient", lightAmbient);
    m_Shader->SetUniform4fv("u_Light.diffuse", lightDiffuse);
    m_Shader->SetUniform4fv("u_Light.specular", lightSpecular);
    m_Shader->SetUniform3fv("u_Light.position", lightPos);
    m_Shader->SetUniform4fv("u_GlobalAmbient", globalAmbient);
    m_Shader->SetUniform4fv("u_Material.ambient", goldAmbient);
    m_Shader->SetUniform4fv("u_Material.diffuse", goldDiffuse);
    m_Shader->SetUniform4fv("u_Material.specular", goldSpecular);
    m_Shader->SetUniform1f("u_Material.shininess", goldShininess);

    m_Renderer = std::make_unique<Renderer>();

    m_VertexArray->UnBind();
    m_Shader->UnBind();
    m_IndexBuffer->UnBind();
    m_VertexBuffer->UnBind();
}
