#include "Rendering/WorldRenderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Texture.h"
#include "Core/World.h"
#include "Core/Log.h"

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

WorldRenderer::WorldRenderer(core::World *inWorld) : m_World(inWorld) {
    Init();
}

void WorldRenderer::Init() {
    m_UIShader = std::make_unique<Shader>("../shaders/ui.shader");
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

    const char *map_path[] = {
            "../texture/right.jpg",
            "../texture/left.jpg",
            "../texture/top.jpg",
            "../texture/bottom.jpg",
            "../texture/front.jpg",
            "../texture/back.jpg",
    };
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    m_SkyboxTexture = Texture::CreateCubeMap(map_path);
    m_SkyboxShader = std::make_unique<Shader>("../shaders/skybox.shader");
    m_SkyboxShader->SetUniform1i("u_Texture", (int) m_SkyboxTexture->GetSlot());
    m_Shader2->SetUniform1i("shTex", (int) m_DepthMap->GetSlot());

    SUCCEED("Init WorldRender")
}

void WorldRenderer::OnRender() {
    float currentTime = 0.f;
    GLCALL(glClear(GL_COLOR_BUFFER_BIT))
    GLCALL(glClearColor(0.f, 0.f, 0.f, 1.f))

    RenderDepthMap();

    RenderSkybox();

    glm::mat4 view = m_World->GetPlayerCamera()->GetView();
    glm::mat4 proj = m_World->GetPlayerCamera()->GetPerspectiveProjection();

    m_Shader2->Bind();
    for (const auto &shape : m_World->GetShapes())
    {
        glm::mat4 mv = view * shape->GetModelMatrix();
        glm::mat4 mvp = proj * mv;

        glm::mat4 lightProj = world.GetPlayerCamera()->GetPerspectiveProjection();
        glm::mat4 lightView = glm::lookAt(glm::vec3(lightPos[0], lightPos[1], lightPos[2]), glm::vec3(0.f, 0.f, 0.f),
                                          glm::vec3(0.f, 1.f, 0.f));

        m_Shader2->SetUniformMat4f("u_V", view);
        m_Shader2->SetUniformMat4f("u_MV", mv);
        m_Shader2->SetUniformMat4f("u_MVP", mvp);
        m_Shader2->SetUniformMat4f("shadowMVP", lightProj * lightView * shape->GetModelMatrix());

        RenderShape(*shape, *m_Shader2);
    }


    GLCALL(glClear(GL_DEPTH_BUFFER_BIT))
    RenderBead();
}

void WorldRenderer::RenderSkybox() {
    GLCALL(glDepthMask(GL_FALSE))

    m_SkyboxTexture->Bind();
    m_SkyboxShader->Bind();
    glm::mat4 view = m_World->GetPlayerCamera()->GetView();
    glm::mat4 proj = m_World->GetPlayerCamera()->GetPerspectiveProjection();
    auto no_translate = glm::mat4(glm::mat3(view));
    glm::mat4 mv = no_translate * m_SkyboxCube.GetModelMatrix();
    glm::mat4 mvp = proj * mv;
    m_SkyboxShader->SetUniformMat4f("u_MVP", mvp);

    RenderShape(m_SkyboxCube,*m_SkyboxShader);

    GLCALL(glDepthMask(GL_TRUE))
}

void WorldRenderer::RenderBead() {
    m_UIShader->Bind();
    const glm::mat4 &model = m_Bead.GetModelMatrix();
    const glm::mat4 &mvp = m_World->GetPlayerCamera()->GetStaticViewProjection2D() * model;
    m_UIShader->SetUniformMat4f("u_MVP", mvp);
    m_UIShader->SetUniform4f("u_Color", 1.f, 0.f, 0.f, 1.f);
    RenderShape(m_Bead,*m_UIShader);
}
