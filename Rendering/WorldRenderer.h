#pragma once

#include <memory>
#include "Cube.h"
#include "Bead.h"
#include "Renderer.h"

namespace core {

class World;
}

class WorldRenderer : public Renderer
{
public:
    explicit WorldRenderer(core::World *inWorld);
    ~WorldRenderer() = default;

    void OnRender();

private:
    void Init();

    void RenderSkybox();

    void RenderBead();

    core::World *m_World;

    std::unique_ptr<Shader> m_Shader1;
    std::unique_ptr<Shader> m_Shader2;
    std::unique_ptr<Shader> m_UIShader;
    std::unique_ptr<Shader> m_SkyboxShader;
    std::unique_ptr<Texture> m_SkyboxTexture;

    core::Cube m_SkyboxCube;
    core::Bead m_Bead;
};