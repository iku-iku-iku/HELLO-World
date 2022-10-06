//
// Created by iku-iku-iku on 2022/10/2.
//


#pragma once

#include <vector>
#include <memory>
#include "Camera.h"
#include "Player.h"

namespace core {
    class World {
    public:
        World();

        Camera *GetPlayerCamera() { return m_Player->GetCamera(); }

        Player *GetPlayer() { return m_Player.get(); }

    private:
        std::vector<std::unique_ptr<Camera>> m_Cameras;

        std::unique_ptr<Player> m_Player;
    };
}
