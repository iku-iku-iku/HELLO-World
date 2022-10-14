//
// Created by iku-iku-iku on 2022/10/2.
//

#include "World.h"
#include "Ring.h"
#include "Plane.h"

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

        SUCCEED("PreInit")
    }

    void World::Init()
    {
        m_WorldRenderer = std::make_unique<WorldRenderer>(this);

        m_Cameras.emplace_back(std::make_unique<Camera>());
        m_Player = std::make_unique<Player>();
        m_Player->SetCamera(m_Cameras[0].get());

        SUCCEED("World Init")
    }

    void World::PostInit()
    {
        m_ShapeVec.emplace_back(std::make_unique<Ring>());
        m_ShapeVec.emplace_back(std::make_unique<Plane>());


        SUCCEED("PostInit")
    }

    void World::Update()
    {
        Editor::ProcessInput(m_Window->GetWindow());
        OnRender();
        m_Window->Update();

    }

    void World::OnRender()
    {
        m_WorldRenderer->OnRender();
    }
}
