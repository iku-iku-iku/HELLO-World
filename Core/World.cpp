//
// Created by iku-iku-iku on 2022/10/2.
//

#include "World.h"
#include "Core/Log.h"
namespace
{
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

namespace core
{

    World::World()
    {
        PreInit();
        Init();
        PostInit();
    }

    void World::PreInit()
    {
        m_Window = std::make_unique<Window>();
        if (!m_Window->IsValid) { LOG("fail to init window") }

        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            LOG("glew init failed!")
        }

        // gl setting
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);
        glDisable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        LOG("PreInit")
    }

    void World::Init()
    {
        m_Cameras.emplace_back(std::make_unique<Camera>());
        m_Player = std::make_unique<Player>();
        m_Player->SetCamera(m_Cameras[0].get());

        LOG("Init")
    }

    void World::PostInit()
    {
        m_VertexBuffer = std::make_unique<VertexBuffer>();
        m_VertexBuffer->Allocate(m_Ring.GetMaxBufferSize());

        m_IndexBuffer = std::make_unique<IndexBuffer>();
        m_IndexBuffer->Allocate(m_Ring.GetMaxIndexCnt());

        m_VertexArray = std::make_unique<VertexArray>();
        m_VertexArray->SetBuffer(*m_VertexBuffer, m_Ring.GetLayout());

        m_Shader1 = std::make_unique<Shader>("../shaders/test_shadow1.shader");
        m_Shader2 = std::make_unique<Shader>("../shaders/test_shadow2.shader");

        m_Shader2->SetUniform4fv("u_Light.ambient", lightAmbient);
        m_Shader2->SetUniform4fv("u_Light.diffuse", lightDiffuse);
        m_Shader2->SetUniform4fv("u_Light.specular", lightSpecular);
        m_Shader2->SetUniform3fv("u_Light.position", lightPos);
        m_Shader2->SetUniform4fv("u_GlobalAmbient", globalAmbient);
        m_Shader2->SetUniform4fv("u_Material.ambient", goldAmbient);
        m_Shader2->SetUniform4fv("u_Material.diffuse", goldDiffuse);
        m_Shader2->SetUniform4fv("u_Material.specular", goldSpecular);
        m_Shader2->SetUniform1f("u_Material.shininess", goldShininess);

        m_Renderer = std::make_unique<Renderer>();

        m_FrameBuffer = std::make_unique<FrameBuffer>();
        m_DepthMap = Texture::DepthTexture();

        m_FrameBuffer->Bind();
        m_FrameBuffer->AttachDepth(*m_DepthMap);
        m_FrameBuffer->DisableDraw();
        m_FrameBuffer->DisableRead();
        m_FrameBuffer->UnBind();

        m_Shader2->SetUniform1i("shTex", (int)m_DepthMap->GetSlot());

        LOG("PostInit")
    }

    void World::Update()
    {
        Editor::ProcessInput(m_Window->GetWindow());
        OnRender();
        m_Window->Update();
    }

    void World::OnRender()
    {
        GLCALL(glClear(GL_COLOR_BUFFER_BIT))
        GLCALL(glClearColor(0.f, 0.f, 0.f, 1.f))
        GLCALL(glClear(GL_DEPTH_BUFFER_BIT))
        float currentTime = 0.f;
        m_FrameBuffer->Bind();
        m_FrameBuffer->ClearDepthBuffer();

        glm::mat4 lightProj = GetPlayerCamera()->GetProjection();
        glm::mat4 lightView = glm::lookAt(glm::vec3(lightPos[0], lightPos[1], lightPos[2]), glm::vec3(0.f, 0.f, 0.f),
                                          glm::vec3(0.f, 1.f, 0.f));

        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(2.f, 4.f);
        {
            m_Shader1->Bind();
            glm::mat4 view = lightView;
            glm::mat4 proj = lightProj;
            {
                m_Ring.SetData(*m_VertexBuffer, *m_IndexBuffer);
                glm::mat4 mvp = proj * view * m_Ring.GetModelMatrix();
                m_Shader1->SetUniformMat4f("u_MVP", mvp);
                m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader1);
            }

            {
                m_Plane.SetData(*m_VertexBuffer, *m_IndexBuffer);
                glm::mat4 mvp = proj * view * m_Plane.GetModelMatrix();
                m_Shader1->SetUniformMat4f("u_MVP", mvp);
                m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader1);
            }
        }
        m_FrameBuffer->UnBind();

        glm::mat4 view = GetPlayerCamera()->GetView();
        glm::mat4 proj = GetPlayerCamera()->GetProjection();

        glDisable(GL_POLYGON_OFFSET_FILL);
        m_Shader2->Bind();
        {
            m_Ring.SetData(*m_VertexBuffer, *m_IndexBuffer);
            glm::mat4 mv = view * m_Ring.GetModelMatrix();
            glm::mat4 mvp = proj * mv;
            m_Shader2->SetUniformMat4f("u_V", view);
            m_Shader2->SetUniformMat4f("u_MV", mv);
            m_Shader2->SetUniformMat4f("u_MVP", mvp);
            m_Shader2->SetUniformMat4f("shadowMVP", lightProj * lightView * m_Ring.GetModelMatrix());

            m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader2);
        }

        {
            m_Plane.SetData(*m_VertexBuffer, *m_IndexBuffer);
            glm::mat4 mv = view * m_Plane.GetModelMatrix();
            glm::mat4 mvp = proj * mv;
            m_Shader2->SetUniformMat4f("u_V", view);
            m_Shader2->SetUniformMat4f("u_MV", mv);
            m_Shader2->SetUniformMat4f("u_MVP", mvp);
            m_Shader2->SetUniformMat4f("shadowMVP", lightProj * lightView * m_Plane.GetModelMatrix());

            m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader2);
        }
    }
}
