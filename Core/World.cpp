//
// Created by iku-iku-iku on 2022/10/2.
//

#include "World.h"

namespace core {

    World::World() {
        m_Cameras.emplace_back(std::make_unique<Camera>());
        m_Player = std::make_unique<Player>();
        m_Player->SetCamera(m_Cameras[0].get());
    }
}
