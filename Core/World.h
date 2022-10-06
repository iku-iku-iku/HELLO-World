//
// Created by iku-iku-iku on 2022/10/2.
//

#pragma once

#include <vector>
#include <memory>
#include "Camera.h"
#include "Player.h"
#include "Core/Window.h"
#include "Shape/Ring.h"
#include "Shape/Plane.h"
#include "Rendering/Renderer.h"
#include "Rendering/FrameBuffer.h"
#include "Rendering/Texture.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/Shader.h"
#include "Rendering/IndexBuffer.h"
#include "Rendering/VertexArray.h"



namespace core
{
    class World
    {
    public:
        World();

        Camera *GetPlayerCamera() { return m_Player->GetCamera(); }

        Player *GetPlayer() { return m_Player.get(); }

        Window *GetWindow() { return m_Window.get(); }

        bool IsGoing() { return !m_Window->ShouldClose(); }

        void Update();

    private:
        std::vector<std::unique_ptr<Camera>> m_Cameras;

        std::unique_ptr<Player> m_Player;

        void PreInit();

        void Init();

        void PostInit();

        void OnRender();

        std::unique_ptr<Window> m_Window;
        std::unique_ptr<FrameBuffer> m_FrameBuffer;
        std::unique_ptr<VertexArray> m_VertexArray;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader1;
        std::unique_ptr<Shader> m_Shader2;
        std::unique_ptr<Texture> m_DepthMap;
        std::unique_ptr<Renderer> m_Renderer;
        Ring m_Ring;
        Plane m_Plane;
    };
}

extern core::World world;