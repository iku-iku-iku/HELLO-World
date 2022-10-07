#pragma once

#include "RenderingHeaders.h"
#include <memory>
#include "Cube.h"

namespace core {

class World;
}

class WorldRenderer
{
public:
    explicit WorldRenderer(core::World *world);
    ~WorldRenderer() = default;

    void OnRender();

private:
    void PreInit();
    void Init();

    void RenderSkybox();

    core::World *m_World;

    std::unique_ptr<FrameBuffer> m_FrameBuffer;
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<Shader> m_Shader1;
    std::unique_ptr<Shader> m_Shader2;
    std::unique_ptr<Shader> m_SkyboxShader;
    std::unique_ptr<Texture> m_DepthMap;
    std::unique_ptr<Renderer> m_Renderer;
    std::unique_ptr<Texture> m_SkyboxTexture;

    Cube m_SkyboxCube;
};