//
// Created by code4love on 2022/9/6.
//

#include <stack>
#include "TestPlanet.h"
#include "imgui.h"


using glm::sin, glm::cos;

test::TestPlanet::~TestPlanet() {

}

void test::TestPlanet::OnUpdate(float deltaTime) {
    Test::OnUpdate(deltaTime);
}

void test::TestPlanet::OnRender(float currentTime) {
    std::stack<glm::mat4> mvStack;
    mvStack.push(m_Camera.GetView());

    mvStack.push(mvStack.top());
    mvStack.top() *= glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f)); // sun location
    mvStack.push(mvStack.top());
    mvStack.top() *= glm::rotate(glm::mat4(1.f), currentTime, glm::vec3(1.f, 0.f, 0.f));

    {
        m_Shader->Bind();
        glm::mat4 mvp = m_Camera.GetProjection() * mvStack.top();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }

    mvStack.pop();
    mvStack.push(mvStack.top());
    mvStack.top() *= glm::translate(glm::mat4(1.f), 4.f * glm::vec3(sin(currentTime), cos(currentTime), 0.f));
    mvStack.push(mvStack.top());
    mvStack.top() *= glm::rotate(glm::mat4(1.f), currentTime, glm::vec3(0.f, 1.f, 0.f));

    {
        m_Shader->Bind();
        glm::mat4 mvp = m_Camera.GetProjection() * mvStack.top();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }

    mvStack.pop();
    mvStack.push(mvStack.top());
    mvStack.top() *= glm::translate(glm::mat4(1.f), 3.f * glm::vec3(sin(currentTime), 0, cos(currentTime)));
    mvStack.push(mvStack.top());
    mvStack.top() *= glm::rotate(glm::mat4(1.f), currentTime, glm::normalize(glm::vec3(1.f, 1.f, 0.f)));

    {
        m_Shader->Bind();
        glm::mat4 mvp = m_Camera.GetProjection() * mvStack.top();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }
}

void test::TestPlanet::OnImGuiRender() {
    Test::OnImGuiRender();

    m_Camera.OnImGuiRender();

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
}

test::TestPlanet::TestPlanet() {
    float positions[] = {
            1.f, 1.f, 1.f,
            1.f, 1.f, -1.f,
            1.f, -1.f, 1.f,
            1.f, -1.f, -1.f,
            -1.f, 1.f, 1.f,
            -1.f, 1.f, -1.f,
            -1.f, -1.f, 1.f,
            -1.f, -1.f, -1.f,
    };

    unsigned int indices[] = {
            0, 1, 3,
            0, 2, 3,
            0, 1, 5,
            0, 4, 5,
            0, 2, 6,
            0, 4, 6,
            7, 3, 2,
            7, 6, 2,
            7, 5, 4,
            7, 6, 4,
            7, 3, 1,
            7, 5, 1
    };

    m_VertexBuffer = std::make_unique<VertexBuffer>(positions, sizeof(positions));

    VertexBufferLayout layout;
    layout.Push<float>(3);

    m_VertexArray = std::make_unique<VertexArray>();
    m_VertexArray->SetBuffer(*m_VertexBuffer, layout);

    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, sizeof(indices) / sizeof(indices[0]));

    m_Shader = std::make_unique<Shader>("../shaders/test_planet.shader");

    m_Renderer = std::make_unique<Renderer>();

    m_VertexArray->UnBind();
    m_Shader->UnBind();
    m_IndexBuffer->UnBind();
    m_VertexBuffer->UnBind();
}
