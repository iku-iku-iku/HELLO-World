//
// Created by iku-iku-iku on 2022/10/2.
//

#pragma once

#include "WorldRenderer.h"
#include <vector>
#include <memory>
#include "Camera.h"
#include "Player.h"
#include "Core/Window.h"
#include "RenderingHeaders.h"
#include "Shape.h"



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

        const std::vector<std::unique_ptr<Shape>>&
        GetShapes() const {return m_ShapeVec;}

    private:
        std::vector<std::unique_ptr<Camera>> m_Cameras;

        std::unique_ptr<Player> m_Player;

        void PreInit();

        void Init();

        void PostInit();

        void OnRender();

        std::unique_ptr<Window> m_Window;

        std::unique_ptr<WorldRenderer> m_WorldRenderer;

        std::vector<std::unique_ptr<Shape>> m_ShapeVec;
    };
}

extern core::World world;