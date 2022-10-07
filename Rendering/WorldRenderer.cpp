#include "Rendering/WorldRenderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Core/World.h"
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

WorldRenderer::WorldRenderer(core::World *world) : m_World(world)
{
    PreInit();
    Init();
}

void WorldRenderer::PreInit()
{
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
}

void WorldRenderer::Init()
{
    m_VertexBuffer = std::make_unique<VertexBuffer>();
    m_VertexBuffer->Allocate(100000);

    m_IndexBuffer = std::make_unique<IndexBuffer>();
    m_IndexBuffer->Allocate(10000);

    m_VertexArray = std::make_unique<VertexArray>();

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<float>(3);
    m_VertexArray->SetBuffer(*m_VertexBuffer, layout);

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
    m_DepthMap = Texture::CreateDepthTexture();
    const char *map_path[] = {
        "../texture/right.jpg",
        "../texture/left.jpg",
        "../texture/top.jpg",
        "../texture/bottom.jpg",
        "../texture/front.jpg",
        "../texture/back.jpg",
    };
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    m_SkyboxTexture = Texture::CreateCubemap(map_path);
    m_SkyboxShader = std::make_unique<Shader>("../shaders/skybox.shader");
    m_SkyboxShader->SetUniform1i("u_Texture", (int)m_SkyboxTexture->GetSlot());

    m_FrameBuffer->Bind();
    m_FrameBuffer->AttachDepth(*m_DepthMap);
    m_FrameBuffer->DisableDraw();
    m_FrameBuffer->DisableRead();
    m_FrameBuffer->UnBind();

    m_Shader2->SetUniform1i("shTex", (int)m_DepthMap->GetSlot());
}

void WorldRenderer::OnRender()
{
    GLCALL(glClear(GL_COLOR_BUFFER_BIT))
    GLCALL(glClearColor(0.f, 0.f, 0.f, 1.f))
    GLCALL(glClear(GL_DEPTH_BUFFER_BIT))
    float currentTime = 0.f;

    m_FrameBuffer->Bind();
    m_FrameBuffer->ClearDepthBuffer();

    glm::mat4 lightProj = m_World->GetPlayerCamera()->GetProjection();
    glm::mat4 lightView = glm::lookAt(glm::vec3(lightPos[0], lightPos[1], lightPos[2]), glm::vec3(0.f, 0.f, 0.f),
                                      glm::vec3(0.f, 1.f, 0.f));

    // avoid z-fighting when two face are too close
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2.f, 4.f);
    ////
    {
        m_Shader1->Bind();
        glm::mat4 view = lightView;
        glm::mat4 proj = lightProj;

        for (const auto &shape : m_World->GetShapes())
        {
            shape->SetData(*m_VertexBuffer, *m_IndexBuffer);
            glm::mat4 mvp = proj * view * shape->GetModelMatrix();
            m_Shader1->SetUniformMat4f("u_MVP", mvp);
            m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader1);
        }
    }
    m_FrameBuffer->UnBind();
    glDisable(GL_POLYGON_OFFSET_FILL);

    RenderSkybox();

    glm::mat4 view = m_World->GetPlayerCamera()->GetView();
    glm::mat4 proj = m_World->GetPlayerCamera()->GetProjection();

    m_Shader2->Bind();
    for (const auto &shape : m_World->GetShapes())
    {
        shape->SetData(*m_VertexBuffer, *m_IndexBuffer);
        glm::mat4 mv = view * shape->GetModelMatrix();
        glm::mat4 mvp = proj * mv;
        m_Shader2->SetUniformMat4f("u_V", view);
        m_Shader2->SetUniformMat4f("u_MV", mv);
        m_Shader2->SetUniformMat4f("u_MVP", mvp);
        m_Shader2->SetUniformMat4f("shadowMVP", lightProj * lightView * shape->GetModelMatrix());

        m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader2);
    }
}

void WorldRenderer::RenderSkybox()
{
    GLCALL(glDepthMask(GL_FALSE))

    m_SkyboxTexture->Bind();
    m_SkyboxShader->Bind();
    glm::mat4 view = m_World->GetPlayerCamera()->GetView();
    glm::mat4 proj = m_World->GetPlayerCamera()->GetProjection();
    m_SkyboxCube.SetData(*m_VertexBuffer, *m_IndexBuffer);
    auto no_translate = glm::mat4(glm::mat3(view));
    glm::mat4 mv = no_translate * m_SkyboxCube.GetModelMatrix();
    glm::mat4 mvp = proj * mv;
    m_SkyboxShader->SetUniformMat4f("u_MVP", mvp);

    m_Renderer->Draw(*m_VertexArray, *m_IndexBuffer, *m_SkyboxShader);

    GLCALL(glDepthMask(GL_TRUE))
}